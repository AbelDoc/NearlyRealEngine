
    #version 450

    in vec4 in_Vertex;

    out vec2 uv;

    void main() {
        gl_Position = vec4(in_Vertex.xy, 0.0, 1.0);
        uv = in_Vertex.zw;
    }
