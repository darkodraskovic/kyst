#version 330 core

#include Lib/uniform.glsl

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
