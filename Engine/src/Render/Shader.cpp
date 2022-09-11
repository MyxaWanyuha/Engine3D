#include "spch.h"
#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

std::string ReadFromFile(const char* path)
{
    std::string result;
    std::ifstream ifile;
    ifile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
#ifdef DEBUG
    try
    {
        ifile.open(path);
        std::stringstream stream;
        // read file's buffer contents into streams
        stream << ifile.rdbuf();
        // close file handlers
        ifile.close();
        result = stream.str();
    }
    catch (std::ifstream::failure e)
    {
        ASSERT(false, "Can't read file!");
    }
#else
    ifile.open(path);
    std::stringstream stream;
    stream << ifile.rdbuf();
    ifile.close();
    result = stream.str();
#endif
    return result;
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
    : m_ID(0)
{
    Init(vertexPath, fragmentPath);
}

Shader::~Shader()
{
    ASSERT(m_ID != 0, "Shader not initialized!");
    glDeleteProgram(m_ID);
}

void Shader::Init(const char* vertexPath, const char* fragmentPath)
{
    ASSERT(m_ID == 0, "Shader already initialized!");
    auto vertexSrc = ReadFromFile(vertexPath);
    auto fragmentSrc = ReadFromFile(fragmentPath);
    const char* vertexSrcPtr = vertexSrc.c_str();
    const char* fragmentSrcPtr = fragmentSrc.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSrcPtr, nullptr);
    glCompileShader(vertexShader);
    // Check vertex shader compile error
    {
        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(vertexShader);

            LOG_ERROR("{0}", infoLog.data());
            ASSERT(false, "Shader compilation failure!");
        }
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSrcPtr, nullptr);
    glCompileShader(fragmentShader);
    // Check vertex shader compile error
    {
        GLint isCompiled = 0;
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            LOG_ERROR("{0}", infoLog.data());
            ASSERT(false, "Shader compilation failure!");
        }
    }

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexShader);
    glAttachShader(m_ID, fragmentShader);
    glLinkProgram(m_ID);
    // Check shader link
    {
        GLint isLinked = 0;
        glGetProgramiv(m_ID, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_ID, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(m_ID);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            LOG_ERROR("{0}", infoLog.data());
            ASSERT(false, "Shader link failure!");
        }
    }

    glDetachShader(m_ID, vertexShader);
    glDetachShader(m_ID, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Bind() const
{
    ASSERT(m_ID != 0, "Shader not initialized!");
    glUseProgram(m_ID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetInt(const std::string& name, int value)
{
    auto location = GetUniformLocation(name);
    glUniform1i(location, value);
}

void Shader::SetFloat(const std::string& name, float value)
{
    auto location = GetUniformLocation(name);
    glUniform1f(location, value);
}

void Shader::SetFloat3(const std::string& name, const glm::vec3& value)
{
    auto location = GetUniformLocation(name);
    glUniform3f(location, value.x, value.y, value.z);
}

void Shader::SetFloat4(const std::string& name, const glm::vec4& value)
{
    auto location = GetUniformLocation(name);
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& value)
{
    auto location = GetUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

int Shader::GetUniformLocation(const std::string& name) const
{
    ASSERT(m_ID != 0, "Shader not initialized!");
    auto it = m_UniformLocationCache.find(name);
    if (it != m_UniformLocationCache.end())
        return it->second;

    auto location = glGetUniformLocation(m_ID, name.c_str());
    m_UniformLocationCache[name] = location;
    return location;
}
