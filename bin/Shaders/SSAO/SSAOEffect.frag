
    #version 450

    in vec2 uv;

    uniform mat4 projection;
    uniform mat3 normalMat;

    uniform sampler2D texPos;
    uniform sampler2D texNormal;
    uniform sampler2D texNoise;

    const int MAX_KERNEL_SIZE = 64;
    const float radius = 0.5;
    const float bias = 0.025;

    uniform vec3 gKernel[MAX_KERNEL_SIZE];

    const vec2 noiseOffset = vec2(1280.0 / 4.0, 720.0 / 4.0);

    out vec3 fragData;

    void main() {
        vec3 N = normalMat * texture(texNormal, uv).xyz;
        if (N != vec3(0.0, 0.0, 0.0)) {
            vec3 vertex = texture(texPos, uv).xyz;
            vec3 noise = normalize(texture(texNoise, uv * noiseOffset).xyz);

            vec3 tangent = normalize(noise - N * dot(noise, N));
            vec3 bitangent = cross(N, tangent);

            mat3 TBN = mat3(tangent, bitangent, N);

            float occlusion = 0.0;
            for (int i = 0; i < MAX_KERNEL_SIZE; i++) {
                vec3 sampleV = TBN * gKernel[i];
                sampleV = vertex + sampleV * radius;

                vec4 offset = vec4(sampleV, 1.0);
                offset = projection * offset;
                offset.xy /= offset.w;
                offset.xy = offset.xy * 0.5 + 0.5;

                float sampleDepth = texture(texPos, offset.xy).z;
                float rangeCheck = smoothstep(0.0, 1.0, radius / abs(vertex.z - sampleDepth));
                occlusion += (sampleDepth >= sampleV.z + bias ? 1.0 : 0.0) * rangeCheck;
            }

            occlusion = 1.0 - (occlusion / MAX_KERNEL_SIZE);
            occlusion = pow(occlusion, 2);
            fragData = vec3(0, 0, occlusion);
        } else {
            fragData = vec3(0);
        }

    }
