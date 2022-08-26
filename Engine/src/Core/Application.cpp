#include "spch.h"
#include "Application.h"

#include "Core/Input.h"
#include "Render/Renderer.h"
#include <ImGui/ImGuiOpenGL.h>
#include <imgui.h>
#include <glm/gtx/transform.hpp>

Application* Application::s_Instance;

Application::Application(const std::string& name, int width, int heigth)
{
    ASSERT(s_Instance == nullptr, "Application alredy created!");
    s_Instance = this;
    m_Window = std::make_unique<Window>(name, width, heigth);
    m_Window->SetCallbackFn(BIND_EVENT_FN(Application::OnEvent));

    Renderer::Init();
    Renderer::SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeigth());
    Renderer::Enable(EParam::DepthTest);
    
    EditorUI::Init(m_Window->GetWindowHandle());
}

Application::~Application()
{
    EditorUI::Destroy();
}

void Application::OnEvent(Event& e)
{
    EventDispatcher dispatcher(e);

    dispatcher.Dispatch<EventKeyPressed>([&](EventKeyPressed& e)
        {
            if (e.Key == Key::Escape)
                m_bIsRunning = false;

            static bool bIsCursorVisible = true;
            if (e.Key == Key::LeftAlt)
            {
                if (bIsCursorVisible)
                {
                    glfwSetInputMode(m_Window->GetWindowHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                }
                else
                {
                    glfwSetInputMode(m_Window->GetWindowHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                }
                bIsCursorVisible = !bIsCursorVisible;
            }

            return false;
        });

    dispatcher.Dispatch<EventWindowResize>(BIND_EVENT_FN(Application::OnWindowResize));
    dispatcher.Dispatch<EventWindowClose>(BIND_EVENT_FN(Application::OnWindowClose));

    for (auto it = m_LayerArray.rbegin(); it != m_LayerArray.rend(); ++it)
    {
        (*it)->OnEvent(e);
        if (e.bHandled)
            break;
    }
}

void Application::Run()
{
    while (m_bIsRunning)
    {
        float currentFrame = glfwGetTime();
        auto deltaTime = currentFrame - m_LastFrame;
        m_LastFrame = currentFrame;
        Update(deltaTime);
        EditorUI::Begin();
        for (auto it = m_LayerArray.rbegin(); it != m_LayerArray.rend(); ++it)
        {
            (*it)->Update(deltaTime);
            (*it)->OnImGuiRender();
        }
        EditorUI::End();

        m_Window->SwapBuffers();
        m_Window->PollEvents();
    }
}

void Application::Update(float dt)
{
}

bool Application::OnWindowResize(EventWindowResize& e)
{
    Renderer::SetViewport(0, 0, e.Width, e.Height);
    m_Window->SetWidth(e.Width);
    m_Window->SetHeigth(e.Height);
    return false;
}

bool Application::OnWindowClose(EventWindowClose& e)
{
    m_bIsRunning = false;
    return false;
}
