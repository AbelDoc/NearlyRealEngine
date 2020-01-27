
    #version 450

    in vec2 uv;
    in vec3 vertex;
    in vec3 normal;
    in vec3 tangent;
    in vec3 materials;

    out vec4 [3] fragData;

    void main() {
        fragData[0] = vec4(normal, uv.s);
        fragData[1] = vec4(tangent, uv.t);
        fragData[2] = vec4(materials, 0);
    }
