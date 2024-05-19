#include "objects/bspline2d.h"

const Color BSpline2D::COLOR_DEFAULT = {0, 0, 0};

BSpline2D::BSpline2D()
{
    this->initRenderData();
}

void BSpline2D::setAutocompute(bool value)
{
    m_autoCompute = value;
}

void BSpline2D::compute()
{
    this->computeBorders();
    this->updateAllSegments();
    
    this->setUpdated();
}

void BSpline2D::addControlPoint(const vec2 &cp)
{
    m_contorlPoints.push_back(cp);

    if (m_autoCompute) {
        this->updateKnots();
        this->computeBorders();        
        this->updateSegment(m_endSegment);

        this->setUpdated();
    }
}

void BSpline2D::setControlPoint(int index, const vec2 &cp)
{
    m_contorlPoints[index] = cp;

    if (m_autoCompute) {
        this->updateSegmentsAffectedByBasis(index);

        this->setUpdated();
    }
}

void BSpline2D::defineKnots(const std::vector<float> &knots)
{
    m_knots = knots;

    if (m_autoCompute) {
        this->computeBorders();
        this->updateAllSegments();
        this->setUpdated();
    }
}

void BSpline2D::defineKnotsUniform(float step)
{
    m_knots.resize(m_contorlPoints.size() + m_order);

    float value = 0;
    for (int i = 0; i < m_knots.size(); i++) {
        m_knots[i] = value;
        value += step;
    }

    if (m_autoCompute) {
        this->computeBorders();
        this->updateAllSegments();
        this->setUpdated();
    }
}

void BSpline2D::defineKnotsOpenUniform(float step)
{
    m_knots.resize(m_contorlPoints.size() + m_order);

    // Begin
    for (int i = 0; i < m_order; i++) {
        m_knots[i] = 0;
    }

    // Intermediate
    float value = 0;
    for (int i = m_order; i < m_knots.size() - m_order; i++) {
        value += step;
        m_knots[i] = value;
    }

    // End
    value += step;
    for (int i = m_knots.size() - m_order; i < m_knots.size(); i++) {
        m_knots[i] = value;
    }

    if (m_autoCompute) {
        this->computeBorders();
        this->updateAllSegments();
        this->setUpdated();
    }
}

int BSpline2D::getKnotsNumber() const
{
    return m_knots.size();
}

void BSpline2D::setKnot(int index, float knot)
{
    m_knots[index] = knot;

    if (m_autoCompute) {
        this->computeBorders();
        this->updateSegmentsAffectedByKnot(index);
        // this->updateAllSegments();

        this->setUpdated();
    }
}

float BSpline2D::getKnot(int index)
{
    return m_knots[index];
}

void BSpline2D::setOrder(int order)
{
    m_order = order;

    if (m_autoCompute) {
        this->updateKnots();
        this->updateAllSegments();
        this->setUpdated();
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

    if (m_autoCompute) {
        this->updateAllSegments();
        this->setUpdated();
    }
}

float BSpline2D::getRenderStep() const
{
    return m_renderStep;
}

void BSpline2D::setColor(const Color &color)
{
    m_color = color;
}

const Color &BSpline2D::getColor() const
{
    return m_color;
}

void BSpline2D::setLineWidth(float width)
{
    m_lineWidth = width;
}

const RenderData &BSpline2D::getRenderData()
{
    // Setup Visual values
    m_renderData.GlobalEdgeColor = m_color;
    m_renderData.EdgeWidth = m_lineWidth;

    // Setup Data

    if (!this->updated()) return m_renderData;
    
    int size = 0;
    for (auto segment : m_segments) {
        size += segment.size();
    }

    m_renderData.VertexData.resize(size);
    int i = 0;
    for (auto segment : m_segments) {
        for (auto v : segment) {
            m_renderData.VertexData[i] = {v, 0.0};
            i++;
        }
    }

    if (size > 0) {
        m_renderData.Edges.resize(size - 1);
        for (int i = 0; i < size - 1; i++) {
            m_renderData.Edges[i] = {i, i + 1};
        }
    }
    
    return m_renderData;
}

void BSpline2D::computeBorders()
{
    m_beginSegment = m_order - 1;
    m_endSegment = m_knots.size() - m_order - 1;
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

    this->computeBorders();
}

bool BSpline2D::isSegmentEmpty(int index)
{
    return m_knots[index + 1] - m_knots[index] == 0;
}

void BSpline2D::updateAllSegments()
{
    // Prepare segments
    m_segments.clear();
    m_segments.resize(m_knots.size() - 1);

    // Update
    for (int i = m_beginSegment; i <= m_endSegment; i++) {
        this->updateSegment(i);
    }

    this->updateLast();
}

void BSpline2D::updateSegmentsAffectedByBasis(int basisIndex)
{
    // Define affected segments borders
    int begin = basisIndex;
    int end = basisIndex + m_order - 1;

    // Project onto usable segments
    if (begin < m_beginSegment) {
        begin = m_beginSegment;
    }
    if (end > m_endSegment) {
        end = m_endSegment;
    }

    // Update defined segments
    for (int i = begin; i <= end; i++) {
        this->updateSegment(i);
    }

    if (end == m_endSegment) {
        this->updateLast();
    }
}

void BSpline2D::updateSegmentsAffectedByKnot(int knotIndex)
{
    int begin = knotIndex - m_order;
    int end = knotIndex + m_order - 1;

    if (begin < m_beginSegment) begin = m_beginSegment;
    if (end > m_endSegment) end = m_endSegment;

    for (int i = begin; i <= end; i++) {
        this->updateSegment(i);
    }

    if (end == m_endSegment) {
        this->updateLast();
    }
}


void BSpline2D::updateSegment(int index)
{
    // Prepare segment
    m_segments[index].clear();

    // Define index of the 1st basis
    int basisBegin = index - m_order + 1;

    // Define segment range
    float tmin = m_knots[index];
    float tmax = m_knots[index + 1];

    // Main loop
    for (float t = tmin; t < tmax; t += m_renderStep) {
        this->computeSegment(index, basisBegin, t);
    }

    // // Update last
    // if (tmax - tmin > 0) {
    //     this->computeSegment(index, basisBegin, tmax);
    // }
}

void BSpline2D::updateLast()
{
    int segment = m_endSegment;
    while (isSegmentEmpty(segment) && segment > 0) {
        segment--;
    }

    if (segment < m_beginSegment) return;

    // Define index of the 1st basis
    int basisBegin = segment - m_order + 1;
    float tmax = m_knots[segment + 1];

    this->computeSegment(segment, basisBegin, tmax);
}

void BSpline2D::computeSegment(int index, int basisBegin, float t)
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

void BSpline2D::initRenderData()
{
    // Setup Transformation Matrix
    m_renderData.ModelMatrix = glm::mat4(1.0); // Identity Matrix

    // Setup Flags
    m_renderData.DrawEdges    = true;
    m_renderData.UseViewMatr  = true;
    m_renderData.UseProjMatr  = true;
    m_renderData.UseGlobalEdgeColor = true;
}
