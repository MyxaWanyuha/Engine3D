#version 450 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main()
{
    //FragColor = mix(texture(texture_diffuse1, TexCoord), texture(texture_specular1, TexCoord), 0.1);
    FragColor = texture(texture_diffuse1, TexCoord);
}