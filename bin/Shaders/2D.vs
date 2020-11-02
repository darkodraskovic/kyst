#version 330 core

#include Lib/transform.glsl
#include Lib/attribute.glsl

out vec3 vCol;
out vec2 vTexCoord;
out vec3 vPos;

void main()
{
    vCol = aCol;
    vTexCoord = aTexCoord;
    vPos = vec3(aPos.xy, 1);
    gl_Position = uProjection * uView * uModel * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}