#version 450 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_TexCoord;
layout (location = 2) in vec3 a_Normal;

out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_FragmentPosition;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

void main()
{
    vec4 worldPos = u_Model * vec4(a_Pos, 1.0);
    v_TexCoord = a_TexCoord;
    // TODO to CPU  mat3(transpose(inverse(u_Model)))
    v_Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
    v_FragmentPosition = vec3(worldPos);
    gl_Position = u_ViewProjection * worldPos;
}
