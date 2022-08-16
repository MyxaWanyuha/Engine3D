#pragma once
#include <glad/glad.h>
#include <memory>
#include "Render/Buffer.h"

enum DataType
{
    Float = GL_FLOAT,
    Int = GL_INT
};

struct BufferElement
{
    BufferElement(DataType type, uint32_t count, const std::string& name, bool normalized = false)
        : Type(type), Count(count), Name(name), bNormalized(normalized)
    {
        switch (type)
        {
        case Float:
            Size = count * sizeof(float);
            break;
        case Int:
            Size = count * sizeof(int);
            break;
        default:
            ASSERT(false, "Unknown DataType!");
            break;
        }
    }

    DataType Type;
    uint32_t Count;
    std::string Name;
    bool bNormalized;
    uint32_t Size;

    uint32_t Offset;
};

class BufferLayout
{
public:
    BufferLayout(const std::initializer_list<BufferElement>& elems)
        : m_Elems(elems)
    {
        size_t offset = 0;
        for (auto& element : m_Elems)
        {
            element.Offset = offset;
            offset += element.Size;
            m_Stride += element.Size;
        }
    }

    auto begin() const { return m_Elems.begin(); }
    auto end() const { return m_Elems.end(); }

    uint32_t GetStride() const { return m_Stride; }

private:
    std::vector<BufferElement> m_Elems;
    uint32_t m_Stride = 0;
};

class VertexArray
{
public:
    VertexArray(const std::shared_ptr<IndexBuffer>& indexBuffer, const std::shared_ptr<VertexBuffer>& vertexBuffer, const BufferLayout& layout);
    ~VertexArray();

    void Bind() const;
    void Unind() const;
private:
    GLuint m_ID;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
    std::shared_ptr<VertexBuffer> m_VertexBuffer;
};

