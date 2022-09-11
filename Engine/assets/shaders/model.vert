#version 450 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 viewprojection;

void main()
{
    TexCoord = a_TexCoord;
    gl_Position = viewprojection * model * vec4(a_Pos, 1.0);
}