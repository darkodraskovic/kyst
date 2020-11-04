#version 330 core

out vec4 FragColor;

in vec2 vTexCoord;

void main()
{
    vec2 col = round(vTexCoord * 5) / 5;
    FragColor = vec4(col, 0.0, 1.0);
}
