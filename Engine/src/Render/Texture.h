#pragma once
#include <glad/glad.h>

static const std::string s_TextureDiffuse = "texture_diffuse";
static const std::string s_TextureSpecular = "texture_specular";
static const std::string s_TextureNormal = "texture_normal";
static const std::string s_TextureHeight = "texture_height";

class Texture
{
public:
    Texture(const std::string& path, const std::string& name = s_TextureDiffuse);
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture(Texture&& texture) noexcept;
    Texture& operator=(Texture&& texture) noexcept;

    uint32_t GetWidth() const { return m_Width; }
    uint32_t GetHeight() const { return m_Height; }

    void Bind(uint32_t slot = 0) const;

    const std::string& GetName() const { return *m_Name; }
private:
    uint32_t m_Width;
    uint32_t m_Height;
    uint32_t m_ID;
    const std::string* m_Name = &s_TextureDiffuse;
};

