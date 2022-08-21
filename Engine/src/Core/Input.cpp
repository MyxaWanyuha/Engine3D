#include "spch.h"
#include "Input.h"
#include "Core/Application.h"

bool Input::IsKeyPressed(KeyCode key)
{
    auto window = Application::Get().GetNativeWindow();
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool Input::IsMouseButtonPressed(MouseCode button)
{
    auto window = Application::Get().GetNativeWindow();
    return  glfwGetMouseButton(window, button) == GLFW_PRESS;
}

glm::vec2 Input::GetMousePosition()
{
    auto window = Application::Get().GetNativeWindow();
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    return { (float)xpos, (float)ypos };
}

float Input::GetMouseX()
{
    return GetMousePosition().x;
}

float Input::GetMouseY()
{
    return GetMousePosition().y;
}