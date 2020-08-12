
    #version 450

    in vec4 in_Vertex;
    in vec4 in_Normal;

    uniform mat4 view;
    uniform mat4 projection;

    uniform float time;

    out vec3 worldPos;
    out vec3 normal;

    float wave(float time, float freq, float amp, float y) {
        float angle = (time + y) * freq;
        return sin(angle) * amp;
    }

    void main() {
        vec4 viewPos = view * vec4(in_Vertex.xyz, 1.0);
        worldPos = viewPos.xyz;

        normal = in_Normal.xyz;

        gl_Position = projection * viewPos;
    }
