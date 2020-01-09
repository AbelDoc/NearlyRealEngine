
    #version 450

    in vec3 vertex;

    uniform sampler2D skyBox;

    out vec4 out_Color;

    const vec2 invAtan = vec2(0.1591, 0.3183);

    vec2 samplerSphericalMap(vec3 v) {
        vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
        uv *= invAtan;
        uv += 0.5;

        return uv;
    }

    void main() {
        vec2 uv = samplerSphericalMap(normalize(vertex));
        vec3 color = texture(skyBox, uv).rgb;

        out_Color = vec4(color, 1.0);
    }
