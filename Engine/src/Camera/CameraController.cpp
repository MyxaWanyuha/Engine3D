#include "spch.h"
#include "CameraController.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

CameraController::CameraController(const EditorCamera& camera)
    : m_Camera(camera)
{
}

// TODO refactor
void CameraController::Update(GLFWwindow* window)
{
    
    //float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_Camera.SetPosition(m_Camera.GetPosition() + m_MovementSpeed * m_Camera.GetFront());
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_Camera.SetPosition(m_Camera.GetPosition() - m_MovementSpeed * m_Camera.GetFront());
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_Camera.SetPosition(m_Camera.GetPosition() + m_Camera.GetRight() * m_MovementSpeed);
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_Camera.SetPosition(m_Camera.GetPosition() - m_Camera.GetRight() * m_MovementSpeed);
}
