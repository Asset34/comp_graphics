#include "objects/axisxyz.h"

const vec3 AxisXYZ::COLOR_X = {1.0, 0.0, 0.0};
const vec3 AxisXYZ::COLOR_Y = {0.0, 1.0, 0.0};
const vec3 AxisXYZ::COLOR_Z = {0.0, 0.0, 1.0};

AxisXYZ::AxisXYZ()
    : m_center({0, 0, 0}),
      m_axisx({1, 0, 0}),
      m_axisy({0, 1, 0}),
      m_axisz({0, 0, 1}),
      m_width(1.0)
{
}

AxisXYZ::~AxisXYZ()
{
}

void AxisXYZ::setSize(float size)
{
    m_axisx.x = size;
    m_axisy.y = size;
    m_axisz.z = size;
}

void AxisXYZ::setWidth(float width)
{
    m_width = width;
}

RenderData AxisXYZ::getRenderData()
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
    data.VertexData.push_back(m_center);
    data.VertexData.push_back(m_axisx);
    data.VertexData.push_back(m_axisy);
    data.VertexData.push_back(m_axisz);

    data.Edges.reserve(3);
    data.Edges.push_back({0, 1, COLOR_X});
    data.Edges.push_back({0, 2, COLOR_Y});
    data.Edges.push_back({0, 3, COLOR_Z});

    // Setup Misc Visual values
    data.EdgeWidth = m_width;

    return data;
}

glm::mat4 AxisXYZ::getTransformation()
{
    return this->getModelMatrix();
}
