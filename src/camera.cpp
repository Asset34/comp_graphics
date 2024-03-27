#include "camera.h"

Camera::Camera(float hfov, float aspectRatio, float near, float far)
    :m_viewMatrix(1.0f),
     m_projMatrix(1.0f),
     m_projType(ProjType::No)
{
    this->setVolume(hfov, aspectRatio, near, far);
}

Camera::~Camera()
{
}

const mat4 &Camera::getViewMatrix()
{
    mat4 translateMatrix(1.0f);
    vec3 pos = this->getPosition();
    translateMatrix[3] = vec4(-pos, 1.0f);

    mat4 rotateMatrix = glm::transpose(this->getUnits());

    m_viewMatrix = rotateMatrix * translateMatrix;
    return m_viewMatrix;
}

const mat4 &Camera::getProjectionMatrix() const
{
    return m_projMatrix;
}

void Camera::setAspectRatio(float aspectRatio)
{
    this->computeRight(aspectRatio);
    this->computeProjection();
}

void Camera::setHFov(float hfov)
{
    this->computeTop(hfov);
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

void Camera::lookAt(const vec3 &point)
{
    vec3 vector = this->getPosition() - point;
    this->coincidez(vector);
}

void Camera::computeTop(float hfov)
{
    float hfovRadians = glm::radians(hfov);
    m_top = glm::tan(hfovRadians / 2.0) * m_near;
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
