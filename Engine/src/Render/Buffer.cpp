#include "spch.h"
#include "Buffer.h"

VertexBuffer::VertexBuffer(float* vertices, uint32_t size)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_ID);
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& vertexBuffer) noexcept
{
    m_ID = vertexBuffer.m_ID;
    vertexBuffer.m_ID = 0;
    return *this;
}

VertexBuffer::VertexBuffer(VertexBuffer&& vertexBuffer) noexcept
    : m_ID(vertexBuffer.m_ID)
{
    vertexBuffer.m_ID = 0;
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_ID);
}

IndexBuffer::IndexBuffer(IndexBuffer&& indexBuffer) noexcept
    : m_ID(indexBuffer.m_ID)
{
    indexBuffer.m_ID = 0;
}
IndexBuffer& IndexBuffer::operator=(IndexBuffer&& indexBuffer) noexcept
{
    m_ID = indexBuffer.m_ID;
    indexBuffer.m_ID = 0;
    return *this;
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
