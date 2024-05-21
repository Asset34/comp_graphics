#include "objects/bsurfacepolygon.h"

const Color BSurfacePolygon::POLYGON_COLOR = {0.0, 0.0, 0.0};
const Color BSurfacePolygon::CONTROL_POINT_COLOR = {0.0, 0.0, 0.0};
const float BSurfacePolygon::DEFAULT_COLUMN_VALUE = 1;
const float BSurfacePolygon::DEFAULT_ROW_VALUE = 2;
const float BSurfacePolygon::DEFAULT_CONTROL_POINT_VALUE = 5;

BSurfacePolygon::BSurfacePolygon()
{
    this->initRenderData();
}

void BSurfacePolygon::setHeight(int height)
{
    int prevHeight = this->getHeight();
    m_rowValues.resize(height);
    m_controlPointsValues.resize(height);

    if (!prevHeight) {
        for (int i = prevHeight; i < height; i++) {
            m_rowValues[i] = DEFAULT_ROW_VALUE;
            m_controlPointsValues[i].resize(m_columnValues.size(), DEFAULT_CONTROL_POINT_VALUE);
        }
    } else {
        for (int i = prevHeight; i < height; i++) {
            m_rowValues[i] = m_rowValues[prevHeight - 1];
            m_controlPointsValues[i] = m_controlPointsValues[prevHeight - 1];
        }
    }
}

void BSurfacePolygon::setWidth(int width)
{
    int prevWidth = this->getWidth();
    m_columnValues.resize(width);

    if (!prevWidth) {
        for (int j = prevWidth; j < width; j++) {
            m_columnValues[j] = DEFAULT_COLUMN_VALUE;
        }
        for (auto &row : m_controlPointsValues) {
            row.resize(width);
            for (int j = prevWidth; j < width; j++) {
                row[j] = DEFAULT_CONTROL_POINT_VALUE;
            }
        }
    } else {
        for (int j = prevWidth; j < width; j++) {
            m_columnValues[j] = m_columnValues[prevWidth - 1];
        }
        for (auto &row : m_controlPointsValues) {
            row.resize(width);
            for (int j = prevWidth; j < width; j++) {
                row[j] = row[prevWidth - 1];
            }
        }
    }
}

void BSurfacePolygon::setRow(int index, float value)
{
    m_rowValues[index] = value;
}

void BSurfacePolygon::setColumn(int index, float value)
{
    m_columnValues[index] = value;
}

void BSurfacePolygon::setControlPointValue(int row, int column, float value)
{
    m_controlPointsValues[row][column] = value;
}

int BSurfacePolygon::getHeight() const
{
    return m_rowValues.size();
}

int BSurfacePolygon::getWidth() const
{
    return m_columnValues.size();
}

float BSurfacePolygon::getRow(int index) const
{
    return m_rowValues[index];
}

float BSurfacePolygon::getColumn(int index) const
{
    return m_columnValues[index];
}

float BSurfacePolygon::getControlPointValue(int row, int column) const
{
    return m_controlPointsValues[row][column];
}

void BSurfacePolygon::setControlPointsColor(const Color &color)
{
    m_controlPointColor = color;
}

void BSurfacePolygon::setPolygonColor(const Color &color)
{
    m_polygonColor = color;
}

void BSurfacePolygon::setPolygonLineWidth(float width)
{
    m_polygonLineWidth = width;
}

void BSurfacePolygon::setControlPointSize(float size)
{
    m_controlPointSize = size;
}

void BSurfacePolygon::showPolygon(bool flag)
{
    m_showPolygon = flag;
}

void BSurfacePolygon::showControlPoints(bool flag)
{
    m_showControlPoints = flag;
}

bool BSurfacePolygon::getPolygonShowStatus() const
{
    return m_showPolygon;
}

bool BSurfacePolygon::getControlPointsShowStatus() const
{
    return m_showControlPoints;
}

const RenderData &BSurfacePolygon::getRenderData()
{
    // Setup Transformation Matrix
    m_renderData.ModelMatrix = this->getModelMatrix();

    // Setup Flags
    m_renderData.DrawVertices = m_showControlPoints;
    m_renderData.DrawEdges = m_showPolygon;

    // Setup Visual values
    m_renderData.GlobalEdgeColor   = m_polygonColor;
    m_renderData.GlobalVertexColor = m_controlPointColor;
    m_renderData.EdgeWidth         = m_polygonLineWidth;
    m_renderData.VertexSize        = m_controlPointSize;

    // Setup Data

    if (!this->updated()) return m_renderData;

    // m_renderData.VertexData.resize(m_controlPoints.size());
    // m_renderData.Vertices.resize(m_controlPoints.size());
    // for (int i = 0; i < m_controlPoints.size(); i++) {
    //     m_renderData.VertexData[i] = {m_controlPoints[i], 0.5};
    //     m_renderData.Vertices[i] = {i};
    // }

    // m_renderData.Edges.resize(m_controlPoints.size() - 1);
    // for (int i = 0; i < m_renderData.Edges.size(); i++) {
    //     m_renderData.Edges[i] = {i, i + 1};
    // }

    return m_renderData;
}

void BSurfacePolygon::initRenderData()
{
    // Setup Flags
    m_renderData.UseModelMatr = true;
    m_renderData.UseViewMatr = true;
    m_renderData.UseProjMatr = true;
    m_renderData.UseGlobalEdgeColor = true;
    m_renderData.UseGlobalVertexColor = true;
}