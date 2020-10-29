#version 330 core
out vec4 FragColor;

in vec2 vTexCoord;

uniform sampler2D uTexture;

void main()
{
    vec3 col = texture(uTexture, vTexCoord).rgb;
    col.y = 0;
    col.z = 0;
    FragColor = vec4(col, 1.0);
}
