
    #version 450

    in vec3 vertex;

    uniform samplerCube skyBox;

    out vec3 [4] fragData;

    void main() {
        vec3 envColor = textureLod(skyBox, vertex, 0.0).rgb;

        fragData[0] = vec3(0);
        fragData[1] = envColor;
        fragData[2] = vec3(0);
        fragData[3] = vec3(0);
    }
