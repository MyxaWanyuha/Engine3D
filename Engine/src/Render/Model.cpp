#include "spch.h"
#include "Model.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

std::unordered_map<std::string, std::shared_ptr<Texture>> Model::s_Textures;

void Model::Draw(Shader& shader)
{
    for (uint32_t i = 0; i < m_Meshes.size(); i++)
        m_Meshes[i].Draw(shader);
}

void Model::LoadModel(const std::string& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

#ifdef DEBUG
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        LOG_ERROR("Assimp error: {0}", importer.GetErrorString());
        ASSERT(false, "Assimp error!");
    }
#endif

    std::string directory = path.substr(0, path.find_last_of('/'));

    ProcessNode(scene->mRootNode, scene, directory);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene, const std::string& directory)
{
    for (uint32_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_Meshes.push_back(ProcessMesh(mesh, scene, directory));
    }

    for (uint32_t i = 0; i < node->mNumChildren; i++)
        ProcessNode(node->mChildren[i], scene, directory);
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene, const std::string& directory)
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<std::shared_ptr<Texture>> textures;

    for (uint32_t i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;

        vertex.Position.x = mesh->mVertices[i].x;
        vertex.Position.y = mesh->mVertices[i].y;
        vertex.Position.z = mesh->mVertices[i].z;

        if (mesh->HasNormals())
        {
            vertex.Normal.x = mesh->mNormals[i].x;
            vertex.Normal.y = mesh->mNormals[i].y;
            vertex.Normal.z = mesh->mNormals[i].z;
        }

        if (mesh->mTextureCoords[0])
        {
            vertex.TexCoord.x = mesh->mTextureCoords[0][i].x;
            vertex.TexCoord.y = mesh->mTextureCoords[0][i].y;

            vertex.Tangent.x = mesh->mTangents[i].x;
            vertex.Tangent.y = mesh->mTangents[i].y;
            vertex.Tangent.z = mesh->mTangents[i].z;

            vertex.Bitangent.x = mesh->mBitangents[i].x;
            vertex.Bitangent.y = mesh->mBitangents[i].y;
            vertex.Bitangent.z = mesh->mBitangents[i].z;
        }

        vertices.push_back(vertex);
    }

    for (uint32_t i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (uint32_t j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    //if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<std::shared_ptr<Texture>> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, s_TextureDiffuse, directory);
        for (auto& t : diffuseMaps)
            textures.emplace_back(std::move(t));

        std::vector<std::shared_ptr<Texture>> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, s_TextureSpecular, directory);
        for (auto& t : specularMaps)
            textures.emplace_back(std::move(t));

        std::vector<std::shared_ptr<Texture>> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, s_TextureNormal, directory);
        for (auto& t : normalMaps)
            textures.emplace_back(std::move(t));

        std::vector<std::shared_ptr<Texture>> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, s_TextureHeight, directory);
        for (auto& t : heightMaps)
            textures.emplace_back(std::move(t));
    }

    return Mesh(std::move(vertices), std::move(indices), std::move(textures));
}

std::vector<std::shared_ptr<Texture>> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type,
    const std::string& typeName, const std::string& directory)
{
    std::vector<std::shared_ptr<Texture>> textures;
    for (uint32_t i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        auto filename = directory + '/' + str.C_Str();

        auto it = s_Textures.find(filename);
        if (it == s_Textures.end())
        {
            LOG_INFO("Texture load path: {0}", filename);
            s_Textures[filename] = std::make_shared<Texture>(filename, typeName);
        }
        textures.emplace_back(s_Textures[filename]);
    }
    return textures;
}
