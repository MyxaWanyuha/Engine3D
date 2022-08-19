#include "spch.h"
#include "Application.h"

#include "Render/Renderer.h"
#include <ImGui/ImGuiOpenGL.h>
#include <imgui.h>
#include <glm/gtx/transform.hpp>


float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f
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
    m_Window->SetCallbackFn(BIND_EVENT_FN(Application::OnEvent));


    Renderer::Init();
    Renderer::SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeigth());
    Renderer::Enable(EParam::DepthTest);
    
    // TODO to layout
    EditorUI::Init(m_Window->GetWindowHandle());
    m_CameraController = std::make_unique<CameraController>(EditorCamera(45.0f, (float)width / heigth));

    m_LightShader = std::make_unique<Shader>("assets/shaders/vertex2.vert", "assets/shaders/fragmentLight.frag");
    m_CubeShader = std::make_unique<Shader>("assets/shaders/vertex2.vert", "assets/shaders/fragmentMaterialTextures.frag");
    m_Shader = std::make_unique<Shader>("assets/shaders/vertexTexture.vert", "assets/shaders/fragmentTexture.frag");

    /*auto IBO = std::make_shared<IndexBuffer>(indices, sizeof(indices) / sizeof(indices[0]));*/
    auto VBO = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
    auto bufferLayout = BufferLayout{
        {DataType::Float, 3, "a_Pos"},
        {DataType::Float, 2, "a_TexCoord"}, 
        {DataType::Float, 3, "a_Normal"}, };
    
    m_VertexArray = std::make_unique<VertexArray>(VBO, bufferLayout);
    m_TextureContainer = std::make_unique<Texture>("assets/textures/container.jpg");
    m_TextureAwesomeface = std::make_unique<Texture>("assets/textures/awesomeface.png");
    m_TextureContainerDiffuse = std::make_unique<Texture>("assets/textures/container2.png");
    m_TextureContainerSpecular = std::make_unique<Texture>("assets/textures/container2_specular.png");
    m_TextureContainerEmission = std::make_unique<Texture>("assets/textures/matrix.jpg");
}

Application::~Application()
{
    EditorUI::Destroy();
}

