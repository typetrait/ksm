#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 outColor;
in vec3 Normal;
in vec2 TexCoord;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform sampler2D sampler;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    // ambient light
    vec3 ambient = light.ambient * material.ambient;

    // diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    // specular light
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    FragColor = texture(sampler, TexCoord);
    FragColor *= vec4(outColor, 1.0f);
    FragColor *= vec4(ambient + diffuse + specular, 1.0);
}
