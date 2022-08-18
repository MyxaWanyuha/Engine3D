#include "spch.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

#include "Render/Renderer.h"
#include "Render/VertexArray.h"
#include "Render/Shader.h"
#include "Render/Texture.h"
#include "ImGui/ImGuiOpenGL.h"
#include "Camera/Camera.h"
#include "Camera/CameraController.h"
#include "Core/Event.h"
#include "Core/Window.h"


const int c_Width = 1280;
const int c_Height = 720;

int main()
{
    Window window("Engine Application", c_Width, c_Height);

    Renderer::Init();
    Renderer::SetViewport(0, 0, window.GetWidth(), window.GetHeigth());
    Renderer::Enable(EParam::DepthTest);
    EditorUI::Init(window.GetWindowHandle());
    
    static bool bIsRunning = true;

    CameraController cameraController(EditorCamera(45.0f, (float)c_Width / c_Height));
    window.SetCallbackFn([&](Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<EventWindowResize>([&](EventWindowResize& e)
        {
            Renderer::SetViewport(0, 0, e.Width, e.Height);

            window.SetWidth(e.Width);
            window.SetHeigth(e.Height);

            cameraController.GetCamera().SetAspectRatio(e.Width / e.Height);
            return false;
        });

        dispatcher.Dispatch<EventWindowClose>([&](EventWindowClose& e)
        {
            bIsRunning = false;
            return false;
        });
    });

    /// Rendering ///////////////////////
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

    Shader shader("assets/shaders/vertex.vert", "assets/shaders/fragment.frag");

    VertexArray VAO(/*std::make_shared<IndexBuffer>(indices, sizeof(indices) / sizeof(indices[0])),*/
                    std::make_shared<VertexBuffer>(vertices, sizeof(vertices)),
                    { {DataType::Float, 3, "a_Pos"}, {DataType::Float, 2, "a_TexCoord"}, });

    Texture texture1("assets/textures/container.jpg");
    Texture texture2("assets/textures/awesomeface.png");
    glm::vec4 color{ 0.2f, 0.3f, 0.8f, 1.0f };
    /////////////////////////////////////
    //!glfwWindowShouldClose(window)
    while (bIsRunning)
    {
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        Renderer::ClearColor(color);
        Renderer::Clear(ColorBufer | DepthBuffer);
        EditorUI::Begin();

        ImGui::ShowDemoWindow();
        ImGui::Begin("Settings");
        ImGui::InputFloat4("Color", &color.x);
        ImGui::End();

        cameraController.Update(window.GetWindowHandle());
        shader.Bind();
        shader.SetInt("u_Tex0", 0);
        shader.SetInt("u_Tex1", 1);
        texture1.Bind(0);
        texture2.Bind(1);
        VAO.Bind();

        shader.SetMat4("u_ViewProjection", cameraController.GetCamera().GetViewProjectionMatrix());
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.SetMat4("u_Model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        EditorUI::End();
        window.SwapBuffers();
        window.PollEvents();
    }

    EditorUI::Destroy();

    return 0;
}