
    #version 450

    in vec4 in_Vertex;
    in vec4 in_Normal;

    uniform mat4 modelview;
    uniform mat4 projection;

    out vec3 normal;

    void main() {
        gl_Position = projection * modelview * in_Vertex;
        mat3 normalMatrix = mat3(transpose(inverse(modelview)));
        normal = normalize(vec3(projection * vec4(normalMatrix * in_Normal.xyz, 0.0)));
    }
