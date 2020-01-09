
    #version 450

    in vec4 in_Vertex;

    uniform mat4 modelview;

    out vec3 vertex;

    void main() {
        gl_Position = modelview * vec4(in_Vertex);
        vertex = in_Vertex.xyz;
    }
