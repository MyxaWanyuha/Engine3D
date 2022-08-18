#include "spch.h"
#include "Window.h"

#include "Core/Event.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Window::Window(const std::string& name, int width, int heigth)
    : m_WindowData(name, width, heigth)
{
    Init();
}

Window::~Window()
{
    Shutdown();
}

void Window::Init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_Window = glfwCreateWindow(m_WindowData.Width, m_WindowData.Heigth, m_WindowData.Name.c_str(), nullptr, nullptr);
    ASSERT(m_Window, "Failed to create GLFW window");

    glfwMakeContextCurrent(m_Window);

    glfwSetWindowUserPointer(m_Window, &m_WindowData);

    glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            EventWindowResize e(width, height);
            data.Callback(e);
        });

    glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            EventKeyTyped e(keycode);
            data.Callback(e);
        });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS:
            {
                EventMouseButtonPressed e(button);
                data.Callback(e);
                break;
            }
            case GLFW_RELEASE:
            {
                EventMouseButtonReleased e(button);
                data.Callback(e);
                break;
            }
            }
        });

    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            EventMouseScrolled e(xOffset, yOffset);
            data.Callback(e);
        });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            EventMouseMoved e(xPos, yPos);
            data.Callback(e);
        });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch (action)
            {
            case GLFW_PRESS:
            {
                EventKeyPressed e(key, 0);
                data.Callback(e);
                break;
            }
            case GLFW_RELEASE:
            {
                EventKeyReleased e(key);
                data.Callback(e);
                break;
            }
            case GLFW_REPEAT:
            {
                EventKeyPressed e(key, 1);
                data.Callback(e);
                break;
            }
            }

        });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            EventWindowClose e;
            data.Callback(e);
        });
}

void Window::Shutdown()
{
    glfwTerminate();
}

void Window::SwapBuffers() const
{
    glfwSwapBuffers(m_Window);
}

void Window::PollEvents() const
{
    glfwPollEvents();
}
