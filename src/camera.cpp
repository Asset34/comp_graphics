#include "camera.h"

Camera::Camera(float hfov, float aspectRatio, float near, float far)
    :m_viewMatrix(1.0f),
     m_projMatrix(1.0f),
     m_projType(ProjType::No),
     m_yaw(0),
     m_pitch(0),
     m_zoomSensitivity(1.0),
     m_yawLimit(false),
     m_pitchLimit(false),
     m_zoomLimit(false),
     m_callbackOccured(false)
{
    this->setVolume(hfov, aspectRatio, near, far);
}

Camera::~Camera()
{
}

const mat4 &Camera::getViewMatrix()
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

const mat4 &Camera::getProjMatrix() const
{
    return m_projMatrix;
}

void Camera::setAspectRatio(float aspectRatio)
{
    this->computeRight(aspectRatio);
    this->computeProjection();
}

void Camera::setFov(float fov)
{
    this->computeTop(fov);
    this->computeProjection();
}

void Camera::setVolume(float hfov, float aspectRatio, float near, float far)
{
    m_near = near;
    m_far = far;

    this->computeTop(hfov);
    this->computeRight(aspectRatio);
    this->computeProjection();
}

void Camera::setNoProjection()
{
    m_projType = ProjType::No;
    this->computeProjection();
}

void Camera::setOrthoProjection()
{
    m_projType = ProjType::Ortho;
    this->computeProjection();
}

void Camera::setPerspectiveProjection()
{
    m_projType = ProjType::Perspective;
    this->computeProjection();
}

void Camera::setYawLimits(float min, float max)
{
    m_yawMin = min;
    m_yawMax = max;
}

void Camera::setPitchLimits(float min, float max)
{
    m_pitchMin = min;
    m_pitchMax = max;
}

void Camera::setZoomLimits(float min, float max)
{
    m_zoomMin = min;
    m_zoomMax = max;
}

void Camera::setZoomSensitivity(float value)
{
    m_zoomSensitivity = value;
}

void Camera::rotateYaw(float angle)
{
    float rotationAngle = angle;
    float newYaw = m_yaw + angle;

    if (m_yawLimit) {
        if (newYaw < m_yawMin) newYaw = m_yawMin;
        if (newYaw > m_yawMax) newYaw = m_yawMax;

        rotationAngle = newYaw - m_yaw;
    }

    m_yaw = newYaw;
    this->rotatey(rotationAngle);
}

void Camera::rotatePitch(float angle)
{
    float rotationAngle = angle;
    float newPitch = m_pitch + angle;

    if (m_pitchLimit) {
        if (newPitch < m_pitchMin) newPitch = m_pitchMin;
        if (newPitch > m_pitchMax) newPitch = m_pitchMax;

        rotationAngle = newPitch - m_pitch;
    }

    m_pitch = newPitch;
    this->rotateAround(rotationAngle, {0, 0, 0}, this->getUnitx());
}

void Camera::ZoomIn()
{
    // this->scale(ZOOM_IN_FACTOR);
}

void Camera::ZoomOut()
{
    // this->scale(ZOOM_OUT_FACTOR);
}

void Camera::computeTop(float fov)
{
    float fovRadians = glm::radians(fov);
    m_top = glm::tan(fovRadians / 2.0) * m_near;
}

void Camera::computeRight(float aspectRatio)
{
    m_right = m_top * aspectRatio;
}

void Camera::computeProjection()
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
