#version 330 core

#include ../Lib/define.glsl
#include ../Lib/uniform.glsl
#include ../Lib/matrix.glsl
#include ../Lib/shape.glsl
#include ../Lib/util.glsl

in vec2 vTexCoord;
in vec3 vPos;

vec3 color = vec3(0.2,0.3,0.33);

void main()
{
    vec3 st = vPos;

    float x_pos = 0.5;
    float y_pos = 0.5;
    float r_size = 0.1;
    float r_anchor = 0.5;
    float line_width = 0.03;
    
    for (int i = 0; i < 4; i++) {
        int sign_x = alter_sign(i, 2);
        int sign_y = alter_sign(i, 1);

        float x = x_pos * sign_x;
        float y = y_pos * sign_y;

        st = translate(vec2(x, y)) * st;
        // color.r += rect_fill(st.xy, vec2(r_size - line_width), vec2(r_anchor));
        color.g += rect_stroke(st.xy, vec2(r_size), vec2(r_anchor), line_width);
        st = vPos;

        st = translate(vec2(x, y)) * st;
        color.r += rect_fill(st.xy, vec2(r_size - line_width), vec2(r_anchor));
        // color.r += rect_stroke(st.xy, vec2(r_size), vec2(r_anchor), line_width);
        st = vPos;
    }
    
    gl_FragColor = vec4(color, 1.0);
}
