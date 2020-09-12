#version 330 core

#include Lib/transform.glsl
#include Lib/attribute.glsl

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
