#version 330 core

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aTexCoords;

out vec3 vFragPos;
out vec3 vFragNorm;
out vec2 vTexCoords;

void main()
{
    vFragPos = mat3(uModel) * aPos;
    vFragNorm = mat3(transpose(inverse(uModel))) * aNorm;
    vTexCoords = aTexCoords.xy;

    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
}
