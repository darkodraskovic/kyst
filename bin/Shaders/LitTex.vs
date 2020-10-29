#version 330 core

#include Lib/transform.glsl
#include Lib/attribute.glsl

out vec3 vFragPos;
out vec3 vFragNorm;
out vec2 vTexCoord;

void main()
{
    vFragPos = mat3(uModel) * aPos;
    vFragNorm = mat3(transpose(inverse(uModel))) * aNorm;
    vTexCoord = aTexCoord.xy;

    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
}
