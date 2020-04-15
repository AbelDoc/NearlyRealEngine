
    #version 450

    in vec2 uv;
    in vec3 vertex;
    in mat3 TBN;
    invariant in float material;

    uniform sampler2DArray texAlbedos;
    uniform sampler2DArray texNormals;
    uniform sampler2DArray texRoughness;
    uniform sampler2DArray texMetallics;

    out vec3 [3] fragData;

    void main() {
        vec3 uv3 = vec3(uv, material);
        vec3 normal = normalize(TBN * (texture(texNormals, uv3).xyz * 2.0 - 1.0));
        float roughness = texture(texRoughness, uv3).r;
        float metallic = texture(texMetallics, uv3).r;
        vec3 color = texture(texAlbedos, uv3).xyz;

        fragData[0] = color;
        fragData[1] = normal;
        fragData[2] = vec3(roughness, metallic, 0);
    }
