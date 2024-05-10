#include "objects/axisxy.h"

const vec3 AxisXY::COLOR_X = {1.0, 0.0, 0.0};
const vec3 AxisXY::COLOR_Y = {0.0, 1.0, 0.0};

AxisXY::AxisXY()
    : m_center({0, 0}),
      m_axisx({1, 0}),
      m_axisy({0, 1}),
      m_colorx(COLOR_X),
      m_colory(COLOR_Y),
      m_width(1.0)
{
}

AxisXY::~AxisXY()
{
}

void AxisXY::setSize(float size)
{
    m_axisx.x = size;
    m_axisy.y = size;
}

void AxisXY::setWidth(float width)
{
    m_width = width;
}

void AxisXY::setColorX(const vec3 &color)
{
    m_colorx = color;
}

void AxisXY::setColorY(const vec3 &color)
{
    m_colory = color;
}

RenderData AxisXY::getRenderData()
{
    RenderData data;

    // Setup Flags
    data.DrawEdges = true;
    data.DrawPolygons = false;
    data.UseModelMatr = true;
    data.UseViewMatr = true;
    data.UseProjMatr = true;

    // Setup data

    data.VertexData.reserve(4);
    data.VertexData.push_back({-m_axisx, m_center.y});
    data.VertexData.push_back({m_axisx, m_center.y});
    data.VertexData.push_back({-m_axisy, m_center.x});
    data.VertexData.push_back({m_axisy, m_center.x});

    data.Edges.reserve(2);
    data.Edges.push_back({0, 1, m_colorx});
    data.Edges.push_back({2, 3, m_colory});

    // Setup Misc Visual values
    data.EdgeWidth = m_width;

    return data;
}

glm::mat4 AxisXY::getTransformation()
{
    return this->getModelMatrix();
}
