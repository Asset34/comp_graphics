#include "objects/line.h"

Line::Line(const vec3 &b, const vec3 &e)
    : m_begin(b),
      m_end(e),
      m_color({0, 0, 0})
{
    this->updateCenter();
}

Line::~Line()
{
}

void Line::setBegin(const vec3 &p)
{
    m_begin = p;

    this->updateCenter();
}

void Line::setEnd(const vec3 &p)
{
    m_end = p;

    this->updateCenter();
}

const vec3 &Line::getBegin() const
{
    return m_begin;
}

const vec3 &Line::getEnd() const
{
    return m_end;
}

vec3 Line::getUnit() const
{
    return glm::normalize(m_end - m_begin);
}

void Line::setColor(const vec3 &color)
{
    m_color = color;
}

const vec3 &Line::getColor() const
{
    return m_color;
}

RenderData Line::getRenderData()
{
    RenderData data;

    // Setup Flags
    data.DrawEdges    = true;
    data.DrawPolygons = false;
    data.UseModelMatr = false;
    data.UseViewMatr  = true;
    data.UseProjMatr  = true;

    // Setup Data

    data.Vertices.reserve(2);
    data.Vertices.push_back(m_begin);
    data.Vertices.push_back(m_end);

    data.Edges.push_back({0, 1});

    // Setup Visuals
    data.EdgeColor = m_color;

    return data;
}

glm::mat4 Line::getTransformation()
{
    return this->getModelMatrix();
}

void Line::transformationCallback()
{
    TransformableObj::transformationCallback();

    // Update points
    m_begin = this->getModelMatrix() * vec4(m_begin, 1);
    m_end = this->getModelMatrix() * vec4(m_end, 1);

    // Update center
    this->updateCenter();
}

const vec3 &Line::selfOrigin() const
{
    return m_center;
}

void Line::updateCenter()
{
    vec3 dp = m_end + m_begin;
    m_center = {dp.x / 2.0, dp.y / 2.0, dp.z / 2.0};
}
