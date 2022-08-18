#pragma once
#include <memory>
#include <string>

#include "Core/Window.h"
#include "Core/Event.h"

#include "Camera/CameraController.h"

#include "Render/VertexArray.h"
#include "Render/Shader.h"
#include "Render/Texture.h"

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
    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<Texture> m_TextureContainer;
    std::unique_ptr<Texture> m_TextureAwesomeface;
    glm::vec4 m_Color = glm::vec4{ 0.2f, 0.3f, 0.8f, 1.0f };
    std::unique_ptr<CameraController> m_CameraController;
};

