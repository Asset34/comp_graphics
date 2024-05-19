#include "objects/line3d.h"

const Color Line3D::COLOR_DEFAULT = {0, 0, 0};

Line3D::Line3D(const vec3 &b, const vec3 &e)
    : m_begin(b),
      m_end(e)
{
    this->updateCenter();
    this->initRenderData();
}

void Line3D::setBegin(const vec3 &p)
{
    m_begin = p;
    this->updateCenter();
    this->setUpdated();
}

void Line3D::setEnd(const vec3 &p)
{
    m_end = p;
    this->updateCenter();
    this->setUpdated();
}

const vec3 &Line3D::getBegin() const
{
    return m_begin;
}

const vec3 &Line3D::getEnd() const
{
    return m_end;
}

vec3 Line3D::getUnit() const
{
    return glm::normalize(m_end - m_begin);
}

void Line3D::setColor(const Color &color)
{
    m_color = color;
}

void Line3D::setEndsColor(const Color &color)
{
    m_endsColor = color;
}

void Line3D::setWidth(float width)
{
    m_width = width;
}

void Line3D::setEndsSize(float size)
{
    m_endsSize = size;
}

const RenderData &Line3D::getRenderData()
{
    // Setup Transformation Matrix
    m_renderData.ModelMatrix = this->getModelMatrix();

    // Setup Visual values
    m_renderData.GlobalEdgeColor   = m_color;
    m_renderData.GlobalVertexColor = m_endsColor;
    m_renderData.EdgeWidth         = m_width;
    m_renderData.VertexSize        = m_endsSize;

    // Setup Data

    if (!this->updated()) return m_renderData;

    m_renderData.VertexData[0] = m_begin;
    m_renderData.VertexData[1] = m_end;

    m_renderData.Vertices[0] = {0};
    m_renderData.Vertices[1] = {1};

    m_renderData.Edges[0] = {0, 1};

    return m_renderData;
}

void Line3D::transformationCallback()
{
    TransformableObj3D::transformationCallback();

    // Update points
    m_begin = this->getModelMatrix() * vec4(m_begin, 1);
    m_end = this->getModelMatrix() * vec4(m_end, 1);

    // Update center
    this->updateCenter();
}

const vec3 &Line3D::selfOrigin() const
{
    return m_center;
}

void Line3D::updateCenter()
{
    vec3 dp = m_end + m_begin;
    m_center = {dp.x / 2.0, dp.y / 2.0, dp.z / 2.0};
}

void Line3D::initRenderData()
{
    // Setup Flags
    m_renderData.DrawVertices = true;
    m_renderData.DrawEdges    = true;
    m_renderData.UseViewMatr  = true;
    m_renderData.UseProjMatr  = true;
    m_renderData.UseGlobalVertexColor = true;
    m_renderData.UseGlobalEdgeColor = true;

    // Setup Data sizes
    m_renderData.VertexData.resize(2);
    m_renderData.Vertices.resize(2);
    m_renderData.Edges.resize(1);
}
