#include "spch.h"
#include "VertexArray.h"

VertexArray::VertexArray()
    : m_ID(0)
{
}

void VertexArray::Init(const std::shared_ptr<IndexBuffer>& indexBuffer, const std::shared_ptr<VertexBuffer>& vertexBuffer, const BufferLayout& layout)
{
    ASSERT(m_ID == 0, "Vertex array already initialized!");

    m_IndexBuffer = indexBuffer;
    m_VertexBuffer = vertexBuffer;

    glCreateVertexArrays(1, &m_ID);
    glBindVertexArray(m_ID);
    m_VertexBuffer->Bind();
    int VertexBufferIndexOffset = 0;
    for (const auto& e : layout)
    {
        glEnableVertexAttribArray(VertexBufferIndexOffset);
        glVertexAttribPointer(
            VertexBufferIndexOffset,
            e.Count,
            e.Type,
            e.bNormalized ? GL_TRUE : GL_FALSE,
            layout.GetStride(),
            (const void*)e.Offset);
        ++VertexBufferIndexOffset;
    }
    m_IndexBuffer->Bind();
    glBindVertexArray(0);
}

VertexArray::VertexArray(const std::shared_ptr<IndexBuffer>& indexBuffer, const std::shared_ptr<VertexBuffer>& vertexBuffer, const BufferLayout& layout)
    : m_ID(0)
{
    Init(indexBuffer, vertexBuffer, layout);
}

VertexArray::VertexArray(const std::shared_ptr<VertexBuffer>& vertexBuffer, const BufferLayout& layout)
{
    m_VertexBuffer = vertexBuffer;
    glCreateVertexArrays(1, &m_ID);
    glBindVertexArray(m_ID);
    m_VertexBuffer->Bind();
    int VertexBufferIndexOffset = 0;
    for (const auto& e : layout)
    {
        glEnableVertexAttribArray(VertexBufferIndexOffset);
        glVertexAttribPointer(
            VertexBufferIndexOffset,
            e.Count,
            e.Type,
            e.bNormalized ? GL_TRUE : GL_FALSE,
            layout.GetStride(),
            (const void*)e.Offset);
        ++VertexBufferIndexOffset;
    }
    glBindVertexArray(0);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_ID);
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_ID);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}
