#include "spch.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

#include "Render/VertexArray.h"
#include "Render/Shader.h"
#include "Render/Texture.h"
#include "ImGui/ImGuiOpenGL.h"
#include "Camera/Camera.h"
#include "Camera/CameraController.h"
#include "Core/Event.h"

const int c_Width = 1280;
const int c_Height = 720;

struct WindowData
{
    std::function<void(Event&)> CallbackFn;
};

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(c_Width, c_Height, "LearnOpenGL", nullptr, nullptr);
    ASSERT(window, "Failed to create GLFW window");

    glfwMakeContextCurrent(window);

    auto glad = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    ASSERT(glad, "Failed to initialize GLAD");

    EditorUI::Init(window);

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, c_Width, c_Height);

    CameraController cameraController(EditorCamera(45.0f, (float)c_Width / c_Height));
    WindowData windowData;
    windowData.CallbackFn = [&](Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<EventWindowResize>([&](EventWindowResize& e)
        {
            LOG_INFO("W {0}, H {1}", e.Width, e.Height);
            glViewport(0, 0, e.Width, e.Height);
            cameraController.GetCamera().SetAspectRatio(e.Width / e.Height);
            return false;
        });
    };

    glfwSetWindowUserPointer(window, &windowData);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        EventWindowResize e(width, height);
        data.CallbackFn(e);
    });

    glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int keycode)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            EventKeyTyped e(keycode);
            data.CallbackFn(e);
        });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS:
            {
                EventMouseButtonPressed e(button);
                data.CallbackFn(e);
                break;
            }
            case GLFW_RELEASE:
            {
                EventMouseButtonReleased e(button);
                data.CallbackFn(e);
                break;
            }
            }
        });

    glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            EventMouseScrolled e(xOffset, yOffset);
            data.CallbackFn(e);
        });

    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            EventMouseMoved e(xPos, yPos);
            data.CallbackFn(e);
        });

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        switch (action)
        {
        case GLFW_PRESS:
        {
            EventKeyPressed e(key, 0);
            data.CallbackFn(e);
            break;
        }
        case GLFW_RELEASE:
        {
            EventKeyReleased e(key);
            data.CallbackFn(e);
            break;
        }
        case GLFW_REPEAT:
        {
            EventKeyPressed e(key, 1);
            data.CallbackFn(e);
            break;
        }
        }

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
    while (!glfwWindowShouldClose(window))
    {
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glClearColor(color.x, color.y, color.z, color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        EditorUI::Begin();

        ImGui::ShowDemoWindow();
        ImGui::Begin("Settings");
        ImGui::InputFloat4("Color", &color.x);
        ImGui::End();

        cameraController.Update(window);
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
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    EditorUI::Destroy();
    glfwTerminate();
    return 0;
}