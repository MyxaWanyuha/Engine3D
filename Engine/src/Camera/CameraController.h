#pragma once
#include <GLFW/glfw3.h>
#include "Camera/Camera.h"
#include <Core/Event.h>

class CameraController
{
public:
    // TODO default constructor
    CameraController(const EditorCamera& camera);
    EditorCamera& GetCamera() { return m_Camera; }

    void Update(float dt);
    void OnEvent(Event& e);

private:
    // backward == -1
    void MoveForward(float multiplier = 1.0f);
    // left == -1
    void MoveRight(float multiplier = 1.0f);
    void OnMouseButtonPressed(int button);
    void OnMouseButtonReleased(int button);
    void OnMouseInput(float xPos, float yPos);
    void OnMouseScroll(float yOffset);

private:
    EditorCamera m_Camera;

    float m_MovementSpeed = 2.0f;
    float m_MouseSensitivity = 0.1f;
    float m_Zoom = 45.0f;

    bool m_bMouseControl = false;
    float m_LastX, m_LastY;
    bool m_bFirstMouse = true;
};
