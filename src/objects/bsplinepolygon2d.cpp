#include "objects/bsplinepolygon2d.h"

const Color BSplinePolygon2D::POLYGON_COLOR = {0.0, 0.0, 0.0};
const Color BSplinePolygon2D::CONTROL_POINT_COLOR = {0.0, 0.0, 0.0};

BSplinePolygon2D::BSplinePolygon2D()
{
    this->initRenderData();
}

void BSplinePolygon2D::addControlPoint(const vec2 &point)
{
    m_controlPoints.push_back(point);
    this->setUpdated();
}

void BSplinePolygon2D::setControlPoint(int index, const vec2 &point)
{
    m_controlPoints[index] = point;
    this->setUpdated();    
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

bool BSplinePolygon2D::getPolygonShowStatus() const
{
    return m_showPolygon;
}

bool BSplinePolygon2D::getControlPointsShowStatus() const
{
    return m_showControlPoints;
}

const RenderData &BSplinePolygon2D::getRenderData()
{
    // Setup Flags
    m_renderData.DrawVertices = m_showControlPoints;
    m_renderData.DrawEdges = m_showPolygon;

    // Setup Vertex Data and Vertices
    m_renderData.VertexData.resize(m_controlPoints.size());
    m_renderData.Vertices.resize(m_controlPoints.size());
    for (int i = 0; i < m_controlPoints.size(); i++) {
        m_renderData.VertexData[i] = {m_controlPoints[i], 0.5};
        m_renderData.Vertices[i] = {i};
    }

    // Setup Edges
    m_renderData.Edges.resize(m_controlPoints.size() - 1);
    for (int i = 0; i < m_renderData.Edges.size(); i++) {
        m_renderData.Edges[i] = {i, i + 1};
    }

    // Setup Visual values
    m_renderData.GlobalEdgeColor   = m_polygonColor;
    m_renderData.GlobalVertexColor = m_controlPointColor;
    m_renderData.EdgeWidth         = m_polygonLineWidth;
    m_renderData.VertexSize        = m_controlPointSize;

    return m_renderData;
}

void BSplinePolygon2D::initRenderData()
{
    // Setup Flags
    m_renderData.UseModelMatr = true;
    m_renderData.UseViewMatr = true;
    m_renderData.UseProjMatr = true;
    m_renderData.UseGlobalEdgeColor = true;
    m_renderData.UseGlobalVertexColor = true;

    // Setup Transformation Matrix
    m_renderData.ModelMatrix = glm::mat4(1.0); // Identity Matrix
}
