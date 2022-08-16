#pragma once

struct GLFWwindow;

class EditorUI
{
public:
    static void Init(GLFWwindow* window);
    static void Destroy();
    static void Begin();
    static void End();
private:

};