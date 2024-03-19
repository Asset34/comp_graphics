#ifndef RENDERER_H_H
#define RENDERER_H_H

#include "shader.h"
#include "scene.h"

class Renderer {
public:
    Renderer();

    void init();
    void render();
    void attachScene(const Scene &scene);

private:
    // Buffers
    unsigned int vbo, vao;

    // Shaders
    const std::string vertexShaderPath = "../shaders/vertex_shader.glsl";
    const std::string fragmentShaderPath = "../shaders/fragment_shader.glsl";
    Shader shader;

    const Scene *m_scene;

};

#endif // RENDERER_H_H