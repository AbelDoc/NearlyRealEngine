
    #version 450

    in vec4 in_Vertex;
    in vec4 in_Normal;
    in vec4 in_Tangent;
    in vec4 in_Material;
    in mat4 in_Matrix;

    uniform mat4 PV;

    out vec2 uv;
    out vec3 vertex;
    out vec3 normal;
    out vec3 tangent;
    out vec3 materials;

    void main() {
        gl_Position = PV * in_Matrix * vec4(in_Vertex.xyz, 1.0);

        vertex = in_Vertex.xyz;
        normal = in_Normal.xyz;
        tangent = in_Tangent.xyz;
        materials = in_Material.xyz;
    }
