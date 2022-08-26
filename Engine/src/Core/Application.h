#pragma once
#include <memory>
#include <string>

#include "Core/Window.h"
#include "Core/Event.h"
#include "Core/LayerArray.h"

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
    virtual ~Application();

    static Application& Get() { return *s_Instance; }

    auto& GetWindow() { return *m_Window; }
    auto GetNativeWindow() const { return m_Window->GetWindowHandle(); }

    virtual void OnEvent(Event& e);

    void Run();
    virtual void Update(float dt);

    LayerArray& GetLayerArray() { return m_LayerArray; }

private:
    bool OnWindowResize(EventWindowResize& e);
    bool OnWindowClose(EventWindowClose& e);

private:
    std::unique_ptr<Window> m_Window;
    bool m_bIsRunning = true;
    static Application* s_Instance;
    LayerArray m_LayerArray;
    float m_LastFrame = 0.0f;
};

std::unique_ptr<Application> CreateApp(const std::string& name, int width, int heigth);
