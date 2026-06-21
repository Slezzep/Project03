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

//Uniform lightning

uniform DirectionalLight directional;

//Uniform textures

uniform sampler2D tex0;

void main(){
    vec3 fragPos = normalize(FragPos);
    vec3 normal = normalize(Normal);

    vec3 result;

    //Directional Light

    vec3 lightDir = normalize(-fragPos);

    vec3 ambient = directional.ambient * vec3(texture(tex0, TexCoords)).rgb;

    result += ambient;

    FragColor = vec4(result, 1.0);
}