#pragma once
#include <glad/glad.h>

class Texture
{
public:
    Texture(const std::string& path);
    ~Texture();

    uint32_t GetWidth() const { return m_Width; }
    uint32_t GetHeight() const { return m_Height; }

    void Bind(uint32_t slot = 0) const;

private:
    uint32_t m_Width;
    uint32_t m_Height;
    uint32_t m_ID;
};

