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

    void loadShapeBuffers();
    void loadShapeVertexData();
    void loadShapeIndexData();

    void loadLineBuffers();
    void loadLineVertexData();

    void renderBackground();
    void renderShape();
    void renderLine();

    // Buffers
    unsigned int vbo_shape, ebo_shape, vao_shape;
    unsigned int vbo_line, vao_line;

    Shader m_shader;
    Scene *m_scene;
    
};

#endif // RENDERER_H_H