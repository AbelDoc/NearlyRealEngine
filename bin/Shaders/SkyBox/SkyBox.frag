
    #version 450

    in vec3 vertex;

    uniform samplerCube skyBox;

    out vec3 [3] fragData;

    void main() {
        vec3 envColor = textureLod(skyBox, vertex, 0.0).rgb;

        fragData[0] = envColor;
        fragData[1] = vec3(0);
        fragData[2] = vec3(0);
    }