void Application::OnEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<EventWindowResize>(BIND_EVENT_FN(Application::OnWindowResize));
    dispatcher.Dispatch<EventWindowClose>(BIND_EVENT_FN(Application::OnWindowClose));

    // TODO to layout
    dispatcher.Dispatch<EventKeyPressed>([&](EventKeyPressed& e)
        {
            if (e.Key == GLFW_KEY_ESCAPE)
                m_bIsRunning = false;

            static bool bIsCursorVisible = true;
            if (e.Key == GLFW_KEY_LEFT_ALT)
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
    dispatcher.Dispatch<EventMouseButtonPressed>([&](EventMouseButtonPressed& e)
        {
            m_CameraController->OnMouseButtonPressed(e.Button);
            return false;
        });

     dispatcher.Dispatch<EventMouseButtonReleased>([&](EventMouseButtonReleased& e)
         {
             m_CameraController->OnMouseButtonReleased(e.Button);
             return false;
         });

    dispatcher.Dispatch<EventMouseMoved>([&](EventMouseMoved& e)
        {
            m_CameraController->OnMouseInput(e.X, e.Y);
            return false;
        });
    dispatcher.Dispatch<EventMouseScrolled>([&](EventMouseScrolled& e)
        {
            m_CameraController->OnMouseScroll(e.YOffset);
            return false;
        });
}

void Application::Run()
{
    while (m_bIsRunning)
    {
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        Renderer::ClearColor(m_BackgroundColor);
        Renderer::Clear(ColorBufer | DepthBuffer);
        EditorUI::Begin();

        static float lastFrame = 0.0f;
        float currentFrame = glfwGetTime();
        auto deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        m_Light.Position.x = cos(currentFrame);
        m_Light.Position.y = sin(currentFrame);

        ImGui::ShowDemoWindow();
        ImGui::Begin("Settings");
        ImGui::DragFloat4("Background color", &m_BackgroundColor.x, 0.01f, 0.0f, 1.0f);
        ImGui::Text("Light");
        ImGui::DragFloat3("Light position", &m_Light.Position.x, 0.01f, 0.0f, 100.0f);
        ImGui::DragFloat3("Light Ambient", &m_Light.Ambient.x, 0.01f, 0.0f, 1.0f);
        ImGui::DragFloat3("Light Diffuse", &m_Light.Diffuse.x, 0.01f, 0.0f, 1.0f);
        ImGui::DragFloat3("Light Specular", &m_Light.Specular.x, 0.01f, 0.0f, 1.0f);
        ImGui::Text("Object");
        ImGui::DragFloat3("Object position", &m_ObjectPosition.x, 0.01f, 0.0f, 100.0f);
        ImGui::DragFloat3("Object Ambient", &m_ObjectMaterial.Ambient.x, 0.01f, 0.0f, 1.0f);
        ImGui::DragFloat3("Object Diffuse", &m_ObjectMaterial.Diffuse.x, 0.01f, 0.0f, 1.0f);
        ImGui::DragFloat3("Object Specular", &m_ObjectMaterial.Specular.x, 0.01f, 0.0f, 1.0f);
        ImGui::DragFloat("Object Shininess", &m_ObjectMaterial.Shininess, 2.0f, 2.0f, 256.0f);
        ImGui::End();
        {
            m_CameraController->Update(m_Window->GetWindowHandle());
            m_Shader->Bind();
            m_Shader->SetInt("u_Tex0", 0);
            m_Shader->SetInt("u_Tex1", 1);

            m_TextureContainer->Bind(0);
            m_TextureAwesomeface->Bind(1);

            m_Shader->SetMat4("u_ViewProjection", m_CameraController->GetCamera().GetViewProjectionMatrix());

            m_VertexArray->Bind();
            for (unsigned int i = 0; i < 10; i++)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i] + glm::vec3(15));
                float angle = 20.0f * i;
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                m_Shader->SetMat4("u_Model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }

        // Cube
        {
            m_CubeShader->Bind();
            m_CubeShader->SetFloat3("u_Light.Position", m_Light.Position);
            m_CubeShader->SetFloat3("u_Light.Ambient", m_Light.Ambient);
            m_CubeShader->SetFloat3("u_Light.Diffuse", m_Light.Diffuse);
            m_CubeShader->SetFloat3("u_Light.Specular", m_Light.Specular);

            m_CubeShader->SetFloat3("u_CameraPosition", m_CameraController->GetCamera().GetPosition());


            m_TextureContainerDiffuse->Bind(0);
            m_TextureContainerSpecular->Bind(1);
            m_TextureContainerEmission->Bind(2);
            m_CubeShader->SetInt("u_Material.Diffuse", 0);
            m_CubeShader->SetInt("u_Material.Specular", 1);
            m_CubeShader->SetInt("u_Material.Emission", 2);
            m_CubeShader->SetFloat("u_Material.Shininess", m_ObjectMaterial.Shininess);

            m_CubeShader->SetMat4("u_ViewProjection", m_CameraController->GetCamera().GetViewProjectionMatrix());

            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_ObjectPosition);
            m_CubeShader->SetMat4("u_Model", model);

            m_VertexArray->Bind();
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        // Light
        {
            m_LightShader->Bind();
            m_LightShader->SetFloat3("u_LightColor", m_Light.Ambient);
            m_LightShader->SetMat4("u_ViewProjection", m_CameraController->GetCamera().GetViewProjectionMatrix());

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, m_Light.Position);
            model = glm::scale(model, glm::vec3(0.2f));
            m_LightShader->SetMat4("u_Model", model);

            m_VertexArray->Bind();
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
