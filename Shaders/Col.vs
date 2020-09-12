#version 330 core

#include Lib/transform.glsl

layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
