#version 330 core

#include Lib/transform.glsl
#include Lib/attribute.glsl

out vec3 vFragPos;
out vec3 vFragNorm;

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
    vFragPos = mat3(uModel) * aPos;
    vFragNorm = mat3(transpose(inverse(uModel))) * aNorm;
}
