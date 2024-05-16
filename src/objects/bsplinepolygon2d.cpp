#include "objects/bsplinepolygon2d.h"

const vec3 BSplinePolygon2D::POLYGON_COLOR = {1.0, 1.0, 1.0};
const vec3 BSplinePolygon2D::CONTROL_POINT_COLOR = {1.0, 1.0, 1.0};

BSplinePolygon2D::BSplinePolygon2D()
    : m_showControlPoints(true),
      m_showPolygon(true),
      m_polygonColor(POLYGON_COLOR),
      m_controlPointColor(CONTROL_POINT_COLOR),
      m_polygonLineWidth(1.0),
      m_controlPointSize(1.0)
{
}

BSplinePolygon2D::~BSplinePolygon2D()
{
}

void BSplinePolygon2D::addControlPoint(const vec2 &point)
{
    m_controlPoints.push_back(point);
}

void BSplinePolygon2D::setControlPoint(int index, const vec2 &point)
{
    m_controlPoints[index] = point;

}

void BSplinePolygon2D::removeControlPoint(int index)
{
    m_controlPoints.erase(m_controlPoints.begin() + index);
}

void BSplinePolygon2D::moveControlPoint(int index, int destinationIndex)
{
    vec2 point = m_controlPoints[index];

    this->removeControlPoint(index);
    m_controlPoints.insert(m_controlPoints.begin() + destinationIndex, point);
}

void BSplinePolygon2D::setControlPointsColor(const vec3 &color)
{
    m_controlPointColor = color;
}

void BSplinePolygon2D::setPolygonColor(const vec3 &color)
{
    m_polygonColor = color;
}

void BSplinePolygon2D::setPolygonLineWidth(float width)
{
    m_polygonLineWidth = width;
}

void BSplinePolygon2D::setControlPointSize(float size)
{
    m_controlPointSize = size;
}

const vec2 &BSplinePolygon2D::getControlPoint(int index) const
{
    return m_controlPoints[index];
}

int BSplinePolygon2D::getSize() const
{
    return m_controlPoints.size();
}

void BSplinePolygon2D::showPolygon(bool flag)
{
    m_showPolygon = flag;
}

void BSplinePolygon2D::showControlPoints(bool flag)
{
    m_showControlPoints = flag;
}

RenderData BSplinePolygon2D::getRenderData()
{
    RenderData data;

    // Setup Flags
    data.DrawVertices = m_showControlPoints;
    data.DrawEdges = m_showPolygon;
    data.DrawPolygons = false;
    data.UseModelMatr = true;
    data.UseViewMatr = true;
    data.UseProjMatr = true;
    data.UseGlobalEdgeColor = true;
    data.UseGlobalVertexColor = true;

    // Setup data

    data.VertexData.reserve(m_controlPoints.size());
    data.Vertices.reserve(m_controlPoints.size());
    for (int i = 0; i < m_controlPoints.size(); i++) {
        data.VertexData.push_back(vec3(m_controlPoints[i], 0.0));
        data.Vertices.push_back({i});
    }

    data.Edges.reserve(m_controlPoints.size() - 1);
    for (int i = 0; i < m_controlPoints.size() - 1; i++) {
        data.Edges.push_back({i, i + 1});
    }

    // Setup Misc Visual values
    data.GlobalEdgeColor = m_polygonColor;
    data.GlobalVertexColor = m_controlPointColor;
    data.EdgeWidth = m_polygonLineWidth;
    data.VertexSize = m_controlPointSize;

    return data;
}

glm::mat4 BSplinePolygon2D::getTransformation()
{
    return this->getModelMatrix();
}
