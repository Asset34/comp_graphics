#ifndef SHADER_H_
#define SHADER_H_

#include "glad/glad.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {

private:
    unsigned int vertexId, fragmentId;
    unsigned int id;

public:
    ~Shader();

    void addVertexShader(std::string path);
    void addFragmentShader(std::string path);
    void link();
    void use();
};

#endif // SHADER_H_H