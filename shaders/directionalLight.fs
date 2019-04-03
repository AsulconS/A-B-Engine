#version 330 core
out vec4 FragColor;

in vec3 fragPos;
in vec3 normal;
in vec2 UV;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;

    float shininess;
};

struct Light
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    // Ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, UV));

    // Diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir =  normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, UV));

    // Specular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, UV));

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0f);
}
