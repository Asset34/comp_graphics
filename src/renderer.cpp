#include "renderer.h"

#include "glad/glad.h"
#include "glfw/glfw3.h"

Renderer::Renderer()
    :m_scene(nullptr)
{
}

void Renderer::init()
{
    // Load glad
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // Configure global state
    glEnable(GL_DEPTH_TEST);
    
    this->loadShaders();
    this->loadBuffers();
}

void Renderer::render()
{
    this->renderBackground();
    this->renderShape();
}

void Renderer::attachScene(Scene &scene)
{
    m_scene = &scene;
}

void Renderer::loadShaders()
{
    m_shader.addVertexShader("../shaders/vertex_shader.glsl");
    m_shader.addFragmentShader("../shaders/fragment_shader.glsl");
    m_shader.link();
}

void Renderer::loadBuffers()
{
    // Generate bufers
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    // Bind buffers
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    
    // Load buffers
    this->loadVertexData();
    this->loadIndicesData();

    // Unbind buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer::loadVertexData()
{
    // Prepare data
    int size = m_scene->getShape().getSize();
    int rawSize = size * 3;
    float data[rawSize];

    int k = 0;
    for(int i = 0; i < size; i++) {
        const vec3 &vertex = m_scene->getShape().getVertex(i);
        data[k] = vertex.x;
        data[k + 1] = vertex.y;
        data[k + 2] = vertex.z;
        
        k += 3;
    }

    // Load data
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
}

void Renderer::loadIndicesData()
{
    // Prepare data
    int size = m_scene->getShape().getPolygonsOverallSize();
    unsigned int data[size];
    int k = 0;
    int polygonsNumber = m_scene->getShape().getPolygonsNumber();
    for (int i = 0; i < polygonsNumber; i++) {
        std::vector<int> indices = m_scene->getShape().getPolygonIndices(i);
        
        for (int j = 0; j < indices.size(); j++) {
            data[k] = indices[j];
            k++;
        }
    }

    // Load data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
}

void Renderer::renderBackground()
{
    vec3 color = m_scene->getBackgroundColor();

    glClearColor(color.x, color.y, color.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::renderShape()
{
    m_shader.use();
    glBindVertexArray(vao);

    // Setup scene matrices
    m_shader.setMat4("model", m_scene->getShape().getModelMatrix());
    m_shader.setMat4("view", m_scene->getViewMatrix());
    m_shader.setMat4("proj", m_scene->getProjectionMatrix());

    int offset = 0;
    for (int i = 0; i < m_scene->getShape().getPolygonsNumber(); i++) {
        vec3 color = m_scene->getShape().getPolygonColor(i);
        m_shader.setVec3("color", color);

        int number = m_scene->getShape().getPolygonSize(i);
        glDrawElements(GL_TRIANGLE_FAN, number, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLint)));

        offset += number;
    }
}
