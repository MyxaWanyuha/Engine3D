#include "spch.h"
#include "Application.h"

#include "Render/Renderer.h"
#include <ImGui/ImGuiOpenGL.h>
#include <imgui.h>
#include <glm/gtx/transform.hpp>

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
// world space positions of our cubes
glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

Application::Application(const std::string& name, int width, int heigth)
{
    m_Window = std::make_unique<Window>(name, width, heigth);
    m_Window->SetCallbackFn(SBR_BIND_EVENT_FN(Application::OnEvent));

    Renderer::Init();
    Renderer::SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeigth());
    Renderer::Enable(EParam::DepthTest);
    
    // TODO to layout
    EditorUI::Init(m_Window->GetWindowHandle());
    m_CameraController = std::make_unique<CameraController>(EditorCamera(45.0f, (float)width / heigth));

    m_Shader = std::make_unique<Shader>("assets/shaders/vertex.vert", "assets/shaders/fragment.frag");

    m_VertexArray = std::make_unique<VertexArray>(/*std::make_shared<IndexBuffer>(indices, sizeof(indices) / sizeof(indices[0])),*/
        std::make_shared<VertexBuffer>(vertices, sizeof(vertices)),
        BufferLayout{ {DataType::Float, 3, "a_Pos"}, {DataType::Float, 2, "a_TexCoord"}, });

    m_TextureContainer = std::make_unique<Texture>("assets/textures/container.jpg");
    m_TextureAwesomeface = std::make_unique<Texture>("assets/textures/awesomeface.png");
}

Application::~Application()
{
    EditorUI::Destroy();
}

void Application::OnEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<EventWindowResize>(SBR_BIND_EVENT_FN(Application::OnWindowResize));
    dispatcher.Dispatch<EventWindowClose>(SBR_BIND_EVENT_FN(Application::OnWindowClose));
}

void Application::Run()
{
    while (m_bIsRunning)
    {
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        Renderer::ClearColor(m_Color);
        Renderer::Clear(ColorBufer | DepthBuffer);
        EditorUI::Begin();

        ImGui::ShowDemoWindow();
        ImGui::Begin("Settings");
        ImGui::InputFloat4("Color", &m_Color.x);
        ImGui::End();

        m_CameraController->Update(m_Window->GetWindowHandle());
        m_Shader->Bind();
        m_Shader->SetInt("u_Tex0", 0);
        m_Shader->SetInt("u_Tex1", 1);
        m_TextureContainer->Bind(0);
        m_TextureAwesomeface->Bind(1);
        m_VertexArray->Bind();

        m_Shader->SetMat4("u_ViewProjection", m_CameraController->GetCamera().GetViewProjectionMatrix());
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            m_Shader->SetMat4("u_Model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        EditorUI::End();
        m_Window->SwapBuffers();
        m_Window->PollEvents();
    }
}

bool Application::OnWindowResize(EventWindowResize& e)
{
    Renderer::SetViewport(0, 0, e.Width, e.Height);
    m_Window->SetWidth(e.Width);
    m_Window->SetHeigth(e.Height);
    m_CameraController->GetCamera().SetAspectRatio(e.Width / e.Height);
    return false;
}

bool Application::OnWindowClose(EventWindowClose& e)
{
    m_bIsRunning = false;
    return false;
}
