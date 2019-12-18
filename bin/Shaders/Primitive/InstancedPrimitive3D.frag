
    #version 450

    in vec4 normal;
    in vec4 pos;
    in vec4 color;

    uniform vec3 camera;

    out vec4 out_Color;

    void main() {
        float ambientStrength = 0.5;
        vec3 ambient = ambientStrength * color.rgb;

        vec3 norm = normal.xyz;
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
