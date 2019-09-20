
    #version 450

    in vec4 in_Vertex;
    in vec4 in_Normal;

    uniform mat4 modelview;
    uniform mat4 projection;

    out vec4 normal;
    out vec4 pos;
    out vec4 realPos;

    void main() {
        pos = modelview * in_Vertex;
        normal = in_Normal;

        realPos = in_Vertex;

        gl_Position = projection * pos;
    }
