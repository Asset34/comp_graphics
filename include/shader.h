#ifndef SHADER_H_
#define SHADER_H_

#include "glad/glad.h"
#include "glm/glm.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    ~Shader();

    void addVertexShader(const std::string &path);
    void addFragmentShader(const std::string &path);
    void link();
    void use();

    void setVec3(const std::string &name, const glm::vec3 &vector) const;
    void setMat4(const std::string &name, const glm::mat4 &matrix) const;

private:
    unsigned int m_vertexId, m_fragmentId;
    unsigned int m_id;

};

#endif // SHADER_H_H