#include "objects/axisxyz.h"

const Color AxisXYZ::COLOR_X = {1.0, 0.0, 0.0};
const Color AxisXYZ::COLOR_Y = {0.0, 1.0, 0.0};
const Color AxisXYZ::COLOR_Z = {0.0, 0.0, 1.0};

AxisXYZ::AxisXYZ()
{
    this->initRenderData();
}

void AxisXYZ::setSize(float size)
{
    m_axisx.x = size;
    m_axisy.y = size;
    m_axisz.z = size;

    this->setUpdated();
}

void AxisXYZ::setWidth(float width)
{
    m_width = width;
}

void AxisXYZ::setColorX(const Color &color)
{
    m_colorx = color;
}

void AxisXYZ::setColorY(const Color &color)
{
    m_colory = color;
}

void AxisXYZ::setColorZ(const Color &color)
{
    m_colorz = color;
}

const RenderData &AxisXYZ::getRenderData()
{
    // Setup Visuals
    m_renderData.EdgeWidth = m_width;

    // Setup Transformation Matrix
    m_renderData.ModelMatrix = this->getModelMatrix();

    // Setup Data

    if (!this->updated()) return m_renderData;

    m_renderData.VertexData.resize(4);
    m_renderData.VertexData[0] = m_center;
    m_renderData.VertexData[1] = m_axisx;
    m_renderData.VertexData[2] = m_axisy;
    m_renderData.VertexData[3] = m_axisz;

    m_renderData.Edges.resize(3);
    m_renderData.Edges[0] = {0, 1, m_colorx};
    m_renderData.Edges[1] = {0, 2, m_colory};
    m_renderData.Edges[2] = {0, 3, m_colorz};

    return m_renderData;
}

void AxisXYZ::initRenderData()
{
    // Setup flags
    m_renderData.DrawEdges    = true;
    m_renderData.UseModelMatr = true;
    m_renderData.UseViewMatr  = true;
    m_renderData.UseProjMatr  = true;
}
