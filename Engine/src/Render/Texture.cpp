#include "spch.h"
#include "Texture.h"
#include <stb_image.h>

Texture::Texture(const std::string& path, const std::string& name)
    : m_Name(&name)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    ASSERT(data, "Failed to load image!");

    m_Width = width;
    m_Height = height;

    GLenum internalFormat = 0, dataFormat = 0;
    if (channels == 4)
    {
        internalFormat = GL_RGBA8;
        dataFormat = GL_RGBA;
    }
    else if (channels == 3)
    {
        internalFormat = GL_RGB8;
        dataFormat = GL_RGB;
    }
    ASSERT(internalFormat & dataFormat, "Format not supported!");

    glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTextureStorage2D(m_ID, 1, internalFormat, m_Width, m_Height);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(m_ID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_ID);
}

Texture::Texture(Texture&& texture) noexcept
    : m_ID(texture.m_ID), m_Width(texture.m_Width), m_Height(texture.m_Height), m_Name(texture.m_Name)
{
    texture.m_ID = 0;
    texture.m_Width = 0;
    texture.m_Height = 0;
}

Texture& Texture::operator=(Texture&& texture) noexcept
{
    m_ID = texture.m_ID;
    m_Width = texture.m_Width;
    m_Height = texture.m_Height;
    m_Name = texture.m_Name;
    return *this;
}

void Texture::Bind(uint32_t slot) const
{
    glBindTextureUnit(slot, m_ID);
}
