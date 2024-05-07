#include "abstract/transformableobj2d.h"

const vec2 TransformableObj2D::UNITX_DEFAULT = {1, 0};
const vec2 TransformableObj2D::UNITY_DEFAULT = {0, 1};
const vec2 TransformableObj2D::ORIGIN_DEFAULT = {0, 0};
const vec2 TransformableObj2D::SCALES_DEFAULT = {1, 1};

TransformableObj2D::TransformableObj2D()
    :m_modelMatrix(1.0f), // Identity matrix
     m_normalMatrix(1.0f), // Identity matrix
     m_scaleMatrix(1.0f), // Identity matrix
     m_unitx(UNITX_DEFAULT),
     m_unity(UNITY_DEFAULT),
     m_origin(ORIGIN_DEFAULT),
     m_scales(SCALES_DEFAULT),
     m_angle(0),
     m_angleTrack(false)
{
}

const mat3 &TransformableObj2D::getModelMatrix() const
{
    return m_modelMatrix;
}

const mat3 &TransformableObj2D::getNormalMatrix() const
{
    return m_normalMatrix;
}

const vec2 &TransformableObj2D::getUnitx() const
{
    return m_unitx;
}

const vec2 &TransformableObj2D::getUnity() const
{
    return m_unity;
}

const vec2 &TransformableObj2D::getOrigin() const
{
    return m_origin;
}

const vec2 &TransformableObj2D::getScales() const
{
    return m_scales;
}

void TransformableObj2D::reset()
{
    m_modelMatrix = mat3(1.0f); // Identity matrix
    m_normalMatrix = mat3(1.0f); // Identity matrix
    m_scaleMatrix = mat3(1.0f); // Identity matrix

    m_unitx = UNITX_DEFAULT;
    m_unity = UNITY_DEFAULT;
    m_origin = ORIGIN_DEFAULT;
    m_scales = SCALES_DEFAULT;

    m_angle = 0;
    m_angleTrack = false;
}

void TransformableObj2D::translate(const vec2 &t)
{
    this->translate_base(t);
    this->transformationCallback();
}

void TransformableObj2D::translateTo(const vec2 &pos)
{
    this->translate_base(pos - m_origin);
    this->transformationCallback();
}

void TransformableObj2D::translateItselfTo(const vec2 &pos)
{
    this->translate_base(pos - this->selfOrigin());
    this->transformationCallback();
}

void TransformableObj2D::rotate(float angle, const vec2 &point)
{
    this->translate_base(-point);
    this->rotate_base(angle);
    this->translate_base(point);

    this->transformationCallback();
}

void TransformableObj2D::rotateItself(float angle)
{
    this->translate_base(-this->selfOrigin());
    this->rotate_base(angle);
    this->translate_base(this->selfOrigin());

    this->transformationCallback();
}

void TransformableObj2D::scale(float sx, float sy, const vec2 &point)
{
    this->translate_base(-point);
    this->scale_base(sx, sy);
    this->translate_base(point);

    this->transformationCallback();
}

void TransformableObj2D::scale(float s, const vec2 &point)
{
    this->scale(s, point);
}

void TransformableObj2D::scaleTo(float sx, float sy, const vec2 &point)
{
    this->translate_base(-point);
    this->scale_base(sx / m_scales.x, sy / m_scales.y);
    this->translate_base(point);

    this->transformationCallback();
}

void TransformableObj2D::scaleTo(float s, const vec2 &point)
{
    this->scaleTo(s, s, point);
}

void TransformableObj2D::scaleItself(float sx, float sy)
{
    this->translate_base(-this->selfOrigin());
    this->scale_base(sx, sy);
    this->translate_base(this->selfOrigin());

    this->transformationCallback();
}

void TransformableObj2D::scaleItself(float s)
{
    this->scaleItself(s, s);
}

void TransformableObj2D::scaleItselfTo(float sx, float sy)
{
    this->translate_base(-this->selfOrigin());
    this->scale_base(sx / m_scales.x, sy / m_scales.y);
    this->translate_base(this->selfOrigin());

    this->transformationCallback();
}

void TransformableObj2D::scaleItselfTo(float s)
{
    this->scaleItselfTo(s, s);
}

void TransformableObj2D::reflectx()
{
    this->scale_base(-1.0, 1.0);
    this->transformationCallback();
}

void TransformableObj2D::reflecty()
{
    this->scale_base(1.0, -1.0);
    this->transformationCallback();
}

void TransformableObj2D::resetAngle()
{
    m_angle = 0;
}

void TransformableObj2D::trackAngle(bool value)
{
    m_angleTrack = value;
}

float TransformableObj2D::getAngle() const
{
    return m_angle;
}

void TransformableObj2D::transformationCallback()
{
    // Update origin
    m_origin = m_modelMatrix * vec3(ORIGIN_DEFAULT, 1.0f);

    // Update units
    m_unitx = m_normalMatrix * vec3(UNITX_DEFAULT, 1.0f);
    m_unity = m_normalMatrix * vec3(UNITY_DEFAULT, 1.0f);

    // Update scales
    m_scales = m_scaleMatrix * vec3(SCALES_DEFAULT, 1.0f);
}

const vec2 &TransformableObj2D::selfOrigin() const
{
    return m_origin;
}

void TransformableObj2D::translate_base(const vec2 &t)
{
    // Make translation matrix
    mat3 matr(1.0f);
    matr[2] = vec3(t, 1.0f);

    // Apply transformation
    m_modelMatrix = matr * m_modelMatrix;
}

void TransformableObj2D::rotate_base(float angle)
{
    // Convert to radians
    float angleRadian = glm::radians(angle);

    // Precompute
    float sinValue = glm::sin(angleRadian);
    float cosValue = glm::cos(angleRadian);

    // Make rotation matrix
    mat3 matr(1.0f);
    matr[0][0] = cosValue;
    matr[1][0] = -sinValue;
    matr[0][1] = sinValue;
    matr[1][1] = cosValue;
}

void TransformableObj2D::scale_base(float sx, float sy)
{
    // Make scale matrix
    mat3 matr(1.0f);
    matr[0][0] = sx;
    matr[1][1] = sy;

    // Apply transformation
    m_modelMatrix = matr * m_modelMatrix;
    m_scaleMatrix = matr * m_scaleMatrix;
}
