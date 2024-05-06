#include "abstract/transformableobj3d.h"

const vec3 TransformableObj3D::UNITX_DEFAULT = {1, 0, 0};
const vec3 TransformableObj3D::UNITY_DEFAULT = {0, 1, 0};
const vec3 TransformableObj3D::UNITZ_DEFAULT = {0, 0, 1};
const vec3 TransformableObj3D::ORIGIN_DEFAULT = {0, 0, 0};
const vec3 TransformableObj3D::SCALES_DEFAULT = {1, 1, 1};

TransformableObj3D::TransformableObj3D()
    :m_modelMatrix(1.0f), // Identity matrix
     m_normalMatrix(1.0f), // Identity matrix
     m_scaleMatrix(1.0f), // Identity matrix
     m_unitx(UNITX_DEFAULT),
     m_unity(UNITY_DEFAULT),
     m_unitz(UNITZ_DEFAULT),
     m_origin(ORIGIN_DEFAULT),
     m_scales(SCALES_DEFAULT),
     m_angle(0),
     m_angleTrack(false)
{
}

const mat4 &TransformableObj3D::getModelMatrix() const
{
    return m_modelMatrix;
}

const mat4 &TransformableObj3D::getNormalMatrix() const
{
    return m_normalMatrix;
}

const vec3 &TransformableObj3D::getUnitx() const
{
    return m_unitx;
}

const vec3 &TransformableObj3D::getUnity() const
{
    return m_unity;
}

const vec3 &TransformableObj3D::getUnitz() const
{
    return m_unitz;
}

const vec3 &TransformableObj3D::getOrigin() const
{
    return m_origin;
}

const vec3 &TransformableObj3D::getScales() const
{
    return m_scales;
}

void TransformableObj3D::reset()
{
    m_modelMatrix = mat4(1.0f); // Identity matrix
    m_normalMatrix = mat4(1.0f); // Identity matrix
    m_scaleMatrix = mat4(1.0f); // Identity matrix

    m_unitx = UNITX_DEFAULT;
    m_unity = UNITY_DEFAULT;
    m_unitz = UNITZ_DEFAULT;
    m_origin = ORIGIN_DEFAULT;
    m_scales = SCALES_DEFAULT;

    m_angle = 0;
    m_angleTrack = false;
}

void TransformableObj3D::translate(const vec3 &t)
{
    this->translate_base(t);
    this->transformationCallback();
}

void TransformableObj3D::translateTo(const vec3 &pos)
{
    this->translate_base(pos - m_origin);
    this->transformationCallback();
}

void TransformableObj3D::translateItselfTo(const vec3 &pos)
{
    this->translate_base(pos - this->selfOrigin());

    this->transformationCallback();
}

void TransformableObj3D::rotatex(float angle, const vec3 &point)
{
    this->translate_base(-point);
    this->rotatex_base(angle);
    this->translate_base(point);

    this->transformationCallback();
}

void TransformableObj3D::rotatey(float angle, const vec3 &point)
{
    this->translate_base(-point);
    this->rotatey_base(angle);
    this->translate_base(point);

    this->transformationCallback();
}

void TransformableObj3D::rotatez(float angle, const vec3 &point)
{
    this->translate_base(-point);
    this->rotatez_base(angle);
    this->translate_base(point);

    this->transformationCallback();
}

void TransformableObj3D::rotateItselfx(float angle)
{
    this->translate_base(-this->selfOrigin());
    this->rotatex_base(angle);
    this->translate_base(this->selfOrigin());

    this->transformationCallback();
}

void TransformableObj3D::rotateItselfy(float angle)
{
    this->translate_base(-this->selfOrigin());
    this->rotatey_base(angle);
    this->translate_base(this->selfOrigin());

    this->transformationCallback();
}

void TransformableObj3D::rotateItselfz(float angle)
{
    this->translate_base(-this->selfOrigin());
    this->rotatez_base(angle);
    this->translate_base(this->selfOrigin());

    this->transformationCallback();
}

void TransformableObj3D::rotateAround(float angle, const vec3 &point, const vec3 &vector)
{
    this->rotateAround_base(angle, point, vector);

    this->transformationCallback();

    // Update tracked angle
    if (m_angleTrack) {
        m_angle += angle;
    }
}

