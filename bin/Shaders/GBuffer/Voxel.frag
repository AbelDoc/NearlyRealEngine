
    #version 450

    #define MAX_MAT 16

    uniform int numMats;
    uniform struct Material {
        vec3 albedo;
        float roughness;
        float metallic;
    } materials[MAX_MAT];

    in vec3 worldPos;
    in vec3 normal;
    flat in int material;

    out vec3 [4] fragData;

    void main() {
        fragData[0] = worldPos;
        fragData[1] = materials[material].albedo;
        fragData[2] = normalize(normal);
        fragData[3] = vec3(materials[material].roughness, materials[material].metallic, 0);
    }
