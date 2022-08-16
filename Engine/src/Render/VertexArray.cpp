#include "spch.h"
#include "VertexArray.h"

VertexArray::VertexArray(const std::shared_ptr<IndexBuffer>& indexBuffer, const std::shared_ptr<VertexBuffer>& vertexBuffer, const BufferLayout& layout)
{
    m_IndexBuffer = indexBuffer;
    m_VertexBuffer = vertexBuffer;

    glGenVertexArrays(1, &m_ID);
    glBindVertexArray(m_ID);
    m_VertexBuffer->Bind();
    m_IndexBuffer->Bind();
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
}

VertexArray::VertexArray(const std::shared_ptr<VertexBuffer>& vertexBuffer, const BufferLayout& layout)
{
    m_VertexBuffer = vertexBuffer;

    glGenVertexArrays(1, &m_ID);
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
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_ID);
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_ID);
}

void VertexArray::Unind() const
{
    glBindVertexArray(0);
}