void TransformableObj3D::rotateAroundTo(float angle, const vec3 &point, const vec3 &vector)
{
    this->rotateAround_base(angle - m_angle, point, vector);

    this->transformationCallback();

    // Update tracke angle
    m_angle = angle;
}

void TransformableObj3D::scale(float sx, float sy, float sz, const vec3 &point)
{
    this->translate_base(-point);
    this->scale_base(sx, sy, sz);
    this->translate_base(point);

    this->transformationCallback();
}

void TransformableObj3D::scale(float s, const vec3 &point)
{
    this->scale(s, s, s, point);
}

void TransformableObj3D::scaleTo(float sx, float sy, float sz, const vec3 &point)
{
    this->translate_base(-point);
    this->scale_base(sx / m_scales.x, sy / m_scales.y, sz / m_scales.z);
    this->translate_base(point);

    this->transformationCallback();
}

void TransformableObj3D::scaleTo(float s, const vec3 &point)
{
    this->scaleTo(s, s, s, point);
}

void TransformableObj3D::scaleItself(float sx, float sy, float sz)
{
    this->translate_base(-this->selfOrigin());
    this->scale_base(sx, sy, sz);
    this->translate_base(this->selfOrigin());

    this->transformationCallback();
}

void TransformableObj3D::scaleItself(float s)
{
    this->scaleItself(s, s, s);
}

void TransformableObj3D::scaleItselfTo(float sx, float sy, float sz)
{
    this->translate_base(-this->selfOrigin());
    this->scale_base(sx / m_scales.x, sy / m_scales.y, sz / m_scales.z);
    this->translate_base(this->selfOrigin());

    this->transformationCallback();
}

void TransformableObj3D::scaleItselfTo(float s)
{
    this->scaleItselfTo(s, s, s);
}

void TransformableObj3D::reflectx()
{
    this->scale_base(-1.0, 1.0, 1.0);

    this->transformationCallback();
}

void TransformableObj3D::reflecty()
{
    this->scale_base(1.0, -1.0, 1.0);

    this->transformationCallback();
}

void TransformableObj3D::reflectz()
{
    this->scale_base(1.0, 1.0, -1.0);

    this->transformationCallback();
}

void TransformableObj3D::reflect(const vec3 &point, const vec3 &normal)
{
    float cosx, sinx, cosy, siny;
    this->coincidez_values(normal, sinx, cosx, siny, cosy);

    this->translate_base(-point);
    this->rotatex_base_values(sinx, cosx);
    this->rotatey_base_values(-siny, cosy);
    this->reflectz();
    this->rotatey_base_values(siny, cosy);
    this->rotatex_base_values(-sinx, cosx);
    this->translate_base(point);

    this->transformationCallback();
}

void TransformableObj3D::coincideWithZ(const vec3 &vector)
{
    float cosx, sinx, cosy, siny;
    this->coincidez_values(vector, sinx, cosx, siny, cosy);
 
    this->translate_base(-m_origin);
    this->rotatex_base_values(sinx, cosx);
    this->rotatey_base_values(-siny, cosy);
    this->translate_base(m_origin);

    this->transformationCallback();
}

void TransformableObj3D::coincideWithZReverse(const vec3 &vector)
{
    float cosx, sinx, cosy, siny;
    this->coincidez_values(vector, sinx, cosx, siny, cosy);
 
    this->translate_base(-m_origin);
    this->rotatey_base_values(siny, cosy);
    this->rotatex_base_values(-sinx, cosx);
    this->translate_base(m_origin);

    this->transformationCallback();
}

void TransformableObj3D::resetAngle()
{
    m_angle = 0;
}

void TransformableObj3D::trackAngle(bool value)
{
    m_angleTrack = value;
}

float TransformableObj3D::getAngle() const
{
    return m_angle;
}

