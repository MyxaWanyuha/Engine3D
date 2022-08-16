#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <unordered_map>

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetInt(const std::string& name, int value);
    void SetFloat(const std::string& name, float value);
    void SetFloat4(const std::string& name, const glm::vec4& value);
    void SetMat4(const std::string& name, const glm::mat4& value);

private:
    int GetUniformLocation(const std::string& name) const;

private:
    GLuint m_ID;
    mutable std::unordered_map<std::string, int> m_UniformLocationCache;
};

