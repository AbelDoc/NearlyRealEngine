
    #version 450

    in vec3 worldPos;
    in vec3 normal;
    in vec3 color;
    in float roughness;
    in float metallic;

    out vec3 [4] fragData;

    void main() {
        fragData[0] = worldPos;
        fragData[1] = color;
        fragData[2] = normalize(normal);
        fragData[3] = vec3(roughness, metallic, 0);
    }
