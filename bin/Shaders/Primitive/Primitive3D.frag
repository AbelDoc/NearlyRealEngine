
    #version 450

    in vec4 normal;
    in vec4 pos;
    in vec4 realPos;

    uniform vec3 camera;

    uniform sampler2D tex;

    out vec4 out_Color;

    void main() {
        vec3 clamped = (realPos.xyz + vec3(16 * 10, 0, 16 * 10)) / vec3(16 * 21, 16 * 5, 16 * 21);

        float ambientStrength = 0.5;
        vec3 ambient = ambientStrength * texture(tex, clamped.xz).rgb;

        vec3 norm = normalize((normal.xyz * texture(tex, clamped.xz).rgb) / 2);
        vec3 lightDir = normalize(vec3(0, 200, 0) - pos.xyz);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * vec3(0.5);

        float specularStrength = 0.1;
        vec3 viewDir = normalize(camera - pos.xyz);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * vec3(1.0, 1.0, 1.0);

        vec3 result = ambient + diffuse + specular;
        out_Color = vec4(result, 1.0);
    }
