
    #version 450

    in vec3 vertex;
    in vec3 normal;

    uniform float time;

    out vec3 [3] fragData;

    float wave(float time, float freq, float amp, float y) {
        float angle = (time + y) * freq;
        return sin(angle) * amp;
    }

    void main() {
        const float freq = 0.05;
        const float amp = 0.1;
        const vec3 color = vec3(1.0, 1.0, 1.0);
        const float roughness = 0;
        const float metallic = 1;

        float d = wave(time, freq, amp, vertex.x)
                + wave(time, freq * 2.0, amp / 2.0, vertex.x)
                + wave(time, freq * 3.5, amp * 0.2, vertex.x);

        vec3 n = normalize(normal + vec3(0, d, 1));

        fragData[0] = color;
        fragData[1] = n;
        fragData[2] = vec3(roughness, metallic, 0);
    }
