#version 330 core

#include ../Lib/uniform.glsl
#include ../Lib/define.glsl
#include ../Lib/matrix.glsl
#include ../Lib/shape.glsl

in vec2 vTexCoord;
in vec3 vPos;

vec3 color = vec3(0.2,0.3,0.33);

void main()
{
    vec3 st = vPos;
    float tnl_x = .5;
    float tnl_y = .5;

    for (int i = 0; i < 28; i++) {
        int fct_x = (i/2)%2 == 0 ? 1 : -1;
        float x = tnl_x * fct_x;
        int fct_y = i%2 == 0 ? 1 : -1;
        float y = tnl_y * fct_y;
        float s = 0.1 * i;
        
        // st = scale(vec2(s)) * translate(vec2(x, y)) * st;
        st = scale(vec2(s)) * rotate(uTime * s / 3 * fct_y) * translate(vec2(x, y)) * st;
        color[i%3] += 0.2 * rect_fill(st.xy, vec2(0.5), vec2(0.5)); // pos, size, anchor
        
        st = vPos;
    }
    
    gl_FragColor = vec4(color, 1.0);
}
