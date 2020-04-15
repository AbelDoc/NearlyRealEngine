
    #version 450

    in vec4 in_Vertex;
    in vec4 in_Normal;
    in vec4 in_Tangent;

    uniform mat4 MVP;

    out vec2 uv;
    out vec3 vertex;
    out mat3 TBN;
    invariant out float material;

    void main() {
        vertex = in_Vertex.xyz;
        gl_Position = MVP * vec4(vertex, 1.0);

        vec3 T = in_Tangent.xyz;
        vec3 N = in_Normal.xyz;
        vec3 B = cross(N, T);

        TBN = mat3(T, B, N);

        uv = vec2(in_Vertex.w, in_Normal.w);
        material = in_Tangent.w;
    }
