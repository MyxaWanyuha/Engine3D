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

struct Light
{
    vec3 Direction;
    vec3 Position;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

    float CutOff;
    float OuterCutOff;
};
const float LightConstant = 1.0;

uniform Material u_Material;
uniform Light u_Light;
uniform vec3 u_CameraPosition;

void main()
{
    vec3 lightDir = normalize(u_Light.Position - v_FragmentPosition);//normalize(-u_Light.Direction);//
    float theta = dot(lightDir, normalize(-u_Light.Direction));
    float epsilon   = u_Light.CutOff - u_Light.OuterCutOff;
    float intensity = clamp((theta - u_Light.OuterCutOff) / epsilon, 0.0, 1.0);
    if(theta > u_Light.OuterCutOff) 
    {
        // ambient
        vec3 diffuseTextureColor = vec3(texture(u_Material.Diffuse, v_TexCoord));
        vec3 ambient = u_Light.Ambient * diffuseTextureColor;

        // diffuse
        vec3 norm = normalize(v_Normal);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = u_Light.Diffuse * diff * diffuseTextureColor;
        
        // specular
        vec3 viewDir = normalize(u_CameraPosition - v_FragmentPosition);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shininess);
        vec3 specular = u_Light.Specular * spec * vec3(texture(u_Material.Specular, v_TexCoord));
        vec3 result = ambient + diffuse * intensity + specular * intensity;//+ vec3(texture(u_Material.Emission, v_TexCoord));
        color = vec4(result, 1.0);
    }
    else  // else, use ambient light so scene isn't completely dark outside the spotlight.
        color = vec4(u_Light.Ambient * vec3(texture(u_Material.Diffuse, v_TexCoord)), 1.0);
}
