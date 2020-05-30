
    #version 450

    #define MAX_MAT 100

    uniform int numMats;
    uniform struct Material {
        vec3 albedo;
        float roughness;
        float metallic;
    } materials[MAX_MAT];

    in vec3 vertex;
    in vec3 normal;
    flat in int material;

    out vec3 [3] fragData;

    void main() {
        fragData[0] = materials[material].albedo;
        fragData[1] = normal;
        fragData[2] = vec3(materials[material].roughness, materials[material].metallic, 0);
    }
