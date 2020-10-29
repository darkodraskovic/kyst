#version 330 core
out vec4 FragColor;

in vec2 vTexCoord;

uniform sampler2D uTexture;

void main()
{
    vec3 col = texture(uTexture, vTexCoord).rgb;
    FragColor = vec4(col, 1.0);
}
