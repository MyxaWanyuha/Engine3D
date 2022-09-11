#include "spch.h"
#include "Renderer.h"
#include <GLFW/glfw3.h>

void Renderer::Init()
{
    auto glad = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    ASSERT(glad, "Failed to initialize GLAD");
}

void Renderer::SetViewport(int x, int y, int width, int heigth)
{
    glViewport(x, y, width, heigth);
}

void Renderer::Enable(EParam param)
{
    glEnable(param);
}

void Renderer::Disable(EParam param)
{
    glDisable(param);
}

void Renderer::ClearColor(const glm::vec4& color)
{
    glClearColor(color.x, color.y, color.z, color.w);
}

void Renderer::Clear(EBitField field)
{
    glClear(field);
}

void Renderer::Clear(int field)
{
    glClear(field);
}

void Renderer::DrawArrays(uint32_t first, size_t count)
{
    glDrawArrays(GL_TRIANGLES, first, count);
}

void Renderer::DrawElements(size_t size)
{
    GL_CHECK(glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0));
}
