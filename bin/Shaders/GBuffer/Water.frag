
    #version 450

    in vec3 worldPos;
    in vec3 normal;

    uniform float time;

    out vec3 [4] fragData;

    float wave(float time, float freq, float amp, float y) {
        float angle = (time + y) * freq;
        return sin(angle) * amp;
    }

    void main() {
        fragData[0] = worldPos;
        fragData[1] = vec3(0.8, 0.8, 1.0);
        fragData[2] = vec3(0, 1.0, 0);
        fragData[3] = vec3(0.1, 0.8, 0);
    }
