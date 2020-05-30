
    #version 450

    in vec4 in_Vertex;
    in vec4 in_Normal;

    uniform mat4 MVP;

    out vec3 vertex;
    out vec3 normal;
    flat out int material;

    void main() {
        vertex = in_Vertex.xyz;
        gl_Position = MVP * vec4(vertex, 1.0);

        normal = in_Normal.xyz;
        material = int(in_Normal.w);
    }
