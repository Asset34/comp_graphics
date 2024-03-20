#include "shader.h"

#include "glm/gtc/type_ptr.hpp"

Shader::~Shader()
{
    glDeleteShader(m_vertexId);
    glDeleteShader(m_fragmentId);
}

void Shader::addVertexShader(const std::string &path)
{
    // Retrieve shader code from the file
    std::string code;
    std::ifstream file;

    file.open(path);
    std::stringstream stream;
    stream << file.rdbuf();
    file.close();
    code = stream.str();

    // Compile shader
    const char *codeShader = code.c_str();

    m_vertexId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertexId, 1, &codeShader, NULL);
    glCompileShader(m_vertexId);
}

void Shader::addFragmentShader(const std::string &path)
{
    // Retrieve shader code from the file
    std::string code;
    std::ifstream file;

    file.open(path);
    std::stringstream stream;
    stream << file.rdbuf();
    file.close();
    code = stream.str();

    // Compile shader
    const char *codeShader = code.c_str();

    m_fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragmentId, 1, &codeShader, NULL);
    glCompileShader(m_fragmentId);
}

void Shader::link()
{
    m_id = glCreateProgram();
    glAttachShader(m_id, m_vertexId);
    glAttachShader(m_id, m_fragmentId);

    glLinkProgram(m_id);
}

void Shader::use()
{
    glUseProgram(m_id);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &vector) const
{
    int location = glGetUniformLocation(m_id, name.c_str());
    glUniform3f(location, vector.x, vector.y, vector.z);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &matrix) const
{
    int location = glGetUniformLocation(m_id, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
