#pragma once
#include <GLFW/glfw3.h>
#include "Camera/Camera.h"

class CameraController
{
public:
    CameraController(const EditorCamera& camera);
    void Update(GLFWwindow* window);
    EditorCamera& GetCamera() { return m_Camera; }
private:
    EditorCamera m_Camera;

    float m_MovementSpeed = 1.0f;
    float m_MouseSensitivity = 0.1f;
    float m_Zoom = 45.0f;
};
