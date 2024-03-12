#include "renderer.h"

#include "glad/glad.h"
#include "glfw/glfw3.h"

void Renderer::init()
{
    // Load glad
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    
    // Setup shaders
    shader.addVertexShader(vertexShaderPath);
    shader.addFragmentShader(fragmentShaderPath);
    shader.link();

    // Setup buffers

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // TODO: BufferData
    // glBufferData(GL_ARRAY_BUFFER, sizeof(verticles_triangle), verticles_triangle, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::render()
{
    shader.use();
    glBindVertexArray(vao);
    // TODO: draw
}
