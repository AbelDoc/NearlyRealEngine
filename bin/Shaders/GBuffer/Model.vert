
    #version 450

    in vec4 in_Vertex;
    in vec4 in_Normal;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    out vec3 worldPos;
    out vec3 normal;
    flat out int material;

    void main() {
        vec4 viewPos = view * model * vec4(in_Vertex.xyz, 1.0);
        worldPos = viewPos.xyz;

        material = int(in_Normal.w);
        normal = in_Normal.xyz;

        gl_Position = projection * viewPos;
    }
