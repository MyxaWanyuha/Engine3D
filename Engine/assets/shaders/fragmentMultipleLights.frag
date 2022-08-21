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

struct DirLight {
    vec3 Direction;
  
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};  
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

struct PointLight {
    vec3 Position;
    float Linear;
    float Quadratic;

    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};
#define NR_POINT_LIGHTS 4
const float LightConstant = 1.0;
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir); 

struct SpotLight {
    vec3 Position;
    vec3 Direction;

    float CutOff;
    float OuterCutOff;

    float Linear;
    float Quadratic;

    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};
vec3 CalcSpotLight(SpotLight spotLight, vec3 normal, vec3 FragPosition, vec3 ViewDir);

uniform Material u_Material;
uniform DirLight u_DirLight;
uniform PointLight u_PointLights[NR_POINT_LIGHTS];
uniform SpotLight u_SpotLight;
uniform vec3 u_CameraPosition;

void main()
{
    // properties
    vec3 norm = normalize(v_Normal);
    vec3 viewDir = normalize(u_CameraPosition - v_FragmentPosition);

    // phase 1: Directional lighting
    vec3 result = CalcDirLight(u_DirLight, norm, viewDir);
    // phase 2: Point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(u_PointLights[i], norm, v_FragmentPosition, viewDir);
    // phase 3: Spot light
    result += CalcSpotLight(u_SpotLight, norm, v_FragmentPosition, viewDir);

    color = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.Direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shininess);
    // combine results
    vec3 ambient  = light.Ambient  * vec3(texture(u_Material.Diffuse, v_TexCoord));
    vec3 diffuse  = light.Diffuse  * diff * vec3(texture(u_Material.Diffuse, v_TexCoord));
    vec3 specular = light.Specular * spec * vec3(texture(u_Material.Specular, v_TexCoord));
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.Position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shininess);
    // attenuation
    float distance    = length(light.Position - fragPos);
    float attenuation = 1.0 / (LightConstant + light.Linear * distance + 
  			     light.Quadratic * (distance * distance));
    // combine results
    vec3 ambient  = light.Ambient  * vec3(texture(u_Material.Diffuse, v_TexCoord));
    vec3 diffuse  = light.Diffuse  * diff * vec3(texture(u_Material.Diffuse, v_TexCoord));
    vec3 specular = light.Specular * spec * vec3(texture(u_Material.Specular, v_TexCoord));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight spotLight, vec3 normal, vec3 FragPosition, vec3 ViewDir)
{
    // ambient
    vec3 ambient = spotLight.Ambient * texture(u_Material.Diffuse, v_TexCoord).rgb;
    
    // diffuse 
    vec3 lightDir = normalize(spotLight.Position - FragPosition);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = spotLight.Diffuse * diff * texture(u_Material.Diffuse, v_TexCoord).rgb;
    
    // specular
    vec3 viewDir = normalize(u_CameraPosition - FragPosition);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(ViewDir, reflectDir), 0.0), u_Material.Shininess);
    vec3 specular = spotLight.Specular * spec * texture(u_Material.Specular, v_TexCoord).rgb;
    
    // spotlight (soft edges)
    float theta = dot(lightDir, normalize(-spotLight.Direction)); 
    float epsilon = (spotLight.CutOff - spotLight.OuterCutOff);
    float intensity = clamp((theta - spotLight.OuterCutOff) / epsilon, 0.0, 1.0);
    diffuse  *= intensity;
    specular *= intensity;
    
    // attenuation
    float distance    = length(spotLight.Position - FragPosition);
    float attenuation = 1.0 / (LightConstant + spotLight.Linear * distance + spotLight.Quadratic * (distance * distance));
    ambient  *= attenuation;
    diffuse   *= attenuation;
    specular *= attenuation;
        
    return ambient + diffuse + specular;
}