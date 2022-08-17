#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
    // FOV in degrees
    Camera(float fieldOfView, float width, float height, const glm::vec3& position = glm::vec3(0.0f));

    const glm::vec3& GetPosition() const { return m_Position; }
    void SetPosition(const glm::vec3& position);

    float GetRotation() const { return m_Rotation; }
    void SetRotation(float rotation);

    // FOV in degrees
    void SetProjection(float fieldOfView, float width, float height);

    // FOV in degrees
    void SetFOV(float fieldOfView);

    const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
    const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
    const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

private:
    void RecalculateViewProjectionMatrix();

private:
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ViewProjectionMatrix;
    
    float m_FieldOfView;
    float m_Width;
    float m_Height;

    glm::vec3 m_Position;
    float m_Rotation = 0.0f;

    static constexpr float c_Near = 0.1f;
    static constexpr float c_Far = 100.f;
};

