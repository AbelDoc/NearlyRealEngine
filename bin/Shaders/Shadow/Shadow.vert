
    #version 450

    in vec4 in_Vertex;

    uniform mat4 lightMVP;

    void main() {
        gl_Position = lightMVP * vec4(in_Vertex.xyz, 1.0);
    }
