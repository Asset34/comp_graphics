#include "objects/bsurface.h"

#include <iostream>

const Color BSurface::COLOR_DEFAULT = {0, 0, 0};

BSurface::BSurface()
{
    this->initRenderData();
}

void BSurface::setAutocompute(bool value)
{
    m_autoCompute = value;
}

void BSurface::compute()
{
    this->computeBorders();
    this->updateAllSegments();

    this->setUpdated();
}

void BSurface::setControlPoints(const BSurfacePolygon &polygon)
{
    m_controlPoints = polygon.getControlPoints();

    if (m_autoCompute) {
        this->updateOrders();
        this->updateWKnots();
        this->updateUKnots();
        this->computeBorders();
        this->updateAllSegments();

        this->setUpdated();
    }
}

void BSurface::defineWKnots(const std::vector<float> &knots)
{
    m_wknots = knots;

    if (m_autoCompute) {
        // TODO
        this->computeBorders();
        this->updateAllSegments();

        this->setUpdated();
    }
}

void BSurface::defineWKnotsUniform(float step)
{
    m_wknots.resize(m_controlPoints.size() + m_worder);

    float value = 0;
    for (int i = 0; i < m_wknots.size(); i++) {
        m_wknots[i] = value;
        value += step;
    }

    if (m_autoCompute) {
        // TODO
        this->computeBorders();
        this->updateAllSegments();

        this->setUpdated();
    }   
}

void BSurface::defineWKnotsOpenUniform(float step)
{
    m_wknots.resize(m_controlPoints.size() + m_worder);

    // Begin
    for (int i = 0; i < m_worder; i++) {
        m_wknots[i] = 0;
    }

    // Intermediate
    float value = 0;
    for (int i = m_worder; i < m_wknots.size() - m_worder; i++) {
        value += step;
        m_wknots[i] = value;
    }

    // End
    value += step;
    for (int i = m_wknots.size() - m_worder; i < m_wknots.size(); i++) {
        m_wknots[i] = value;
    }

    if (m_autoCompute) {
        // TODO
        this->computeBorders();
        this->updateAllSegments();

        this->setUpdated();
    }
}

void BSurface::setWKnot(int index, float knot)
{
    m_wknots[index] = knot;

    if (m_autoCompute) {
        // TODO
        this->computeBorders();
        this->updateAllSegments();

        this->setUpdated();
    }
}

float BSurface::getWKnot(int index) const
{
    return m_wknots[index];
}

int BSurface::getWKnotNumber() const
{
    return m_wknots.size();
}

void BSurface::defineUKnots(const std::vector<float> &knots)
{
    m_uknots = knots;

    if (m_autoCompute) {
        // TODO
        this->computeBorders();
        this->updateAllSegments();

        this->setUpdated();
    }
}

void BSurface::defineUKnotsUniform(float step)
{
    m_uknots.resize(m_controlPoints[0].size() + m_uorder);

    float value = 0;
    for (int i = 0; i < m_uknots.size(); i++) {
        m_uknots[i] = value;
        value += step;
    }

    if (m_autoCompute) {
        // TODO
        this->computeBorders();
        this->updateAllSegments();

        this->setUpdated();
    }  
}

void BSurface::defineUKnotsOpenUniform(float step)
{
    m_uknots.resize(m_controlPoints[0].size() + m_uorder);

    // Begin
    for (int i = 0; i < m_uorder; i++) {
        m_uknots[i] = 0;
    }

    // Intermediate
    float value = 0;
    for (int i = m_uorder; i < m_uknots.size() - m_uorder; i++) {
        value += step;
        m_uknots[i] = value;
    }

    // End
    value += step;
    for (int i = m_uknots.size() - m_uorder; i < m_uknots.size(); i++) {
        m_uknots[i] = value;
    }

    if (m_autoCompute) {
        // TODO
        this->computeBorders();
        this->updateAllSegments();

        this->setUpdated();
    }
}

void BSurface::setUKnot(int index, float knot)
{
    m_uknots[index] = knot;

    if (m_autoCompute) {
        // TODO
        this->computeBorders();
        this->updateAllSegments();

        this->setUpdated();
    }
}

float BSurface::getUKnot(int index) const
{
    return m_uknots[index];
}

int BSurface::getUKnotNumber() const
{
    return m_uknots.size();
}

void BSurface::setWDegree(int degree)
{
    m_worder = degree + 1;

    if (m_autoCompute) {
        // TODO
        this->computeBorders();
        this->updateWKnots();
        this->updateAllSegments();

        this->setUpdated();
    }
}

int BSurface::getWDegree() const
{
    return m_worder - 1;
}

int BSurface::getWDegreeMax() const
{
    int degree = this->getWOrderMax();

    if (degree) return degree;
    else return 0;
}

