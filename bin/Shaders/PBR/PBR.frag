
    #version 450

    #define MAX_LIGHTS 100

    uniform int numLights;
    uniform struct Light {
       vec3 position;
       vec3 intensities;
    } lights[MAX_LIGHTS];

    in vec2 uv;

    uniform mat4 lightSpace;
    uniform mat4 invView;

    uniform sampler2D texPos;
    uniform sampler2D texShadow;
    uniform sampler2D texColor;
    uniform sampler2D texNormal;
    uniform sampler2D texMaterial;
    uniform samplerCube irradianceMap;
    uniform samplerCube prefilterMap;
    uniform sampler2D brdfLUT;

    uniform vec3 cameraV;

    const float PI = 3.14159265359;

    out vec4 out_Color;

    vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness) {
        return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);
    }

    vec3 fresnelSchlick(float cosTheta, vec3 F0) {
        return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
    }

    float distributionGGX(vec3 N, vec3 H, float roughness) {
        float a = roughness * roughness;
        float a2 = a * a;
        float NdotH = max(dot(N, H), 0.0);
        float NdotH2 = NdotH * NdotH;

        float num = a2;
        float denom = (NdotH2 * (a2 - 1.0) + 1.0);
        denom = PI * denom * denom;

        return num / denom;
    }

    float geometrySchlickGGX(float NdotV, float roughness) {
        float r = roughness + 1.0;
        float k = (r * r) / 8.0;

        float num = NdotV;
        float denom = NdotV * (1.0 - k) + k;

        return num / denom;
    }

    float geometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
        float NdotV = max(dot(N, V), 0.0);
        float NdotL = max(dot(N, L), 0.0);
        float ggx2 = geometrySchlickGGX(NdotV, roughness);
        float ggx1 = geometrySchlickGGX(NdotL, roughness);

        return ggx1 * ggx2;
    }

    float computeBlur(vec2 uv) {
        vec2 texelSize = 1.0 / vec2(textureSize(texMaterial, 0));
        float result = 0.0;
        for (int x = -2; x < 2; x = x + 1) {
            for (int y = -2; y < 2; y = y + 1) {
                vec2 offset = vec2(float(x), float(y)) * texelSize;
                result += texture(texMaterial, uv + offset).z;
            }
        }
        return result / (4.0 * 4.0);
    }

    float computeShadow(vec4 vertexLightSpace) {
        vec3 projCoords = vertexLightSpace.xyz / vertexLightSpace.w;
        projCoords = projCoords * 0.5 + 0.5;
        float closestDepth = texture(texShadow, projCoords.xy).r;
        float currentDepth = projCoords.z;
        float bias = 0.05;
        float shadow = 0.0;
        vec2 texelSize = 1.0 / textureSize(texShadow, 0);
        for(int x = -2; x <= 2; ++x) {
            for(int y = -2; y <= 2; ++y) {
                float pcfDepth = texture(texShadow, projCoords.xy + vec2(x, y) * texelSize).r;
                shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
            }
        }
        shadow /= 16.0;
        return shadow;
    }

    void main() {
        vec3 N = texture(texNormal, uv).xyz;
        if (N != vec3(0.0, 0.0, 0.0)) {
            vec3 vertex = (invView * texture(texPos, uv)).xyz;
            vec3 V = normalize(cameraV - vertex);
            vec3 R = reflect(-V, N);

            vec2 material = texture(texMaterial, uv).rg;

            vec3 albedo = texture(texColor, uv).rgb;
            float roughness = material.x;
            float metallic = material.y;

            vec3 F0 = vec3(0.04);
            F0 = mix(F0, albedo, metallic);

            vec3 Lo = vec3(0.0);
            for (int i = 0; i < numLights; i = i + 1) {
                vec3 L = normalize(lights[i].position - vertex);
                vec3 H = normalize(V + L);

                float distance = length(lights[i].position - vertex);
                float attenuation = 1.0 / (distance * distance);
                vec3 radiance = lights[i].intensities * attenuation;

                float NDF = distributionGGX(N, H, roughness);
                float G = geometrySmith(N, V, L, roughness);
                vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);

                vec3 numerator = NDF * G * F;
                float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001;
                vec3 specular = numerator / denominator;

                vec3 kS = F;
                vec3 kD = vec3(1.0) - kS;
                kD *= 1.0 - metallic;

                float NdotL = max(dot(N, L), 0.0);
                Lo += (kD * albedo / PI + specular) * radiance * NdotL;
            }

            vec3 F = fresnelSchlickRoughness(max(dot(N, V), 0.0), F0, roughness);

            vec3 kS = F;
            vec3 kD = 1.0 - kS;
            kD *= 1.0 - metallic;

            vec3 irradiance = texture(irradianceMap, N).rgb;
            vec3 diffuse = irradiance * albedo;

            const float MAX_REFLECTION_LOD = 4.0;
            vec3 prefilteredColor = textureLod(prefilterMap, R, roughness * MAX_REFLECTION_LOD).rgb;
            vec2 brdf = texture(brdfLUT, vec2(max(dot(N, V), 0.0), roughness)).rg;
            vec3 specular = prefilteredColor * (F * brdf.x + brdf.y);

            float ao = computeBlur(uv);
            vec3 ambient = (kD * diffuse + specular) * ao;

            vec3 color = ambient + Lo;

            float exposure = 0.2;
            float gamma = 2.2;
            vec3 mapped = vec3(1.0) - exp(-color * exposure);
            mapped = pow(mapped, vec3(1.0 / gamma));

            out_Color = vec4(mapped, 1.0);
        } else {
            out_Color = vec4(texture(texColor, uv).rgb, 1.0);
        }
    }
