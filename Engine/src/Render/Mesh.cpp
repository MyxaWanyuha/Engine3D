#include "spch.h"
#include "Mesh.h"
#include "Render/Renderer.h"
#include "Render/Buffer.h"

Mesh::Mesh(std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices, std::vector<std::shared_ptr<Texture>>&& textures)
    : m_Vertices(std::move(vertices)), m_Indices(std::move(indices)), m_Textures(std::move(textures))
{
    SetupMesh();
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

void Mesh::Draw(Shader& shader)
{
    uint32_t diffuseNr = 1;
    uint32_t specularNr = 1;
    uint32_t normalNR = 1;
    uint32_t heightNR = 1;

    for (uint32_t i = 0; i < m_Textures.size(); ++i)
    {
        m_Textures[i]->Bind(i);
        std::string number;
        if (m_Textures[i]->GetName() == s_TextureDiffuse)
        {
            number = std::to_string(diffuseNr++);
        }
        else if(m_Textures[i]->GetName() == s_TextureSpecular)
        {
            number = std::to_string(specularNr++);
        }
        else if (m_Textures[i]->GetName() == s_TextureHeight)
        {
            number = std::to_string(heightNR++);
        }
        else if (m_Textures[i]->GetName() == s_TextureNormal)
        {
            number = std::to_string(normalNR++);
        }
        std::string name = /*"material." + */m_Textures[i]->GetName() + number;
        shader.SetInt(name.c_str(), i);
    }
    glBindVertexArray(m_VAO);
    Renderer::DrawElements(m_Indices.size());
}

Mesh::Mesh(Mesh&& mesh) noexcept
    : m_Vertices(std::move(mesh.m_Vertices)),
      m_Indices(std::move(mesh.m_Indices)),
      m_Textures(std::move(mesh.m_Textures)),
      m_VBO(mesh.m_VBO),
      m_EBO(mesh.m_EBO),
      m_VAO(mesh.m_VAO)
{
    mesh.m_VBO = 0;
    mesh.m_EBO = 0;
    mesh.m_VAO = 0;
}

Mesh& Mesh::operator=(Mesh&& mesh) noexcept
{
    m_Vertices = std::move(mesh.m_Vertices);
    m_Indices = std::move(mesh.m_Indices);
    m_Textures = std::move(mesh.m_Textures);
    m_VBO = mesh.m_VBO;
    m_EBO = mesh.m_EBO;
    m_VAO = mesh.m_VAO;
    mesh.m_VBO = 0;
    mesh.m_EBO = 0;
    mesh.m_VAO = 0;
    return *this;
}

void Mesh::SetupMesh()
{
    glCreateVertexArrays(1, &m_VAO);
    glCreateBuffers(1, &m_VBO);
    glCreateBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

    glBindVertexArray(0);
}