void BSurface::setUDegree(int degree)
{
    m_uorder = degree + 1;

    if (m_autoCompute) {
        // TODO
        this->computeBorders();
        this->updateUKnots();
        this->updateAllSegments();

        this->setUpdated();
    }
}

int BSurface::getUDegree() const
{
    return m_uorder - 1;
}

int BSurface::getUDegreeMax() const
{
    int degree = this->getUOrderMax() - 1;

    if (degree) return degree;
    else return 0;
}

int BSurface::getWOrderMax() const
{
    return m_controlPoints.size();
}

int BSurface::getUOrderMax() const
{
    if (!m_controlPoints.size()) return 0;

    return m_controlPoints[0].size();
}

void BSurface::setWRenderStep(float step)
{
    m_wrenderStep = step;

    if (m_autoCompute) {
        this->updateAllSegments();

        this->setUpdated();
    }
}

float BSurface::getWRenderStep() const
{
    return m_wrenderStep;
}

void BSurface::setURenderStep(float step)
{
    m_urenderStep = step;

    if (m_autoCompute) {
        this->updateAllSegments();

        this->setUpdated();
    }
}

float BSurface::getURenderStep() const
{
    return m_urenderStep;
}

void BSurface::setColor(const Color &color)
{
    m_color = color;
}

const vec3 &BSurface::getColor() const
{
    return m_color;
}

void BSurface::setLineWidth(float width)
{
    m_lineWidth = width;
}

const RenderData &BSurface::getRenderData()
{
    // Setup Transformation Matrix
    m_renderData.ModelMatrix = this->getModelMatrix();

    // Setup Visual values
    m_renderData.GlobalEdgeColor = m_color;
    m_renderData.EdgeWidth = m_lineWidth;

    if (!this->updated()) return m_renderData;

    // Compute sizes for data
    
    int fullSplineSize = 0;
    for (int s = m_leftSegment; s <= m_rightSegment; s++) {
        if (m_segments[m_bottomSegment][s].splines.size()) {
            fullSplineSize += m_segments[m_bottomSegment][s].splines[0].size();
        }
    }

    int totalNumberOfSplines = 0;
    for (int s = m_bottomSegment; s <= m_topSegment; s++) {
        totalNumberOfSplines += m_segments[s][m_leftSegment].splines.size();
    }

    int fullVertexDataSize = fullSplineSize * totalNumberOfSplines;
    int fullEdgeDataSize = (fullSplineSize - 1) * totalNumberOfSplines;
    if (fullEdgeDataSize < 0) fullEdgeDataSize = 0;

    // Setup Data

    m_renderData.VertexData.resize(fullVertexDataSize);
    m_renderData.Vertices.resize(fullVertexDataSize);
    m_renderData.Edges.resize(fullEdgeDataSize + 1);

    int index = 0;
    int edgeIndex = 0;
    int rowHeight;
    int splineSize;
    for (int row = m_bottomSegment; row <= m_topSegment; row++) {
        rowHeight = m_segments[row][m_leftSegment].splines.size();
        for (int i = 0; i < rowHeight; i++) {
            for (int s = m_leftSegment; s <= m_rightSegment; s++) {
                splineSize = m_segments[row][s].splines[i].size();
                for (int t = 0; t < splineSize; t++) {
                    m_renderData.VertexData[index] = m_segments[row][s].splines[i][t];
                    m_renderData.Vertices[index] = {index};

                    m_renderData.Edges[edgeIndex] = {index, index + 1};

                    index++;
                    edgeIndex++;
                }

                if (s == m_rightSegment) {
                    edgeIndex--;
                }
            }
        }
    }

    m_renderData.Edges.erase(m_renderData.Edges.end());

    return m_renderData;
}

void BSurface::computeBorders()
{
    m_leftSegment = m_uorder - 1;
    m_rightSegment = m_uknots.size() - m_uorder - 1;

    m_bottomSegment = m_worder - 1;
    m_topSegment = m_wknots.size() - m_worder - 1;
}

void BSurface::updateWKnots()
{
    int diff = m_controlPoints.size() + m_worder - m_wknots.size();

    if (diff > 0) {
        float knotvalue = m_wknots.back() + 1;
        for (int i = 0; i < diff; i++) {
            m_wknots.push_back(knotvalue);
        }
    } else if (diff < 0) {
        for (int i = 0; i < -diff; i++) {
            m_wknots.pop_back();
        }
    }

    this->computeBorders();
}

void BSurface::updateUKnots()
{
    if (!m_controlPoints.size()) return;

    int diff = m_controlPoints[0].size() + m_uorder - m_uknots.size();

    if (diff > 0) {
        float knotvalue = m_uknots.back() + 1;
        for (int i = 0; i < diff; i++) {
            m_uknots.push_back(knotvalue);
        }
    } else if (diff < 0) {
        for (int i = 0; i < -diff; i++) {
            m_uknots.pop_back();
        }
    }

    this->computeBorders();
}

