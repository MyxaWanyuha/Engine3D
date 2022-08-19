#pragma once
#include <GLFW/glfw3.h>
#include "Camera/Camera.h"

class CameraController
{
public:
    CameraController(const EditorCamera& camera);
    void Update(GLFWwindow* window);
    EditorCamera& GetCamera() { return m_Camera; }
    void OnMouseButtonPressed(int button);
    void OnMouseButtonReleased(int button);
    void OnMouseInput(float xPos, float yPos);
    void OnMouseScroll(float yOffset);
private:
    EditorCamera m_Camera;

    float m_MovementSpeed = 0.1f;
    float m_MouseSensitivity = 0.1f;
    float m_Zoom = 45.0f;

    bool m_bMouseControl = false;
    float m_LastX, m_LastY;
    bool m_bFirstMouse = true;
};
