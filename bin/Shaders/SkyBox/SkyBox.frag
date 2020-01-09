
    #version 450

    in vec3 vertex;

    uniform samplerCube skyBox;

    out vec4 [2] fragData;

    void main() {
        vec3 envColor = texture(skyBox, vertex).rgb;

        fragData[0] = vec4(envColor, 1.0);
        fragData[1] = vec4(0, 0, 0, 1);
    }
