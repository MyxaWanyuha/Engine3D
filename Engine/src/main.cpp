#include "spch.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Render/VertexArray.h"
#include "Render/Shader.h"

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    ASSERT(window, "Failed to create GLFW window");

    glfwMakeContextCurrent(window);

    auto glad = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    ASSERT(glad, "Failed to initialize GLAD");

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
    {
        LOG_INFO("Width: {0}, Height: {1}", width, height);
        glViewport(0, 0, width, height);
    });

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        LOG_INFO("key {0}, scancode {1}, action {2}, mods {3}", key, scancode, action, mods);
        if(key == GLFW_KEY_ESCAPE)
        {
            glfwSetWindowShouldClose(window, true);
        }
    });

    /// Rendering ///////////////////////
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    Shader shader("assets/shaders/vertex.vert", "assets/shaders/fragment.frag");

    VertexArray VAO(std::make_shared<IndexBuffer>(indices, sizeof(indices) / sizeof(indices[0])),
                    std::make_shared<VertexBuffer>(vertices, sizeof(vertices)),
                    { {DataType::Float, 3, "aPos"} });
    /////////////////////////////////////
    while (!glfwWindowShouldClose(window))
    {
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glm::vec4 color{ 0.2f, 0.3f, 0.8f, 1.0f };
        glClearColor(color.x, color.y, color.z, color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        
        shader.Bind();
        shader.SetFloat4("color", { 0.0f, greenValue, 0.0f, 1.0f });
        VAO.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}