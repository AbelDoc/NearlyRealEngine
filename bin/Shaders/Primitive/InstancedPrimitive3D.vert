
    #version 450

    in vec4 in_Vertex;
    in vec4 in_Normal;
    in vec4 in_Color;
    in mat4 in_Matrix;

    uniform mat4 modelview;
    uniform mat4 projection;

    out vec4 normal;
    out vec4 pos;
    out vec4 color;

    void main() {
        normal = in_Normal;
        color = in_Color;
        pos = modelview * in_Matrix * in_Vertex;
        gl_Position = projection * pos;
    }
