
    #version 450

    in vec4 in_Vertex;
    in vec4 in_Normal;
    in mat4 in_Matrix;

    uniform mat4 modelview;
    uniform mat4 projection;

    out vec4 normal;
    out vec4 pos;
    out vec4 realPos;

    uniform sampler2D tex;

    void main() {
        vec3 clamped = (in_Vertex.xyz + vec3(16 * 10, 0, 16 * 10)) / vec3(16 * 21, 16 * 5, 16 * 21);

        normal = in_Normal;

        realPos = in_Matrix * (in_Vertex - vec4(texture(tex, clamped.xz).rgb, 0));
        pos = modelview * realPos;

        gl_Position = projection * modelview * realPos;
    }
