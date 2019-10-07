
    #version 450

    layout (triangles) in;
    layout (line_strip, max_vertices = 6) out;

    in vec3 normal[];

    const float MAGNITUDE = 0.4;

    void generateLine(int index) {
        gl_Position = gl_in[index].gl_Position;
        EmitVertex();
        gl_Position = gl_in[index].gl_Position + vec4(normal[index], 0.0);
        EmitVertex();
        EndPrimitive();
    }

    void main() {
        generateLine(0);
        generateLine(1);
        generateLine(2);
    }
