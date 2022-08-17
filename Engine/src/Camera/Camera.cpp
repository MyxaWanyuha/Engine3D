#include "spch.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float fieldOfView, float width, float height, const glm::vec3& position)
    : m_ProjectionMatrix(glm::perspective(glm::radians(fieldOfView), width / height, c_Near, c_Far)),
      m_ViewMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f))),
      m_ViewProjectionMatrix(m_ProjectionMatrix * m_ViewMatrix),
      m_Position(position),
      m_FieldOfView(fieldOfView),
      m_Width(width),
      m_Height(height)
{
}

void Camera::SetPosition(const glm::vec3& position)
{
    m_Position = position;
    RecalculateViewProjectionMatrix();
}

void Camera::SetRotation(float rotation)
{
    m_Rotation = rotation;
    RecalculateViewProjectionMatrix();
}

void Camera::SetProjection(float fieldOfView, float width, float height)
{
    m_ProjectionMatrix = glm::perspective(glm::radians(fieldOfView), width / height, c_Near, c_Far);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    m_Width = width;
    m_Height = height;
}

void Camera::SetFOV(float fieldOfView)
{
    m_ProjectionMatrix = glm::perspective(glm::radians(fieldOfView), m_Width / m_Height, c_Near, c_Far);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void Camera::RecalculateViewProjectionMatrix()
{
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position)
                        * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

    m_ViewMatrix = glm::inverse(transform);
    m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}
