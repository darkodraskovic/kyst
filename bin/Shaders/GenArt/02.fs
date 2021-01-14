#version 330 core

#include ../Lib/define.glsl
#include ../Lib/uniform.glsl
#include ../Lib/matrix.glsl
#include ../Lib/shape.glsl
#include ../Lib/function.glsl

in vec2 vTexCoord;
in vec3 vPos;

vec3 color = vec3(0.2,0.3,0.33);

void main()
{
    vec3 st = vPos;
    float tnl_x = .5;
    float tnl_y = .5;

    for (int i = 0; i < 32; i++) {
        float x = tnl_x * alter_sign(i, 2);
        float y = tnl_y * alter_sign(i, 1);
        float s = 0.3 + 0.035 * i;
        float r = s * 1.5 * alter_sign(i,3);
        
        // st = scale(vec2(s)) * translate(vec2(x, y)) * st;
        st = scale(vec2(s)) * rotate(r) * translate(vec2(x, y)) * st;
        color[i%2] += 0.075 * rectFill(st.xy, vec2(0.5), vec2(0.5)); // pos, size, anchor

        st = vPos;
        
        // st = scale(vec2(s)) * rotate(r) * translate(vec2(y, x)) * st;
        // color[i%2] += 0.02 * rectFill(st.xy, vec2(0.5), vec2(0.5)); // pos, size, anchor
        // st = vPos;
    }
    
    tnl_y = 0.01;
    float col_int = 0.4;
    st = translate(vec2(0, -tnl_y)) * st;
    color[2] += col_int * rectFill(st.xy, vec2(2,0.01), vec2(0.5)); // pos, size, anchor
    st = vPos;
    st = translate(vec2(0, tnl_y)) * st;
    color[2] += col_int * rectFill(st.xy, vec2(2,0.01), vec2(0.5)); // pos, size, anchor
    st = vPos;
    color[2] += col_int * rectFill(st.xy, vec2(0.03,2.0), vec2(0.5)); // pos, size, anchor
    
    gl_FragColor = vec4(color, 1.0);
}
