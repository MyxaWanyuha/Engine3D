#version 450 core
out vec4 color;

in vec3 v_Normal;
in vec3 v_FragmentPosition;

uniform vec3 u_LightColor;

void main()
{
    color = vec4(u_LightColor, 1.0);
}