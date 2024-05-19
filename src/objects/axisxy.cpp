#include "objects/axisxy.h"

const Color AxisXY::COLOR_X = {1.0, 0.0, 0.0};
const Color AxisXY::COLOR_Y = {0.0, 1.0, 0.0};

AxisXY::AxisXY()
{
    this->initRenderData();
}

void AxisXY::setSize(float size)
{
    m_axisx.x = size;
    m_axisy.y = size;

    this->setUpdated();
}

void AxisXY::setWidth(float width)
{
    m_width = width;
}

void AxisXY::setColorX(const Color &color)
{
    m_colorx = color;
}

void AxisXY::setColorY(const Color &color)
{
    m_colory = color;
}

const RenderData &AxisXY::getRenderData()
{
    // Setup Visuals
    m_renderData.EdgeWidth = m_width;

    // Setup Data

    if (!this->updated()) return m_renderData;

    m_renderData.VertexData.resize(4);
    m_renderData.VertexData[0] = {m_center - m_axisx, 0.0};
    m_renderData.VertexData[1] = {m_center + m_axisx, 0.0};
    m_renderData.VertexData[2] = {m_center - m_axisy, 0.0};
    m_renderData.VertexData[3] = {m_center + m_axisy, 0.0};

    m_renderData.Edges.resize(2);
    m_renderData.Edges[0] = {0, 1, m_colorx};
    m_renderData.Edges[1] = {2, 3, m_colory};

    return m_renderData;
}

void AxisXY::initRenderData()
{
    // Setup Flags
    m_renderData.DrawEdges    = true;
    m_renderData.UseModelMatr = true;
    m_renderData.UseViewMatr  = true;
    m_renderData.UseProjMatr  = true;

    // Setup Transformation Matrix
    m_renderData.ModelMatrix = glm::mat4(1); // Identity Matrix
}