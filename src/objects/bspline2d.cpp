#include "objects/bspline2d.h"

const vec3 BSpline2D::COLOR_DEFAULT = {0, 0, 0};

BSpline2D::BSpline2D()
    : m_knotBeginIndex(0),
      m_knotEndIndex(0),
      m_order(0),
      m_renderStep(0.1),
      m_autoupdate(true),
      m_color(COLOR_DEFAULT),
      m_lineWidth(1.0)
{
}

BSpline2D::~BSpline2D()
{
}

void BSpline2D::beginEdit()
{
    m_autoupdate = false;
}

void BSpline2D::endEdit()
{
    m_autoupdate = true;
    this->updateAllSegments();
}

void BSpline2D::addControlPoint(const vec2 &cp)
{
    m_contorlPoints.push_back(cp);

    if (m_autoupdate) {
        this->updateKnots();
        // TODO: update new segments
        this->updateAllSegments();
    }
}

void BSpline2D::setControlPoint(int index, const vec2 &cp)
{
    m_contorlPoints[index] = cp;

    if (m_autoupdate) {
        // TODO: update near segments
        this->updateAllSegments();
    }
}

void BSpline2D::defineKnots(const std::vector<float> &knots)
{
    m_knots = knots;

    if (m_autoupdate) {
        this->updateAllSegments();
    }
}

int BSpline2D::getKnotsNumber() const
{
    return m_knots.size();
}

void BSpline2D::setKnot(int index, float knot)
{
    m_knots[index] = knot;

    if (m_autoupdate) {
        // TODO: update near(left and right) segments
        this->updateAllSegments();
    }
}

float BSpline2D::getKnot(int index)
{
    return m_knots[index];
}

void BSpline2D::setOrder(int order)
{
    m_order = order;

    if (m_autoupdate) {
        this->updateKnots();
        this->updateAllSegments();
    }
}

int BSpline2D::getOrder() const
{
    return m_order;
}

int BSpline2D::getOrderMax() const
{
    return m_contorlPoints.size();
}

void BSpline2D::setRenderStep(float step)
{
    m_renderStep = step;

    if (m_autoupdate) {
        this->updateAllSegments();
    }
}

float BSpline2D::getRenderStep() const
{
    return m_renderStep;
}

void BSpline2D::setColor(const vec3 &color)
{
    m_color = color;
}
void BSpline2D::setLineWidth(float width)
{
    m_lineWidth = width;
}

RenderData BSpline2D::getRenderData()
{
    RenderData data;

    // Setup Flags
    data.DrawEdges    = true;
    data.UseViewMatr  = true;
    data.UseProjMatr  = true;
    data.UseGlobalEdgeColor = true;

    // Setup Data
    
    int size = 0;
    for (auto segment : m_segments) {
        size += segment.size();
    }

    data.VertexData.reserve(size);
    for (auto segment : m_segments) {
        for (auto v : segment) {
            data.VertexData.push_back(vec3(v, 0.0));
        }
    }

    data.Edges.reserve(data.VertexData.size() - 1);
    for (int i = 0; i < data.VertexData.size() - 1; i++) {
        data.Edges.push_back({i, i + 1});
    }

    // Setup global values
    data.GlobalEdgeColor = m_color;
    data.EdgeWidth = m_lineWidth;

    return data;
}

glm::mat4 BSpline2D::getTransformation()
{
    return glm::mat4(1.0);
}

void BSpline2D::updateSegmentsBorders()
{
    m_knotBeginIndex = m_order - 1;
    m_knotEndIndex = m_knots.size() - m_order;
}

void BSpline2D::updateKnots()
{
    int diff = m_contorlPoints.size() + m_order - m_knots.size();

    if (diff > 0) {
        float knotvalue = m_knots.back() + 1;
        for (int i = 0; i < diff; i++) {
            m_knots.push_back(knotvalue);
        }
    } else if (diff < 0) {
        for (int i = 0; i < -diff; i++) {
            m_knots.pop_back();
        }
    }
}

void BSpline2D::updateAllSegments()
{
    // Define begin and end segments
    int beginSegment = m_order - 1;
    int endSegment = m_knots.size() - m_order - 1;

    // Prepare segments
    m_segments.clear();
    m_segments.resize(m_knots.size() - 1);

    // Update
    for (int i = beginSegment; i <= endSegment; i++) {
        this->updateSegment(i);
    }
}

void BSpline2D::updateSegment(int index)
{
    // Prepare segment
    m_segments[index].clear();

    // Define basis range
    int basisBegin = index - m_order + 1;
    int basisEnd = index;

    // Define t range
    float tmin = m_knots[index];
    float tmax = m_knots[index + 1];

    // Main loop
    for (float t = tmin; t < tmax; t += m_renderStep) {
        this->computeSegment(index, basisBegin, basisEnd, t);
    }
}

void BSpline2D::computeSegment(int index, int basisBegin, int basisEnd, float t)
{
    // Setup initial basis vector
    int size = 2 * m_order - 1;
    std::vector<float> basis(size, 0);
    basis[index - basisBegin] = 1;

    // Compute basis
    float term1, term2;
    float delta1, delta2;
    int k = 2;
    for (int i = 0; i < m_order - 1; i++) {
        for (int j = 0; j < size - 1; j++) {
            int currentIndex = basisBegin + j;
            delta1 = m_knots[currentIndex + k - 1] - m_knots[currentIndex];
            delta2 = m_knots[currentIndex + k] - m_knots[currentIndex + 1];

            term1 = 0;
            if (delta1) {
                term1 = (t - m_knots[currentIndex]) / delta1;
            }

            term2 = 0;
            if (delta2) {
                term2 = (m_knots[currentIndex + k] - t) / delta2;
            }

            basis[j] = term1 * basis[j] + term2 * basis[j + 1];
        }

        size--;
        k++;
    }

    // Compute value
    vec2 value = {0.0, 0.0};
    for (int i = 0; i < m_order; i++) {
        value += basis[i] * m_contorlPoints[basisBegin + i];
    }

    // Add value
    m_segments[index].push_back(value);
}
