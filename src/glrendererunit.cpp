#include "glrenderer.h"
#include "shaders.h"

GLRenderer::GLRendererUnit::GLRendererUnit(RenderableObj *r)
    :m_obj(r)
{
    // Init shader
    m_shader.addVertexShader(Shaders::BASIC_VERTEX_SHADER);
    m_shader.addFragmentShader(Shaders::BASIC_FRAGMENT_SHADER);
    m_shader.link();

    // Init VAO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Associate Id
    m_associatedId = r->getId();

    this->load();
    m_obj->updateAck();

    // Unbind VAO
    glBindVertexArray(0);
}

void GLRenderer::GLRendererUnit::update()
{
    if (!m_obj->updated()) return;

    glBindVertexArray(m_vao);
    
    this->load();
    m_obj->updateAck();

    glBindVertexArray(0);
}

void GLRenderer::GLRendererUnit::render(const GlobalRenderData &data)
{
    // Bind VAO
    glBindVertexArray(m_vao);

    // Activate shader
    m_shader.use();
    
    // Prepare for render with data (global and local)
    if (m_obj->getRenderData().UseModelMatr) {
        m_shader.setMat4("model", m_obj->getRenderData().ModelMatrix);
    } else {
        m_shader.setMat4("model", glm::mat4(1)); // Indentity Matrix
    }
    
    if (m_obj->getRenderData().UseViewMatr) {
        m_shader.setMat4("view", data.ViewMatrix);
    } else {
        m_shader.setMat4("view", glm::mat4(1)); // Indentity Matrix
    }
    
    if (m_obj->getRenderData().UseProjMatr) {
        m_shader.setMat4("proj", data.ProjMatrix);
    } else {
        m_shader.setMat4("proj", glm::mat4(1)); // Indentity Matrix
    }

    this->render();

    // Unbind VAO
    glBindVertexArray(0);
}

int GLRenderer::GLRendererUnit::getAssociatedId()
{
    return m_associatedId;
}

void GLRenderer::GLRendererUnit::load()
{
    const RenderData &data = m_obj->getRenderData();

    this->loadVertexData(data);
    this->loadVertices(data);
    this->loadEdges(data);
    this->loadPolygons(data);
}

void GLRenderer::GLRendererUnit::render()
{
    const RenderData &data = m_obj->getRenderData();

    if (data.DrawVertices) this->renderVertices(data);
    if (data.DrawEdges) this->renderEdges(data);
    if (data.DrawPolygons) this->renderPolygons(data);
}

void GLRenderer::GLRendererUnit::loadVertexData(const RenderData &data)
{
    // Generate and bind vertex buffer
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    // Process data

    int rawDataSize = data.VertexData.size() * RenderData::VERTEX_PURE_SIZE;
    float rawData[rawDataSize];

    int i = 0;
    for (auto v : data.VertexData) {
        rawData[i] = v.x;
        rawData[i + 1] = v.y;
        rawData[i + 2] = v.z;

        i += RenderData::VERTEX_PURE_SIZE;
    }

    // Load buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(rawData), rawData, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLRenderer::GLRendererUnit::loadVertices(const RenderData &data)
{
    // Generate and bind index buffer
    glGenBuffers(1, &m_eboVertices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboVertices);

    // Process data

    int rawDataSize = data.Vertices.size() * RenderData::VERTEX_UNIT_SIZE;
    unsigned int rawData[rawDataSize];

    int i = 0;
    for (auto v : data.Vertices) {
        rawData[i] = v.index;

        i += RenderData::VERTEX_UNIT_SIZE;
    }

    // Load buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rawData), rawData, GL_STATIC_DRAW);

    // Unbind buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLRenderer::GLRendererUnit::loadEdges(const RenderData &data)
{
    // Generate and bind index buffer
    glGenBuffers(1, &m_eboEdges);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboEdges);

    // Process data

    int rawDataSize = data.Edges.size() * RenderData::EDGE_UNIT_SIZE;
    unsigned int rawData[rawDataSize];

    int i = 0;
    for (auto e : data.Edges) {
        rawData[i] = e.begin;
        rawData[i + 1] = e.end;

        i += RenderData::EDGE_UNIT_SIZE;
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
        rawDataSize += p.indices.size();
    }
    unsigned int rawData[rawDataSize];

    int i = 0;
    for (auto p : data.Polygons) {
        for (int j = 0; j < p.indices.size(); j++) {
            rawData[i + j] = p.indices[j];
        }

        i += p.indices.size();
    }

    // Load buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rawData), rawData, GL_STATIC_DRAW);

    // Unbind buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLRenderer::GLRendererUnit::renderVertices(const RenderData &data)
{
    // Bind index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboVertices);

    // Setup visuals
    glPointSize(data.VertexSize);

    // Render
    if (data.UseGlobalVertexColor) {
        m_shader.setVec3("color", data.GlobalVertexColor);

        int n = data.Vertices.size() * RenderData::VERTEX_UNIT_SIZE;
        glDrawElements(GL_POINTS, n, GL_UNSIGNED_INT, (void*)(0));
    } else {
        unsigned int offset = 0;
        for (auto v : data.Vertices) {
            m_shader.setVec3("color", v.color);
            glDrawElements(GL_POINTS, RenderData::VERTEX_UNIT_SIZE, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLint)));
            offset += RenderData::VERTEX_UNIT_SIZE;
        }
    }

    // Unbind buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLRenderer::GLRendererUnit::renderEdges(const RenderData &data)
{
    // Bind index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboEdges);

    // Setup visuals
    glLineWidth(data.EdgeWidth);

    // Render
    if (data.UseGlobalEdgeColor) {
        m_shader.setVec3("color", data.GlobalEdgeColor);

        int n = data.Edges.size() * RenderData::EDGE_UNIT_SIZE;
        glDrawElements(GL_LINES, n, GL_UNSIGNED_INT, (void*)(0));
    } else {
        unsigned int offset = 0;
        for (auto p : data.Edges) {
            m_shader.setVec3("color", p.color);
            glDrawElements(GL_LINES, RenderData::EDGE_UNIT_SIZE, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLint)));
            offset += RenderData::EDGE_UNIT_SIZE;
        }
    }

    // Unbind buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GLRenderer::GLRendererUnit::renderPolygons(const RenderData &data)
{
    // Bind index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboPolygons);

    // Render
    if (data.UseGlobalPolygonColor) {
        m_shader.setVec3("color", data.GlobalPolygonColor);

        int n = 0;
        for (auto p : data.Polygons) {
            n += p.indices.size();
        }
        glDrawElements(GL_TRIANGLE_FAN, n, GL_UNSIGNED_INT, (void*)(0));
    } else {
        unsigned int offset = 0;
        for (auto p : data.Polygons) {
            m_shader.setVec3("color", p.color);
            glDrawElements(GL_TRIANGLE_FAN, p.indices.size(), GL_UNSIGNED_INT, (void*)(offset * sizeof(GLint)));

            offset += p.indices.size();
        }
    }

    // Unbind buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
