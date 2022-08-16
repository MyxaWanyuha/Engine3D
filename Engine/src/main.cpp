#include "spch.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Render/VertexArray.h"

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

    const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    // Check vertex shader compile error
    {
    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

        glDeleteShader(vertexShader);

        LOG_ERROR("{0}", infoLog.data());
        ASSERT(false, "Shader compilation failure!");
    }
    }

    const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
uniform vec4 color;
void main()
{
    FragColor = color;
} 
)";

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    // Check vertex shader compile error
    {
    GLint isCompiled = 0;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
        
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        LOG_ERROR("{0}", infoLog.data());
        ASSERT(false, "Shader compilation failure!");
    }
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Check shader link
    {
    GLint isLinked = 0;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, &infoLog[0]);

        glDeleteProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        LOG_ERROR("{0}", infoLog.data());
        ASSERT(false, "Shader link failure!");
    }
    }

    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

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
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "color");
        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        VAO.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}