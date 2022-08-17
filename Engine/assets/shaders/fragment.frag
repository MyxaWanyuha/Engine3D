#version 450 core
out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Tex0;
uniform sampler2D u_Tex1;

void main()
{
    color = mix(texture(u_Tex0, v_TexCoord), texture(u_Tex1, v_TexCoord), 0.2);
}
