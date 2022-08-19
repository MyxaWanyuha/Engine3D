#version 450 core
out vec4 color;

in vec3 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragmentPosition;

struct Material {
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    float Shininess;
}; 

struct Light {
    vec3 Position;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};
uniform Material u_Material;
uniform Light u_Light;
uniform vec3 u_CameraPosition;

void main()
{
    // ambient
    vec3 ambient = u_Light.Ambient * u_Material.Ambient;

    // diffuse
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_Light.Position - v_FragmentPosition); 
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_Light.Diffuse * (diff * u_Material.Diffuse);
    
    // specular
    vec3 viewDir = normalize(u_CameraPosition - v_FragmentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shininess);
    vec3 specular = u_Light.Specular * (u_Material.Specular * spec);

    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0);
}
