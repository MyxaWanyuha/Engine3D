#pragma once
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "Render/Shader.h"
#include "Render/Texture.h"
#include "Render/VertexArray.h"

struct Vertex
{
    glm::vec3 Position = glm::vec3(0.0f);
    glm::vec3 Normal = glm::vec3(0.0f);
    glm::vec2 TexCoord = glm::vec2(0.0f);
    glm::vec3 Tangent = glm::vec3(0.0f);
    glm::vec3 Bitangent = glm::vec3(0.0f);
};

class Mesh
{
public:
    Mesh(std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices, std::vector<std::shared_ptr<Texture>>&& textures);
    void Draw(Shader& shader);

    ~Mesh();

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    Mesh(Mesh&& mesh) noexcept;
    Mesh& operator=(Mesh&& mesh) noexcept;

private:
    void SetupMesh();

private:
    std::vector<Vertex> m_Vertices;
    std::vector<uint32_t> m_Indices;
    std::vector<std::shared_ptr<Texture>> m_Textures;
    uint32_t m_VBO;
    uint32_t m_EBO;
    uint32_t m_VAO;
};

