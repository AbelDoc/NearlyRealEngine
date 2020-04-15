
    #version 450

    in vec3 vertex;
    in mat3 TBN;
    invariant in vec3 materials;

    uniform sampler2DArray texAlbedos;
    uniform sampler2DArray texNormals;
    uniform sampler2DArray texRoughness;
    uniform sampler2DArray texMetallics;

    out vec3 [3] fragData;

    vec3 queryVec3(sampler2DArray sampler, vec3 normal, mat3 uv) {
        vec3 blending = pow(normal, vec3(4));
        blending /= dot(blending, vec3(1, 1, 1));

        vec3 sampleX = texture(sampler, uv[0]).rgb; // Project along x axis
        vec3 sampleY = texture(sampler, uv[1]).rgb; // Project along y axis
        vec3 sampleZ = texture(sampler, uv[2]).rgb; // Project along z axis

        return sampleX * blending.x + sampleY * blending.y + sampleZ * blending.z;
    }

    float queryFloat(sampler2DArray sampler, vec3 normal, mat3 uv) {
        vec3 blending = pow(normal, vec3(4));
        blending /= dot(blending, vec3(1, 1, 1));

        float sampleX = texture(sampler, uv[0]).r; // Project along x axis
        float sampleY = texture(sampler, uv[1]).r; // Project along y axis
        float sampleZ = texture(sampler, uv[2]).r; // Project along z axis

        return sampleX * blending.x + sampleY * blending.y + sampleZ * blending.z;
    }

    void main() {
        mat3 uv = mat3(vec3(vertex.yz * 0.1, materials.x),
                       vec3(vertex.xz * 0.1, materials.y),
                       vec3(vertex.xy * 0.1, materials.z));
        vec3 normal = normalize(TBN * (queryVec3(texNormals, TBN[2], uv) * 2.0 - 1.0));
        float roughness = queryFloat(texRoughness, normal, uv);
        float metallic  = queryFloat(texMetallics, normal, uv);
        vec3 color = queryVec3(texAlbedos, normal, uv);

        fragData[0] = color;
        fragData[1] = normal;
        fragData[2] = vec3(roughness, metallic, 0);
    }
