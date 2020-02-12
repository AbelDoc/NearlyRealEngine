
    #version 450

    in vec4 in_Vertex;
    in mat4 in_Matrix;

    uniform mat4 lightPV;

    void main() {
        gl_Position = lightPV * in_Matrix * vec4(in_Vertex.xyz, 1.0);
    }
