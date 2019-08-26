
    #version 450

    in vec4 in_Vertex;
    in vec4 in_Color;

    out vec4 color;

    void main() {
        gl_Position = in_Vertex;

        color = in_Color;
    }
