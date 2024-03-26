#ifndef RENDERER_H_H
#define RENDERER_H_H

#include "shader.h"
#include "scene.h"

class Renderer {
public:
    Renderer();

    void init();
    void render();
    void attachScene(Scene &scene);

private:
    void loadShaders();
    void loadBuffers();
    void loadVertexData();
    void loadIndicesData();

    void renderBackground();
    void renderShape();

    // Buffers
    unsigned int vbo, ebo, vao;

    Shader m_shader;
    Scene *m_scene;

    unsigned int VAO, VBO, EBO;
    
};

#endif // RENDERER_H_H