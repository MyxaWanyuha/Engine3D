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
    // Keyboard input
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

void CameraController::OnMouseButtonPressed(int button)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        m_bMouseControl = true;
        m_bFirstMouse = true;
    }
}

void CameraController::OnMouseButtonReleased(int button)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        m_bMouseControl = false;
    }
}

void CameraController::OnMouseInput(float xPos, float yPos)
{
    if (m_bMouseControl == false) return;

    if (m_bFirstMouse)
    {
      m_LastX = xPos;
      m_LastY = yPos;
      m_bFirstMouse = false;
    }

    float xoffset = xPos - m_LastX;
    float yoffset = m_LastY - yPos; // reversed since y-coordinates go from bottom to top

    m_LastX = xPos;
    m_LastY = yPos;

    auto newYaw = m_Camera.GetRotationYaw() + xoffset * m_MouseSensitivity;
    auto newPitch = m_Camera.GetRotationPitch() + yoffset * m_MouseSensitivity;
    
    if (newPitch > 89.0f)
        newPitch = 89.0f;
    if (newPitch < -89.0f)
        newPitch = -89.0f;

    m_Camera.SetRotationPitch(newPitch);
    m_Camera.SetRotationYaw(newYaw);
}

void CameraController::OnMouseScroll(float yOffset)
{
    m_Zoom -= yOffset;
    if (m_Zoom < 1.0f)
        m_Zoom = 1.0f;
    if (m_Zoom > 45.0f)
        m_Zoom = 45.0f;
    m_Camera.SetFieldOfView(m_Zoom);
}
