#ifndef RENDERER_H_H
#define RENDERER_H_H

#include "shader.h"

class Renderer {
private:
    // Buffers
    unsigned int vbo, vao;

    // Shaders
    const std::string vertexShaderPath = "../shaders/vertex_shader.glsl";
    const std::string fragmentShaderPath = "../shaders/fragment_shader.glsl";
    Shader shader;

public:
    void init();
    void render();

};

#endif // RENDERER_H_H