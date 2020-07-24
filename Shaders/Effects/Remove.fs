#version 330 core
out vec4 FragColor;

in vec2 vTexCoords;

uniform sampler2D uTexture;

void main()
{
    vec3 col = texture(uTexture, vTexCoords).rgb;
    col.y = 0;
    col.z = 0;
    FragColor = vec4(col, 1.0);
}
