#pragma once
#include <memory>
#include <string>

#include "Core/Window.h"
#include "Core/Event.h"

#include "Camera/CameraController.h"

#include "Render/VertexArray.h"
#include "Render/Shader.h"
#include "Render/Texture.h"

struct Material
{
    glm::vec3 Ambient = { 1.0f, 1.0f, 1.0f };
    glm::vec3 Diffuse = { 1.0f, 1.0f, 1.0f };
    glm::vec3 Specular = { 1.0f, 1.0f, 1.0f };
    float Shininess = 1.0f;
};

struct DirLight
{
    glm::vec3 Direction = { -0.1f, -0.1f, -0.1f };

    glm::vec3 Ambient = { 1.0f, 1.0f, 1.0f };
    glm::vec3 Diffuse = { 1.0f, 1.0f, 1.0f };
    glm::vec3 Specular = { 1.0f, 1.0f, 1.0f };
};

struct PointLight
{
    glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
    float Linear = 0.1f;
    float Quadratic = 0.5f;

    glm::vec3 Ambient = { 1.0f, 1.0f, 1.0f };
    glm::vec3 Diffuse = { 1.0f, 1.0f, 1.0f };
    glm::vec3 Specular = { 1.0f, 1.0f, 1.0f };
};
#define NR_POINT_LIGHTS 4

struct SpotLight
{
    glm::vec3 Position;
    glm::vec3 Direction;

    float CutOff = glm::cos(glm::radians(12.0f));
    float OuterCutOff = glm::cos(glm::radians(17.0f));

    float Linear = 0.1f;
    float Quadratic = 0.5f;

    glm::vec3 Ambient = { 1.0f, 1.0f, 1.0f };
    glm::vec3 Diffuse = { 1.0f, 1.0f, 1.0f };
    glm::vec3 Specular = { 1.0f, 1.0f, 1.0f };
};

class Application
{
public:
    Application(const std::string& name, int width, int heigth);
    ~Application();

    void OnEvent(Event& e);

    void Run();

private:
    bool OnWindowResize(EventWindowResize& e);
    bool OnWindowClose(EventWindowClose& e);

private:
    std::unique_ptr<Window> m_Window;
    bool m_bIsRunning = true;

    // TODO to layout
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<Shader> m_CubeShader;
    std::shared_ptr<Shader> m_LightShader;
    std::shared_ptr<Shader> m_MultipleLightsShader;
    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<Texture> m_TextureContainer;
    std::unique_ptr<Texture> m_TextureAwesomeface;
    std::unique_ptr<Texture> m_TextureContainerDiffuse;
    std::unique_ptr<Texture> m_TextureContainerSpecular;
    std::unique_ptr<Texture> m_TextureContainerEmission;
    
    glm::vec4 m_BackgroundColor = glm::vec4{ 0.2f, 0.3f, 0.8f, 1.0f };

    SpotLight m_SpotLight;
    PointLight m_PointLights[NR_POINT_LIGHTS];
    glm::vec3 m_PointLightPositions[NR_POINT_LIGHTS] = {
        glm::vec3(0.7f,  0.2f,  2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
    };
    DirLight m_DirLight;

    glm::vec3 m_ObjectPosition = glm::vec3(0, 0, 0);
    Material m_ObjectMaterial = { { 0.0f, 0.0f, 0.37f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, 256.0f };

    std::unique_ptr<CameraController> m_CameraController;
};

