#include "objects/bsurface.h"

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
}

void BSurface::setControlPoints(const BSurfacePolygon &polygon)
{
    m_controlPoints = polygon.getControlPoints();
}

void BSurface::defineWKnots(const std::vector<float> &knots)
{
    m_wknots = knots;

    if (m_autoCompute) {
        // TODO
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
    }
}

void BSurface::setWKnot(int index, float knot)
{
    m_wknots[index] = knot;

    if (m_autoCompute) {
        // TODO
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
    }
}

void BSurface::defineUKnotsUniform(float step)
{
    m_uknots.resize(m_controlPoints.size() + m_uorder);

    float value = 0;
    for (int i = 0; i < m_uknots.size(); i++) {
        m_uknots[i] = value;
        value += step;
    }

    if (m_autoCompute) {
        // TODO
    }  
}

void BSurface::defineUKnotsOpenUniform(float step)
{
    m_uknots.resize(m_controlPoints.size() + m_uorder);

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
    }
}

void BSurface::setUKnot(int index, float knot)
{
    m_uknots[index] = knot;
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
    }
}

int BSurface::getWDegree() const
{
    return m_worder - 1;
}

int BSurface::getWDegreeMax() const
{
    return m_controlPoints.size() - 1;
}

void BSurface::setUDegree(int degree)
{
    m_uorder = degree + 1;

    if (m_autoCompute) {
        // TODO
    }
}

int BSurface::getUDegree() const
{
    return m_uorder - 1;
}

int BSurface::getUDegreeMax() const
{
    if (!m_controlPoints.size()) return 0;

    return m_controlPoints[0].size();
}

void BSurface::setWRenderStep(float step)
{
    m_wrenderStep = step;
}

float BSurface::getWRenderStep() const
{
    return m_wrenderStep;
}

void BSurface::setURenderStep(float step)
{
    m_urenderStep = step;
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


    return m_renderData;
}

void BSurface::initRenderData()
{
    // Setup Flags
    m_renderData.DrawEdges    = true;
    m_renderData.UseViewMatr  = true;
    m_renderData.UseProjMatr  = true;
    m_renderData.UseGlobalEdgeColor = true;
}
