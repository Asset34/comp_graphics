#include "shader.h"

Shader::Shader()
{
    id = glCreateProgram();
}

Shader::~Shader()
{
    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
}

void Shader::addVertexShader(std::string path)
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

    fragmentId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fragmentId, 1, &codeShader, NULL);
    glCompileShader(fragmentId);

    // Attach shader
    glAttachShader(id, fragmentId);
}

void Shader::addFragmentShader(std::string path)
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

    vertexId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexId, 1, &codeShader, NULL);
    glCompileShader(vertexId);

    // Attach shader
    glAttachShader(id, vertexId);
}

void Shader::link()
{
    glLinkProgram(id);
}

void Shader::use()
{
    glUseProgram(id);
}
