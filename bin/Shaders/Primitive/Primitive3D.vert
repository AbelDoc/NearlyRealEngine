
    #version 450

    in vec4 in_Vertex;
    in vec4 in_Color;

    uniform mat4 MVP;

    out vec4 color;

    void main() {
        gl_Position = MVP * in_Vertex;

        color = in_Color;
    }