void TransformableObj3D::transformationCallback()
{
    // Update origin
    m_origin = m_modelMatrix * vec4(ORIGIN_DEFAULT, 1.0f);

    // Update units
    m_unitx = m_normalMatrix * vec4(UNITX_DEFAULT, 1.0f);
    m_unity = m_normalMatrix * vec4(UNITY_DEFAULT, 1.0f);
    m_unitz = m_normalMatrix * vec4(UNITZ_DEFAULT, 1.0f);

    // Update scales
    m_scales = m_scaleMatrix * vec4(SCALES_DEFAULT, 1.0f);
}

const vec3 &TransformableObj3D::selfOrigin() const
{
    return m_origin;
}

void TransformableObj3D::translate_base(const vec3 &t)
{
    // Make translation matrix
    mat4 matr(1.0f);
    matr[3] = vec4(t, 1.0f);

    // Apply transformation
    m_modelMatrix = matr * m_modelMatrix;
}

void TransformableObj3D::rotatex_base(float angle)
{
    float angleRadian = glm::radians(angle);
    this->rotatex_base_values(glm::sin(angleRadian), glm::cos(angleRadian));
}

void TransformableObj3D::rotatey_base(float angle)
{
    float angleRadian = glm::radians(angle);
    this->rotatey_base_values(glm::sin(angleRadian), glm::cos(angleRadian));
}

void TransformableObj3D::rotatez_base(float angle)
{
    float angleRadian = glm::radians(angle);
    this->rotatez_base_values(glm::sin(angleRadian), glm::cos(angleRadian));
}

void TransformableObj3D::rotatex_base_values(float sinValue, float cosValue)
{
    // Make rotation matrix
    mat4 matr(1.0f);
    matr[1][1] = cosValue;
    matr[2][1] = -sinValue;
    matr[1][2] = sinValue;
    matr[2][2] = cosValue;

    // Apply transformation
    m_modelMatrix = matr * m_modelMatrix;
    m_normalMatrix = matr * m_normalMatrix;
}

void TransformableObj3D::rotatey_base_values(float sinValue, float cosValue)
{
    // Make rotation matrix
    mat4 matr(1.0f);
    matr[0][0] = cosValue;
    matr[2][0] = sinValue;
    matr[0][2] = -sinValue;
    matr[2][2] = cosValue;

    // Apply transformation
    m_modelMatrix = matr * m_modelMatrix;
    m_normalMatrix = matr * m_normalMatrix;
}

void TransformableObj3D::rotatez_base_values(float sinValue, float cosValue)
{
    // Make rotation matrix
    mat4 matr(1.0f);
    matr[0][0] = cosValue;
    matr[1][0] = -sinValue;
    matr[0][1] = sinValue;
    matr[1][1] = cosValue;

    // Apply transformation
    m_modelMatrix = matr * m_modelMatrix;
    m_normalMatrix = matr * m_normalMatrix;
}

void TransformableObj3D::rotateAround_base(float angle, const vec3 &point, const vec3 &vector)
{
    float sinx, cosx, siny, cosy;
    this->coincidez_values(vector, sinx, cosx, siny, cosy);

    this->translate_base(-point);
    this->rotatex_base_values(sinx, cosx);
    this->rotatey_base_values(-siny, cosy);
    this->rotatez_base(angle);
    this->rotatey_base_values(siny, cosy);
    this->rotatex_base_values(-sinx, cosx);
    this->translate_base(point);
}

void TransformableObj3D::scale_base(float sx, float sy, float sz)
{
    // Make scale matrix
    mat4 matr(1.0f);
    matr[0][0] = sx;
    matr[1][1] = sy;
    matr[2][2] = sz;

    // Apply transformation
    m_modelMatrix = matr * m_modelMatrix;
    m_scaleMatrix = matr * m_scaleMatrix;
}

void TransformableObj3D::coincidez_values(const vec3 &vector, float &sinx, float &cosx, float &siny, float &cosy)
{
    vec3 unit = glm::normalize(vector);

    float d = sqrt(unit.y * unit.y + unit.z * unit.z);

    // Values for X rotation
    if (d > 0) {
        cosx = unit.z / d;
        sinx = unit.y / d;
    } else {
        cosx = 1;
        sinx = 0;
    }

    // Values for Y rotation
    cosy = d;
    siny = unit.x;
}
