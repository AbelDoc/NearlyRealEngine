
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
    uniform sampler2DArray texAlbedos;

    uniform vec3 cameraV;

    const float PI = 3.14159265359;

    out vec4 out_Color;

    vec4 worldPosFromDepth(vec2 tc) {
        float z = texture(texDepth, tc).x * 2.0 - 1.0;

        vec4 clipSpacePosition = vec4(tc * 2.0 - 1.0, z, 1.0);
        vec4 viewSpacePosition = invProjection * clipSpacePosition;

        return viewSpacePosition /= viewSpacePosition.w;
    }

    vec3 queryVec3(sampler2DArray sampler, vec3 normal, vec3 worldPos, vec3 ids) {
        vec3 blending = abs(normal);
        blending = normalize(max(blending, 0.00001));
        float b = (blending.x + blending.y + blending.z);
        blending /= vec3(b, b, b);

        vec3 sampleX = texture(sampler, vec3(worldPos.yz * 0.05, ids.x)).rgb; // Project along x axis
        vec3 sampleY = texture(sampler, vec3(worldPos.xz * 0.05, ids.y)).rgb; // Project along y axis
        vec3 sampleZ = texture(sampler, vec3(worldPos.xy * 0.05, ids.z)).rgb; // Project along z axis

        return sampleX * blending.x + sampleY * blending.y + sampleZ * blending.z;
    }

    void main() {
        vec3 vertex = (invModelview * worldPosFromDepth(uv)).xyz;
        vec4 normalAndU = texture(texNormal, uv);
        vec3 normal = normalAndU.xyz;

        if (normal != vec3(0.0, 0.0, 0.0)) {
            vec3 ids = texture(texMaterials, uv).xyz;
            vec3 viewDir = normalize(cameraV - vertex);
            vec3 color = queryVec3(texAlbedos, normal, vertex, ids);
            vec3 ambient = 0.05 * color;

            vec3 diffuse, specular;
            for (int i = 0; i < numLights; i = i + 1) {
                vec3 lightDir = normalize(lights[i].position - vertex);
                vec3 halfwayDir = normalize(lightDir + viewDir);
                float diff = max(dot(lightDir, normal), 0.0);
                diffuse += color * diff;
                float spec = pow(max(dot(normal, halfwayDir), 0.0), 32);
                specular += lights[i].intensities * spec;
            }
            out_Color = vec4(ambient + diffuse + specular, 1.0);
        } else {
            out_Color = vec4(texture(texTangent, uv).rgb, 0.0);
        }
    }
