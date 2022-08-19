#version 450 core
out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragmentPosition;

struct Material {
    sampler2D Diffuse;
    sampler2D Specular;
    sampler2D Emission;
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
    vec3 diffuseTextureColor = vec3(texture(u_Material.Diffuse, v_TexCoord));
    vec3 ambient = u_Light.Ambient * diffuseTextureColor;

    // diffuse
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(u_Light.Position - v_FragmentPosition); 
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_Light.Diffuse * diff * diffuseTextureColor;
    
    // specular
    vec3 viewDir = normalize(u_CameraPosition - v_FragmentPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shininess);
    vec3 specular = u_Light.Specular * spec * vec3(texture(u_Material.Specular, v_TexCoord));

    vec3 result = ambient + diffuse + specular + vec3(texture(u_Material.Emission, v_TexCoord));

    color = vec4(result, 1.0);
}
