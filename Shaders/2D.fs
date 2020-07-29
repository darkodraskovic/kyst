#version 330 core

uniform vec3 uColor = vec3(0.0);
uniform float uAlpha = 1.0;
uniform float uPctCol = 0.0;
uniform float uPctTex = 0.0;
uniform sampler2D uTexture;

in vec3 vCol;
in vec2 vTexCoord;

out vec4 FragCol;

void main()
{
    vec3 col = mix(uColor, vCol, uPctCol);
    col = mix(col, texture(uTexture,vTexCoord).rgb, uPctTex);
    FragCol = vec4(col, uAlpha);
}
