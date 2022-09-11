#pragma once
#include <vector>
#include "Render/Shader.h"
#include "Render/Mesh.h"
#include <assimp/scene.h>

class Model
{
public:
    Model(const std::string& path)
    {
        LoadModel(path);
    }
    Model() {}

    void LoadModel(const std::string& path);

    void Draw(Shader& shader);

private:
    void ProcessNode(aiNode* node, const aiScene* scene, const std::string& directory);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, const std::string& directory);
    std::vector<std::shared_ptr<Texture>> LoadMaterialTextures(aiMaterial* mat, aiTextureType type,
        const std::string& typeName, const std::string& directory);

private:
    std::vector<Mesh> m_Meshes;

    // <path, texture>
    static std::unordered_map<std::string, std::shared_ptr<Texture>> s_Textures;
};
