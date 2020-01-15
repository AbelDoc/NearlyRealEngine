
    #version 450

    in vec4 in_Vertex;
    in vec4 in_Normal;
    in vec4 in_Tangent;

    uniform mat4 modelview;
    uniform mat4 projection;

    out vec4 normal;
    out vec4 pos;
    out vec4 color;

    void main() {
        normal = in_Normal;
        color = in_Tangent;
        pos = modelview * vec4(in_Vertex.xyz, 1.0);
        gl_Position = projection * pos;
    }
