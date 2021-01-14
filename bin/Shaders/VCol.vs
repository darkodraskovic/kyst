#version 330 core

#include Lib/uniform.glsl
#include Lib/attribute.glsl
#include Lib/function.glsl

out vec3 vCol;

void main()
{
    gl_Position = project3D(aPos);
    vCol = aCol;
}
