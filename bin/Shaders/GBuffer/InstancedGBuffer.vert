
    #version 450

    #define MAX_MATERIALS_X4 8

    in vec4 in_Vertex;
    in vec4 in_Normal;
    in vec4 in_Tangent;
    in mat4 in_Matrix;

    uniform mat4 PV;

    out vec2 uv;
    out mat3 TBN;
    out vec4 vertexAndId;
    out vec3 normal;

    void main() {
        gl_Position = PV * in_Matrix * vec4(in_Vertex.xyz, 1.0);

        const int materialResolution = 1024;

        int id = int(in_Vertex.w);
        uv = vec2(in_Normal.w, in_Tangent.w) / materialResolution;
        vec3 T = normalize(in_Tangent.xyz);
        vec3 N = normalize(in_Normal.xyz);
        vec3 B = cross(N, T);
        vertexAndId = in_Vertex;
        normal = in_Normal.xyz;
        TBN = mat3(T, B, N);
    }
