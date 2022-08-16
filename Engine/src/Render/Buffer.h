#pragma once
#include <glad/glad.h>

class VertexBuffer
{
public:
    VertexBuffer(float* vertices, uint32_t size);
    ~VertexBuffer();

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;
    VertexBuffer(VertexBuffer&& vertexBuffer) noexcept;
    VertexBuffer& operator=(VertexBuffer&& vertexBuffer) noexcept;

    void Bind() const;
    void Unbind() const;

private:
    GLuint m_ID;
};

class IndexBuffer
{
public:
    IndexBuffer(uint32_t* indices, uint32_t count);
    ~IndexBuffer();

    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer& operator=(const IndexBuffer&) = delete;
    IndexBuffer(IndexBuffer&& indexBuffer) noexcept;
    IndexBuffer& operator=(IndexBuffer&& indexBuffer) noexcept;

    void Bind() const;
    void Unbind() const;

private:
    GLuint m_ID;
};
