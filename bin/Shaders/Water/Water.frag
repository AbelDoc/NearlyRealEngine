
    #version 450

    in vec2 uv;
    in vec3 vertex;
    in vec3 normal;
    in vec3 tangent;
    in vec3 materials;

    uniform float time;

    out vec4 [3] fragData;

    float wave(float time, float freq, float amp, float y) {
        float angle = (time + y) * freq;
        return sin(angle) * amp;
    }

    void main() {
        const float freq = 0.05;
        const float amp = 0.1;

        float d = wave(time, freq, amp, vertex.x)
                + wave(time, freq * 2.0, amp / 2.0, vertex.x)
                + wave(time, freq * 3.5, amp * 0.2, vertex.x);

        vec3 n = normalize(vec3(0, d, 1));

        fragData[0] = vec4(normalize(normal + n), uv.s);
        fragData[1] = vec4(normalize(tangent + n), uv.t);
        fragData[2] = vec4(materials, 0);
    }
