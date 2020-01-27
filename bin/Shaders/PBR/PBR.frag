
    #version 450

    #define MAX_LIGHTS 100

    uniform int numLights;
    uniform struct Light {
       vec3 position;
       vec3 intensities;
    } lights[MAX_LIGHTS];

    in vec2 uv;

    uniform mat4 invModelview;
    uniform mat4 invProjection;

    uniform sampler2D texDepth;
    uniform sampler2D texNormal;
    uniform sampler2D texTangent;
    uniform sampler2D texMaterials;
    uniform samplerCube irradianceMap;
    uniform samplerCube prefilterMap;
    uniform sampler2D brdfLUT;
    uniform sampler2DArray texAlbedos;
    uniform sampler2DArray texNormals;
    uniform sampler2DArray texRoughness;
    uniform sampler2DArray texMetallics;
    uniform sampler2DArray texDisplacements;

    uniform vec3 cameraV;

    const float PI = 3.14159265359;

    out vec4 out_Color;

    vec4 worldPosFromDepth(vec2 tc) {
        float z = texture(texDepth, tc).x * 2.0 - 1.0;

        vec4 clipSpacePosition = vec4(tc * 2.0 - 1.0, z, 1.0);
        vec4 viewSpacePosition = invProjection * clipSpacePosition;

        return viewSpacePosition /= viewSpacePosition.w;
    }

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
        vec2 texelSize = 1.0 / vec2(textureSize(texMaterials, 0));
        float result = 0.0;
        for (int x = -2; x < 2; x = x + 1) {
            for (int y = -2; y < 2; y = y + 1) {
                vec2 offset = vec2(float(x), float(y)) * texelSize;
                result += texture(texMaterials, uv + offset).a;
            }
        }

        return result / (4.0 * 4.0);
    }

    vec3 queryVec3(sampler2DArray sampler, vec3 normal, vec3 worldPos, vec3 ids) {
        vec3 blending = abs(normal);
        blending = normalize(max(blending, 0.00001));
        float b = (blending.x + blending.y + blending.z);
        blending /= vec3(b, b, b);

        vec3 sampleX = texture(sampler, vec3(worldPos.yz * 0.01, ids.x)).rgb; // Project along x axis
        vec3 sampleY = texture(sampler, vec3(worldPos.xz * 0.01, ids.y)).rgb; // Project along y axis
        vec3 sampleZ = texture(sampler, vec3(worldPos.xy * 0.01, ids.z)).rgb; // Project along z axis

        return sampleX * blending.x + sampleY * blending.y + sampleZ * blending.z;
    }

    float queryFloat(sampler2DArray sampler, vec3 normal, vec3 worldPos, vec3 ids) {
        vec3 blending = abs(normal);
        blending = normalize(max(blending, 0.00001));
        float b = (blending.x + blending.y + blending.z);
        blending /= vec3(b, b, b);

        float sampleX = texture(sampler, vec3(worldPos.yz * 0.01, ids.x)).r; // Project along x axis
        float sampleY = texture(sampler, vec3(worldPos.xz * 0.01, ids.y)).r; // Project along y axis
        float sampleZ = texture(sampler, vec3(worldPos.xy * 0.01, ids.z)).r; // Project along z axis

        return sampleX * blending.x + sampleY * blending.y + sampleZ * blending.z;
    }

    void main() {
        vec3 vertex = (invModelview * worldPosFromDepth(uv)).xyz;
        vec4 normalAndU = texture(texNormal, uv);
        vec3 normal = normalAndU.xyz;

        if (normal != vec3(0.0, 0.0, 0.0)) {
            vec4 tangentAndV = texture(texTangent, uv);
            vec3 T = tangentAndV.xyz;
            vec3 N = normal;
            vec3 B = cross(N, T);
            vec3 ids = texture(texMaterials, uv).xyz;

            mat3 TBN = mat3(T, B, N);

            vec2 tileUV = vec2(normalAndU.w, tangentAndV.w);

            N = TBN * normalize(queryVec3(texNormals, normal, vertex, ids) * 2.0 - 1.0);

            vec3 V = normalize(cameraV - vertex);
            vec3 R = reflect(-V, N);

            vec3 albedo = queryVec3(texAlbedos, normal, vertex, ids);
            float roughness = queryFloat(texRoughness, normal, vertex, ids);
            float metallic = queryFloat(texMetallics, normal, vertex, ids);
            float displacement = queryFloat(texDisplacements, normal, vertex, ids);

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

            vec3 ambient = (kD * diffuse + specular) * computeBlur(uv);

            vec3 color = (ambient + Lo);
            color = color / (color + vec3(1.0));
            color = pow(color, vec3(1.0/2.2));

            out_Color = vec4(color, 1.0);
        } else {
            out_Color = vec4(texture(texTangent, uv).rgb, 0.0);
        }
    }
