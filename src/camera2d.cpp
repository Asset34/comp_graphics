#include "camera2d.h"

Camera2D::Camera2D(float height, float aspectRatio)
    : m_viewMatrix(1.0f),
      m_clipMatrix(1.0f),
      m_zoom(1.0),
      m_zoomFactor(ZOOM_FACTOR_DEFAULT),
      m_zoomMin(ZOOM_LIMIT_MIN_DEFAULT),
      m_zoomMax(ZOOM_LIMIT_MAX_DEFAULT),
      m_zoomLimitFlag(false),
      m_originHome({0, 0})
{
    this->setArea(height, aspectRatio);
    this->computeClipMatrix();
}

Camera2D::~Camera2D()
{
}

const mat4 &Camera2D::getViewMatrix()
{
    mat4 translateMatrix(1.0f);
    vec2 pos = this->getOrigin();
    translateMatrix[3] = vec4(-pos, 0.0f, 1.0f);

    mat4 rotateMatrix(1.0f);
    rotateMatrix[0] = vec4(this->getUnitx(), 0, 0);
    rotateMatrix[1] = vec4(this->getUnity(), 0, 0);
    rotateMatrix[2] = vec4(0);
    rotateMatrix = glm::transpose(rotateMatrix);

    m_viewMatrix = rotateMatrix * translateMatrix;
    return m_viewMatrix;
}

const mat4 &Camera2D::getClippingMatrix()
{
    return m_clipMatrix;
}

void Camera2D::home()
{
    this->translate(m_originHome - this->getOrigin());
}

void Camera2D::setHome()
{
    m_originHome = this->getOrigin();
}

void Camera2D::setZoomLimitsFlag(bool flag)
{
    m_zoomLimitFlag = flag;
}

void Camera2D::setZoomLimits(float min, float max)
{
    m_zoomMin = min;
    m_zoomMax = max;
}

void Camera2D::setZoomFactor(float factor)
{
    m_zoomFactor = factor;
}

void Camera2D::setArea(float height, float aspectRatio)
{
    m_height = height;
    this->setAspectRatio(aspectRatio);

    this->computeClipMatrix();
}

void Camera2D::setAspectRatio(float aspectRatio)
{
    m_width = m_height * aspectRatio;

    this->computeClipMatrix();
}

void Camera2D::movex(float dx)
{
    this->translate({dx, 0});
}

void Camera2D::movey(float dy)
{
    this->translate({0, dy});
}

void Camera2D::zoomIn()
{
    float factor = m_zoomFactor;
    float newZoom = m_zoom * m_zoomFactor;
    if (m_zoomLimitFlag) {
        if (newZoom < m_zoomMin) newZoom = m_zoomMin;

        factor = newZoom / m_zoom;
    }

    m_zoom = newZoom;
    this->scale(factor, this->getOrigin());
}

void Camera2D::zoomOut()
{
    float factor = 1.0 / m_zoomFactor;
    float newZoom = m_zoom * factor;
    if (m_zoomLimitFlag) {
        if (newZoom > m_zoomMax) newZoom = m_zoomMax;

        factor = newZoom / m_zoom;
    }

    m_zoom = newZoom;
    this->scale(factor, this->getOrigin());
}

void Camera2D::computeClipMatrix()
{
    m_clipMatrix[0][0] = 2.0 / m_width;
    m_clipMatrix[1][1] = 2.0 / m_height;
}
