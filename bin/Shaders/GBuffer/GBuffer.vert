
    #version 450

    in vec4 in_Vertex;
    in vec4 in_Normal;
    in vec4 in_Tangent;
    in vec4 in_Material;

    uniform mat4 MVP;

    out vec2 uv;
    out vec3 vertex;
    out vec3 normal;
    out vec3 tangent;
    out vec3 materials;

    void main() {
        gl_Position = MVP * vec4(in_Vertex.xyz, 1.0);

        uv = vec2(in_Normal.w, in_Tangent.w);

        vertex = in_Vertex.xyz;
        normal = in_Normal.xyz;
        tangent = in_Tangent.xyz;
        materials = in_Material.xyz;
    }