void BSurface::updateOrders()
{
    if (m_uorder > this->getUOrderMax()) m_uorder = this->getUOrderMax();
    if (m_worder > this->getWOrderMax()) m_worder = this->getWOrderMax();
}

void BSurface::updateAllSegments()
{
    // Prepare segments
    m_segments.clear();
    m_segments.resize(m_wknots.size() - 1);
    for (auto &row : m_segments) {
        row.resize(m_uknots.size() - 1);
    }

    // Update segments
    for (int i = m_leftSegment; i <= m_rightSegment; i++) {
        for (int j = m_bottomSegment; j <= m_topSegment; j++) {
            this->updateSegment(j, i);
        }
    }
}

void BSurface::updateSegment(int indexw, int indexu)
{
    // Prepare segment
    m_segments[indexw][indexu].splines.clear();

    // Define starting basis indexes
    int left = indexu - m_uorder + 1;
    int bottom = indexw - m_worder + 1;

    // Define values range
    float umin = m_uknots[indexu];
    float umax = m_uknots[indexu + 1];
    float wmin = m_wknots[indexw];
    float wmax = m_wknots[indexw + 1];

    // Main loop
    vec3 value;
    int k = 0;
    for (float w = wmin; w < wmax; w += m_wrenderStep) {
        // Prepare subsegment
        m_segments[indexw][indexu].splines.push_back(std::vector<vec3>(0));

        // Prepare intermediate control points vector
        m_intermediateControlPoints.clear();
        m_intermediateControlPoints.resize(2 * m_uorder - 1);

        // Find all active intermediate control points
        for (int c = 0; c < m_intermediateControlPoints.size(); c++) {
            m_intermediateControlPoints[c] = this->computeIntermediateControlPoint(indexw, bottom, left + c, w);
        }

        // Compute value
        for (float u = umin; u < umax; u += m_urenderStep) {
            value = this->computeSegment(indexu, left, u);
            m_segments[indexw][indexu].splines[k].push_back(value);
        }

        k++;
    }
}

vec3 BSurface::computeSegment(int indexu, int basisBegin, float u)
{
    // Setup initial basis vector
    int size = 2 * m_uorder - 1;
    std::vector<float> basis(size, 0);
    basis[indexu - basisBegin] = 1;

    // Compute basis
    float term1, term2;
    float delta1, delta2;
    int k = 2;
    for (int i = 0; i < m_uorder - 1; i++) {
        for (int j = 0; j < size - 1; j++) {
            int currentIndex = basisBegin + j;
            delta1 = m_uknots[currentIndex + k - 1] - m_uknots[currentIndex];
            delta2 = m_uknots[currentIndex + k] - m_uknots[currentIndex + 1];

            term1 = 0;
            if (delta1) {
                term1 = (u - m_uknots[currentIndex]) / delta1;
            }

            term2 = 0;
            if (delta2) {
                term2 = (m_uknots[currentIndex + k] - u) / delta2;
            }

            basis[j] = term1 * basis[j] + term2 * basis[j + 1];
        }

        size--;
        k++;
    }

    vec3 value = {0.0, 0.0, 0.0};
    for (int i = 0; i < m_uorder; i++) {
        value += basis[i] * m_intermediateControlPoints[i];
    }

    return value;
}

vec3 BSurface::computeIntermediateControlPoint(int indexw, int basisStart, int pointsIndex, float w)
{
    // Setup initial basis vector
    int size = 2 * m_worder - 1;
    std::vector<float> basis(size, 0);
    basis[indexw - basisStart] = 1;

    // Compute basis
    float term1, term2;
    float delta1, delta2;
    int k = 2;
    for (int i = 0; i < m_worder - 1; i++) {
        for (int j = 0; j < size - 1; j++) {
            int currentIndex = basisStart + j;
            delta1 = m_wknots[currentIndex + k - 1] - m_wknots[currentIndex];
            delta2 = m_wknots[currentIndex + k] - m_wknots[currentIndex + 1];

            term1 = 0;
            if (delta1) {
                term1 = (w - m_wknots[currentIndex]) / delta1;
            }

            term2 = 0;
            if (delta2) {
                term2 = (m_wknots[currentIndex + k] - w) / delta2;
            }

            basis[j] = term1 * basis[j] + term2 * basis[j + 1];
        }

        size--;
        k++;
    }

    // Compute value
    vec3 value = {0.0, 0.0, 0.0};
    for (int i = 0; i < m_worder; i++) {
        value += basis[i] * m_controlPoints[basisStart + i][pointsIndex];
    }

    return value;
}

void BSurface::initRenderData()
{
    // Setup Flags
    m_renderData.DrawEdges    = true;
    m_renderData.DrawVertices = true;
    m_renderData.UseModelMatr = true;
    m_renderData.UseViewMatr  = true;
    m_renderData.UseProjMatr  = true;
    m_renderData.UseGlobalEdgeColor = true;
}
