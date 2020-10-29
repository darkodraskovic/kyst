struct Light
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
};
uniform Light uLight;

uniform vec3 uViewPos;
