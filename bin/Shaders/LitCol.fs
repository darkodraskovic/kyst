#version 330 core

#include Lib/uniform.glsl
#include Lib/light.glsl

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float shininess;
};
uniform Material uMaterial;

in vec3 vFragPos;
in vec3 vFragNorm;
out vec4 FragCol;

void main()
{
    // ambient
    vec3 ambient = uLight.ambient * uMaterial.ambient;

    // diffuse
    vec3 norm = normalize(vFragNorm);
    vec3 lightDir = normalize(uLight.position - vFragPos);
    float intensity = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = uLight.diffuse * (intensity * uMaterial.diffuse);

    // specular
    vec3 viewDir = normalize(uViewPos - vFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    vec3 specular = uLight.specular * (spec * uMaterial.specular);

    vec3 result = ambient + diffuse + specular;
    FragCol = vec4(result, uAlpha);
}
