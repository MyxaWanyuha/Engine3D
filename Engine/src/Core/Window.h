#pragma once
#include "Core/Event.h"
#include <functional>
#include <string>

struct GLFWwindow;
using CallbackFn = std::function<void(Event&)>;
class Window
{
public:
    Window(const std::string& name, int width, int heigth);
    ~Window();

    void Init();
    void Shutdown();

    void SetCallbackFn(const CallbackFn& fn) { m_WindowData.Callback = fn; }

    int GetWidth() const { return m_WindowData.Width; }
    void SetWidth(int width) { m_WindowData.Width = width; }

    int GetHeigth() const { return m_WindowData.Heigth; }
    void SetHeigth(int heigth) { m_WindowData.Heigth = heigth; }

    GLFWwindow* GetWindowHandle() { return m_Window; }

    void SwapBuffers() const;
    void PollEvents() const;
private:
    struct WindowData
    {
        WindowData(const std::string& name, int width, int heigth)
            : Name(name), Width(width), Heigth(heigth) {}

        std::string Name;
        int Width;
        int Heigth;
        CallbackFn Callback;
    } m_WindowData;

    GLFWwindow* m_Window;
};

