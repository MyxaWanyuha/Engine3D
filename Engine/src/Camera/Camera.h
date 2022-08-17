#pragma once
#include <glm/glm.hpp>

class EditorCamera
{
public:
    // FOV in degrees
    EditorCamera(float fieldOfView, float aspectRatio, const glm::vec3& position = glm::vec3(0.0f));

    const glm::vec3& GetPosition() const { return m_Position; }
    void SetPosition(const glm::vec3& position);

    float GetRotationPitch() const { return m_Pitch; }
    void SetRotationPitch(float pitch);

    float GetRotationYaw() const { return m_Yaw; }
    void SetRotationYaw(float yaw);

    // FOV in degrees
    void SetProjection(float fieldOfView, float aspectRatio);

    const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
    const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
    const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

    const glm::vec3 GetFront() const { return m_Front; }
    const glm::vec3 GetUp() const { return m_Up; }
    const glm::vec3 GetRight() const { return m_Right; }
private:
    void RecalculateViewProjectionMatrix();
    void RecalculateViewMatrix();
    void RecalculateCameraVectors();
    void RecalculateAll();
private:
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ViewProjectionMatrix;

    glm::vec3 m_Position;
    float m_Yaw;
    float m_Pitch;

    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;

    static constexpr glm::vec3 c_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    static constexpr float c_Near = 0.1f;
    static constexpr float c_Far = 100.f;
};

