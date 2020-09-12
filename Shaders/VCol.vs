#version 330 core

#include Lib/transform.glsl
#include Lib/attribute.glsl

out vec3 vCol;

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
    vCol = aCol;
}
