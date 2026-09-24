#version 330 core

out vec4 FragColor;

//Inputs

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

//Structs

struct DirectionalLight{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct Material{
    float strength;
    float intensity;
};

//Uniform lightning

uniform DirectionalLight dirLight;
uniform Material material = Material(3.0f, 32);

//Uniform textures

uniform sampler2D diffuse_0;
uniform sampler2D specular_0;

//Uniforms

uniform vec3 viewPos;

void main(){
    vec3 fragPos = FragPos;
    vec3 normal = normalize(Normal);

    vec3 result;

    //Directional Light - Ambient

    vec3 ambient = dirLight.ambient * vec3(texture(diffuse_0, TexCoords)).rgb;

    //Difuse

    vec3 lightDir = normalize(-dirLight.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 diffuse = dirLight.diffuse * diff * vec3(texture(diffuse_0, TexCoords)).rgb;

    //Specular

    vec3 viewDir = normalize(viewPos -fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.intensity);

    vec3 specular = material.strength * spec * vec3(texture(diffuse_0, TexCoords)).rgb;

    result += ambient;
    result += diffuse;
    result += specular;

    FragColor = vec4(result, 1.0);
}
