#include "spch.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

EditorCamera::EditorCamera(float fieldOfView, float aspectRatio, const glm::vec3& position)
    : m_ProjectionMatrix(glm::perspective(glm::radians(fieldOfView), aspectRatio, c_Near, c_Far)),
      m_ViewProjectionMatrix(m_ProjectionMatrix * m_ViewMatrix),
      m_Position(position),
      m_Yaw(-90.0f),
      m_Pitch(0.0f),
      m_FieldOfView(fieldOfView),
      m_AspectRatio(aspectRatio)
{
    RecalculateAll();
}

void EditorCamera::SetPosition(const glm::vec3& position)
{
    m_Position = position;
    RecalculateAll();
}

void EditorCamera::SetRotationPitch(float pitch)
{
    m_Pitch = pitch;
    RecalculateAll();
}

void EditorCamera::SetRotationYaw(float yaw)
{
    m_Yaw = yaw;
    RecalculateAll();
}

void EditorCamera::SetProjection(float fieldOfView, float aspectRatio)
{
    m_FieldOfView = fieldOfView;
    m_AspectRatio = aspectRatio;
    RecalculateProjectionMatrix();
}

void EditorCamera::SetAspectRatio(float aspectRatio)
{
    m_AspectRatio = aspectRatio;
    RecalculateProjectionMatrix();
}

void EditorCamera::SetFieldOfView(float fieldOfView)
{
    m_FieldOfView = fieldOfView;
    RecalculateProjectionMatrix();
}

void EditorCamera::RecalculateViewProjectionMatrix()
{
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void EditorCamera::RecalculateViewMatrix()
{
    m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    RecalculateViewProjectionMatrix();
}

void EditorCamera::RecalculateProjectionMatrix()
{
    m_ProjectionMatrix = glm::perspective(glm::radians(m_FieldOfView), m_AspectRatio, c_Near, c_Far);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    RecalculateViewProjectionMatrix();
}

void EditorCamera::RecalculateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    front.y = sin(glm::radians(m_Pitch));
    front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Front = glm::normalize(front);
    m_Right = glm::normalize(glm::cross(m_Front, c_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

void EditorCamera::RecalculateAll()
{
    RecalculateCameraVectors();
    RecalculateViewMatrix();
    RecalculateViewProjectionMatrix();
}
