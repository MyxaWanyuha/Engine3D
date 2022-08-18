#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

enum EParam
{
    DepthTest = GL_DEPTH_TEST,
    // TODO add other params
};

enum EBitField
{
    ColorBufer = GL_COLOR_BUFFER_BIT,
    DepthBuffer = GL_DEPTH_BUFFER_BIT
};

static int operator|(EBitField left, EBitField right)
{
    return (int)left | (int)right;
}

class Renderer
{
public:
    static void Init();

    static void SetViewport(int x, int y, int width, int heigth);

    static void Enable(EParam param);
    static void Disable(EParam param);

    static void ClearColor(const glm::vec4& color);
    static void Clear(EBitField field);
    static void Clear(int field);

    // TODO
    //static void DrawArrays();
private:


};

