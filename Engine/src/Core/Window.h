#pragma once
#include <functional>
#include <string>

struct GLFWwindow;
using CallbackFn = std::function<void(struct Event&)>;
class Window
{
public:
    Window(const std::string& name, int width, int heigth);
    ~Window();

    void SetCallbackFn(const CallbackFn& fn) { m_WindowData.Callback = fn; }

    int GetWidth() const { return m_WindowData.Width; }
    void SetWidth(int width) { m_WindowData.Width = width; }

    int GetHeigth() const { return m_WindowData.Heigth; }
    void SetHeigth(int heigth) { m_WindowData.Heigth = heigth; }

    GLFWwindow* GetWindowHandle() { return m_Window; }

    void SwapBuffers() const;
    void PollEvents() const;

private:
    void Init();
    void Shutdown();

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

