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
    glm::vec3 Ambient;
    glm::vec3 Diffuse;
    glm::vec3 Specular;
    float Shininess;
};

struct Light
{
    glm::vec3 Position;
    glm::vec3 Ambient;
    glm::vec3 Diffuse;
    glm::vec3 Specular;
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
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<Shader> m_CubeShader;
    std::unique_ptr<Shader> m_LightShader;
    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<Texture> m_TextureContainer;
    std::unique_ptr<Texture> m_TextureAwesomeface;
    std::unique_ptr<Texture> m_TextureContainerDiffuse;
    std::unique_ptr<Texture> m_TextureContainerSpecular;
    std::unique_ptr<Texture> m_TextureContainerEmission;
    
    glm::vec4 m_BackgroundColor = glm::vec4{ 0.2f, 0.3f, 0.8f, 1.0f };

    Light m_Light = { { 0, 0, -2 }, { 0.2f, 0.2f, 0.2f }, { 0.5f, 0.5f, 0.5f }, { 1.0f, 1.0f, 1.0f } };
    
    glm::vec3 m_ObjectPosition = glm::vec3(0, 0, 0);
    Material m_ObjectMaterial = { { 0.0f, 0.0f, 0.37f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, 256.0f };

    std::unique_ptr<CameraController> m_CameraController;
};

