
    #version 450

    in vec4 in_Vertex;
    in vec4 in_Normal;
    in vec4 in_Tangent;
    in vec4 in_Material;

    uniform mat4 MVP;
    uniform float time;

    out vec2 uv;
    out vec3 vertex;
    out vec3 normal;
    out vec3 tangent;
    out vec3 materials;

    float wave(float time, float freq, float amp, float y) {
        float angle = (time + y) * freq;
        return sin(angle) * amp;
    }

    void main() {
        uv = vec2(in_Normal.w, in_Tangent.w);

        const float freq = 0.5;
        const float amp = 0.1;

        vertex = in_Vertex.xyz;

        float d = wave(time, freq, amp, vertex.x)
                + wave(time, freq * 2.0, amp / 2.0, vertex.x)
                + wave(time, freq * 3.5, amp * 0.2, vertex.x);

        normal = in_Normal.xyz;
        tangent = in_Tangent.xyz;
        materials = in_Material.xyz;
        gl_Position = MVP * vec4(vertex + vec3(0, d, 0), 1.0);
    }
