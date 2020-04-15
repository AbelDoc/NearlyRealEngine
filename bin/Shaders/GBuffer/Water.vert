
    #version 450

    in vec4 in_Vertex;
    in vec4 in_Normal;

    uniform mat4 MVP;
    uniform float time;

    out vec3 vertex;
    out vec3 normal;

    float wave(float time, float freq, float amp, float y) {
        float angle = (time + y) * freq;
        return sin(angle) * amp;
    }

    void main() {
        const float freq = 0.05;
        const float amp = 0.1;

        normal = in_Normal.xyz;
        vertex = in_Vertex.xyz;

        float d = wave(time, freq, amp, vertex.x)
                + wave(time, freq * 2.0, amp / 2.0, vertex.x)
                + wave(time, freq * 3.5, amp * 0.2, vertex.x);

        vertex = vertex + vec3(0, d, 0);
        gl_Position = MVP * vec4(vertex, 1.0);
    }
