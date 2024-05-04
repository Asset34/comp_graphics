#include "camera3d.h"

Camera3D::Camera3D(float hfov, float aspectRatio, float near, float far)
    :m_viewMatrix(1.0f),
     m_projMatrix(1.0f),
     m_projType(ProjType::No),
     m_horizontal(0),
     m_vertical(0),
     m_zoom(1),
     m_zoomFactor(ZOOM_FACTOR_DEFAULT),
     m_horizontalMin(HORIZONTAL_MIN_DEFAULT),
     m_horizontalMax(HORIZONTAL_MAX_DEFAULT),
     m_verticalMin(VERTICAL_MIN_DEFAULT),
     m_verticalMax(VERTICAL_MAX_DEFAULT),
     m_zoomMin(ZOOM_LIMIT_MIN_DEFAULT),
     m_zoomMax(ZOOM_LIMIT_MAX_DEFAULT),
     m_horizontalLimitFlag(false),
     m_verticalLimitFlag(false),
     m_zoomLimitFlag(false)
{
    this->setVolume(hfov, aspectRatio, near, far);
}

Camera3D::~Camera3D()
{
}

const mat4 &Camera3D::getViewMatrix()
{
    mat4 translateMatrix(1.0f);
    vec3 pos = this->getOrigin();
    translateMatrix[3] = vec4(-pos, 1.0f);

    mat4 rotateMatrix(1.0f);
    rotateMatrix[0] = vec4(this->getUnitx(), 0);
    rotateMatrix[1] = vec4(this->getUnity(), 0);
    rotateMatrix[2] = vec4(this->getUnitz(), 0);
    rotateMatrix = glm::transpose(rotateMatrix);

    m_viewMatrix = rotateMatrix * translateMatrix;
    return m_viewMatrix;
}

const mat4 &Camera3D::getProjMatrix() const
{
    return m_projMatrix;
}

void Camera3D::home()
{
     m_horizontal = 0;
     m_vertical = 0;
     m_zoom = 1;
}

void Camera3D::setAspectRatio(float aspectRatio)
{
    this->computeRight(aspectRatio);
    this->computeProjection();
}

void Camera3D::setFov(float fov)
{
    this->computeTop(fov);
    this->computeProjection();
}

void Camera3D::setVolume(float hfov, float aspectRatio, float near, float far)
{
    m_near = near;
    m_far = far;

    this->computeTop(hfov);
    this->computeRight(aspectRatio);
    this->computeProjection();
}

void Camera3D::setNoProjection()
{
    m_projType = ProjType::No;
    this->computeProjection();
}

void Camera3D::setOrthoProjection()
{
    m_projType = ProjType::Ortho;
    this->computeProjection();
}

void Camera3D::setPerspectiveProjection()
{
    m_projType = ProjType::Perspective;
    this->computeProjection();
}

void Camera3D::setHorizontalLimits(float min, float max)
{
    m_horizontalMin = min;
    m_horizontalMax = max;
}

void Camera3D::setVerticalLimits(float min, float max)
{
    m_verticalMin = min;
    m_verticalMax = max;
}

void Camera3D::setZoomLimits(float min, float max)
{
    m_zoomMin = min;
    m_zoomMax = max;
}

void Camera3D::setZoomFactor(float factor)
{
    m_zoomFactor = factor;
}

void Camera3D::rotateHorizontal(float angle)
{
    float rotationAngle = angle;
    float newHorizontal = m_horizontal + angle;

    if (m_horizontalLimitFlag) {
        if (newHorizontal < m_horizontalMin) newHorizontal = m_horizontalMin;
        if (newHorizontal > m_horizontalMax) newHorizontal = m_horizontalMax;

        rotationAngle = newHorizontal - m_horizontal;
    }

    m_horizontal = newHorizontal;
    this->rotatey(rotationAngle);
}

void Camera3D::rotateVertical(float angle)
{
    float rotationAngle = angle;
    float newVertical = m_vertical + angle;

    if (m_verticalLimitFlag) {
        if (newVertical < m_verticalMin) newVertical = m_verticalMin;
        if (newVertical > m_verticalMax) newVertical = m_verticalMax;

        rotationAngle = newVertical - m_vertical;
    }

    m_vertical = newVertical;
    this->rotateAround(rotationAngle, {0, 0, 0}, this->getUnitx());
}

void Camera3D::zoomIn()
{
    float factor = m_zoomFactor;
    float newZoom = m_zoom * m_zoomFactor;
    if (m_zoomLimitFlag) {
        if (newZoom < m_zoomMin) newZoom = m_zoomMin;

        factor = newZoom / m_zoom;
    }

    m_zoom = newZoom;
    this->scale(factor);
}

void Camera3D::zoomOut()
{
    float factor = 1.0 / m_zoomFactor;
    float newZoom = m_zoom * factor;
    if (m_zoomLimitFlag) {
        if (newZoom > m_zoomMax) newZoom = m_zoomMax;

        factor = newZoom / m_zoom;
    }

    m_zoom = newZoom;
    this->scale(factor);
}

void Camera3D::setZoomLimitsFlag(bool flag)
{
    m_zoomLimitFlag = flag;
}

void Camera3D::setHorizontalLimitsFlag(bool flag)
{
    m_horizontalLimitFlag = flag;
}

void Camera3D::setVerticalLimitsFlag(bool flag)
{
    m_verticalLimitFlag = flag;
}

void Camera3D::computeTop(float fov)
{
    float fovRadians = glm::radians(fov);
    m_top = glm::tan(fovRadians / 2.0) * m_near;
}

void Camera3D::computeRight(float aspectRatio)
{
    m_right = m_top * aspectRatio;
}

void Camera3D::computeProjection()
{
    // Intermediate values
    float d = m_far - m_near;

    m_projMatrix = mat4(0.0f);
    switch (m_projType)
    {
        case No:
            m_projMatrix = mat4(1.0f);
        break;

        case Ortho:
            m_projMatrix[0][0] = 1.0 / m_right;
            m_projMatrix[1][1] = 1.0 / m_top;
            m_projMatrix[2][2] = -2.0 / d;
            m_projMatrix[3][3] = 1;
            m_projMatrix[3][2] = - (m_far + m_near) / d;
        break;

        case Perspective:
            m_projMatrix[0][0] = m_near / m_right;
            m_projMatrix[1][1] = m_near / m_top;
            m_projMatrix[2][2] = - (m_near + m_far) / d;
            m_projMatrix[2][3] = -1;
            m_projMatrix[3][2] = - 2 * m_far * m_near / d;
        break;
    }
}
