#pragma once
#include <glad/glad.h>

class VertexBuffer
{
public:
    VertexBuffer(float* vertices, uint32_t size);
    ~VertexBuffer();

    void Bind();
    void Unbind();

private:
    GLuint m_ID;
};

class IndexBuffer
{
public:
    IndexBuffer(uint32_t* indices, uint32_t count);
    ~IndexBuffer();

    void Bind();
    void Unbind();

private:
    GLuint m_ID;
};
