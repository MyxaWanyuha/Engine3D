#include "spch.h"
#include "CameraController.h"
#include "Core/Input.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


CameraController::CameraController(const EditorCamera& camera)
    : m_Camera(camera)
{
}

void CameraController::Update(float dt)
{
    if (Input::IsKeyPressed(Key::W))
        MoveForward(dt);
    if (Input::IsKeyPressed(Key::S))
        MoveForward(-1.0f * dt);
    if (Input::IsKeyPressed(Key::D))
        MoveRight(dt);
    if (Input::IsKeyPressed(Key::A))
        MoveRight(-1.0f * dt);
}

void CameraController::OnEvent(Event& e)
{
    EventDispatcher dispatcher(e);

    dispatcher.Dispatch<EventMouseButtonPressed>([&](EventMouseButtonPressed& e)
        {
            OnMouseButtonPressed(e.Button);
            return false;
        });

    dispatcher.Dispatch<EventMouseButtonReleased>([&](EventMouseButtonReleased& e)
        {
            OnMouseButtonReleased(e.Button);
            return false;
        });

    dispatcher.Dispatch<EventMouseMoved>([&](EventMouseMoved& e)
        {
            OnMouseInput(e.X, e.Y);
            return false;
        });
    dispatcher.Dispatch<EventMouseScrolled>([&](EventMouseScrolled& e)
        {
            OnMouseScroll(e.YOffset);
            return false;
        });

    dispatcher.Dispatch<EventWindowResize>([&](EventWindowResize& e)
        {
            if (e.Height == 0) return false;
            GetCamera().SetAspectRatio(e.Width / e.Height);
            return false;
        });
}

void CameraController::MoveForward(float multiplier)
{
    m_Camera.SetPosition(m_Camera.GetPosition() + multiplier * m_MovementSpeed * m_Camera.GetFront());
}

void CameraController::MoveRight(float multiplier)
{
    m_Camera.SetPosition(m_Camera.GetPosition() + multiplier * m_MovementSpeed * m_Camera.GetRight());
}

void CameraController::OnMouseButtonPressed(int button)
{
    if (button == MouseKey::Right)
    {
        m_bMouseControl = true;
        m_bFirstMouse = true;
    }
}

void CameraController::OnMouseButtonReleased(int button)
{
    if (button == MouseKey::Right)
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
