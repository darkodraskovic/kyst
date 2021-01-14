#version 330 core

#include Lib/uniform.glsl
#include Lib/attribute.glsl
#include Lib/function.glsl

void main()
{
    gl_Position = project3D(aPos);
}
