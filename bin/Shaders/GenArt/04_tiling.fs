#version 330 core

#include ../Lib/define.glsl
#include ../Lib/matrix.glsl
#include ../Lib/shape.glsl
#include ../Lib/uniform.glsl

uniform float uPctCol = 0.0;
uniform float uPctTex = 0.0;
uniform sampler2D uTexture;

in vec3 vPos;
in vec2 vTexCoord;
in vec3 vCol;
out vec4 FragCol;

vec3 color = vec3(0.2,0.3,0.33);

void main()
{
    vec3 pt = vec3(vTexCoord.xy, 1);
    
    vec2 tilecount = vec2(6.0, 3.0);
    pt.xy = fract(pt.xy * tilecount);
    
    pt = translate(vec2(0.5)) * pt;
    pt = rotate(uTime) * pt;
    color.g += rect_fill(pt.xy, vec2(0.2), vec2(0.5));
    
    FragCol = vec4(color, uAlpha);
}
