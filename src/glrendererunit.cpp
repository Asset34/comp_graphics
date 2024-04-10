#include "glrenderer.h"

#include "shaders.h"

GLRenderer::GLRendererUnit::GLRendererUnit(Renderable *r)
    :m_renderable(r)
{
    // Init shader
    m_shader.addVertexShader(Shaders::BASIC_VERTEX_SHADER);
    m_shader.addFragmentShader(Shaders::BASIC_FRAGMENT_SHADER);
    m_shader.link();

    // Init VAO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Get Render Data
    const RenderData data = r->getRenderData();

    // Process Data
    this->loadVertices(data);
    this->loadEdges(data);
    this->loadPolygons(data);

    // Unbind VAO
    glBindVertexArray(0);
}

GLRenderer::GLRendererUnit::~GLRendererUnit()
{
}

void GLRenderer::GLRendererUnit::updateData()
{
    glBindVertexArray(m_vao);
    this->loadVertices(m_renderable->getRenderData());
    glBindVertexArray(0);
}

void GLRenderer::GLRendererUnit::render(const RenderProviderData &data)
{
    // Bind VAO
    glBindVertexArray(m_vao);

    // Activate shader
    m_shader.use();
    
    // Retrieve Render Data
    const RenderData renderData = m_renderable->getRenderData();
    
    // Apply Globals

    if (renderData.UseModelMatr) m_shader.setMat4("model", m_renderable->getTransformation());
    else m_shader.setMat4("model", glm::mat4(1)); // Identity Matrix

    if (renderData.UseViewMatr) m_shader.setMat4("view", data.ViewMatrix);
    else m_shader.setMat4("view", glm::mat4(1)); // Identity Matrix
    
    if (renderData.UseProjMatr) m_shader.setMat4("proj", data.ProjMatrix);
    else m_shader.setMat4("proj", glm::mat4(1)); // Identity Matrix

    // Render
    if (renderData.DrawEdges) this->renderEdges(renderData);
    if (renderData.DrawPolygons) this->renderPolygons(renderData);

    // Unbind VAO
    glBindVertexArray(0);
}

void GLRenderer::GLRendererUnit::loadVertices(const RenderData &data)
{
    // Generate and bind vertex buffer
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    // Process data

    int rawDataSize = data.Vertices.size() * data.VertexSize;
    float rawData[rawDataSize];

    int i = 0;
    for (auto v : data.Vertices) {
        rawData[i] = v.x;
        rawData[i + 1] = v.y;
        rawData[i + 2] = v.z;

        i += data.VertexSize;
    }

    // Load buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(rawData), rawData, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLRenderer::GLRendererUnit::loadEdges(const RenderData &data)
{
    // Generate and bind index buffer
    glGenBuffers(1, &m_eboEdges);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboEdges);

    // Process data

    int rawDataSize = data.Edges.size() * data.EdgeSize;
    float rawData[rawDataSize];

    int i = 0;
    for (auto e : data.Edges) {
        rawData[i] = e.x;
        rawData[i + 1] = e.y;

        i += data.EdgeSize;
    }

    // Load buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rawData), rawData, GL_STATIC_DRAW);

    // Unbind buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLRenderer::GLRendererUnit::loadPolygons(const RenderData &data)
{
    // Generate and bind index buffer
    glGenBuffers(1, &m_eboPolygons);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboPolygons);

    // Process data

    int rawDataSize = 0;
    for (auto p : data.Polygons) {
        rawDataSize += p.Indices.size();
    }
    float rawData[rawDataSize];

    int i = 0;
    for (auto p : data.Polygons) {
        for (int j = 0; j < p.Indices.size(); j++) {
            rawData[i + j] = p.Indices[j];
        }

        i += p.Indices.size();
    }

    // Load buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rawData), rawData, GL_STATIC_DRAW);

    // Unbind buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLRenderer::GLRendererUnit::renderEdges(const RenderData &data)
{
    // Bind index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboEdges);

    // Render
    m_shader.setVec3("color", data.EdgeColor);
    for (auto e : data.Edges) {
        glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (void*)(0));
    }

    // Unbind buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLRenderer::GLRendererUnit::renderPolygons(const RenderData &data)
{
    // Bind index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboPolygons);

    // Render
    unsigned int offset = 0;
    for (auto p : data.Polygons) {
        m_shader.setVec3("color", p.Color);
        glDrawElements(GL_TRIANGLE_FAN, p.Indices.size(), GL_UNSIGNED_INT, (void*)(offset * sizeof(GLint)));

        offset += p.Indices.size();
    }

    // Unbind buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
