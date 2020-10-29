#version 330 core

#include Lib/uniform.glsl
#include Lib/light.glsl

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emissive;
  
    float shininess;
};
uniform Material uMaterial;

in vec3 vFragPos;
in vec3 vFragNorm;
in vec2 vTexCoord;
out vec4 FragCol;

void main()
{
    // ambient
    vec3 ambient = uLight.ambient * texture(uMaterial.diffuse, vTexCoord).rgb;

    // diffuse
    vec3 norm = normalize(vFragNorm);
    vec3 lightDir = normalize(uLight.position - vFragPos);
    float intensity = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = uLight.diffuse * (intensity * texture(uMaterial.diffuse, vTexCoord).rgb);

    // specular
    vec3 viewDir = normalize(uViewPos - vFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    vec3 specular = uLight.specular * (spec * texture(uMaterial.specular, vTexCoord).rgb);

    // emissive
    vec3 emissive = texture(uMaterial.emissive, vTexCoord).rgb;
    
    vec3 result = ambient + diffuse + specular + emissive;
    // vec3 result = ambient + diffuse + emissive;
    FragCol = vec4(result, uAlpha);
}
