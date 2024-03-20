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

    void testInit();
    void testDraw();

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

    float vertices[12] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[6] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

};

#endif // RENDERER_H_H