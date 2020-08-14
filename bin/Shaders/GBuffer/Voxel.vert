
    #version 450

    in vec4 in_Vertex;
    in vec4 in_Normal;
    in vec4 in_Color;

    uniform mat4 view;
    uniform mat4 projection;

    out vec3 worldPos;
    out vec3 normal;
    out vec3 color;
    out float roughness;
    out float metallic;

    void main() {
        vec4 viewPos = view * vec4(in_Vertex.xyz, 1.0);
        worldPos = viewPos.xyz;

        normal = in_Normal.xyz;
        metallic = in_Normal.w;

        color = in_Color.rgb;
        roughness = in_Color.a;

        gl_Position = projection * viewPos;
    }
