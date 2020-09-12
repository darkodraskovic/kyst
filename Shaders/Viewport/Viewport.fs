#version 330 core

uniform sampler2D uTexture;

in vec3 vPos;
in vec2 vTexCoord;
out vec4 FragColor;

void main()
{
    vec3 col = texture(uTexture, vTexCoord).rgb;
    FragColor = vec4(col, 1.0);
}
