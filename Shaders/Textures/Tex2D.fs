#version 330 core

out vec4 FragColor;

in vec2 vTexCoord;

void main()
{
    vec2 col = vTexCoord;
    FragColor = vec4(col, 0.0, 1.0);
}
