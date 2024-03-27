#include "sceneobj.h"

SceneObj::SceneObj()
    :m_modelMatrix(1.0f), // Identity matrix
     m_units(1.0f), // columns of basic unit vectors (1,0,0), (0,1,0) and (0,0,1)
     m_position(0.0f),
     m_scales(1.0f, 1.0f, 1.0f)
{
}

SceneObj::~SceneObj()
{
}

const mat4 &SceneObj::getModelMatrix() const
{
    return m_modelMatrix;
}

const mat3 &SceneObj::getUnits() const
{
    return m_units;
}

vec3 SceneObj::getUnitx() const
{
    return m_units[0];
}

vec3 SceneObj::getUnity() const
{
    return m_units[1];
}

vec3 SceneObj::getUnitz() const
{
    return m_units[2];
}

const vec3 &SceneObj::getPosition() const
{
    return m_position;
}

const vec3 &SceneObj::getScales() const
{
    return m_scales;
}

void SceneObj::translate(const vec3 &t)
{
    // Make translation matrix
    mat4 matr(1.0f);
    matr[3] = vec4(t, 1.0f);

    // Apply transformation
    m_modelMatrix = matr * m_modelMatrix;
    this->updatePosition(matr);
}

void SceneObj::setPosition(const vec3 &pos)
{
    vec3 dpos;
    dpos.x = pos.x - m_position.x;
    dpos.y = pos.y - m_position.y;
    dpos.z = pos.z - m_position.z;

    this->translate(dpos);
}

void SceneObj::rotatex(float angle, const vec3 &point)
{
    // Translate origin to the axis point
    this->translate(-point);

    // Convert angle to radians
    float angleRadian = glm::radians(angle);

    // Make rotation matrix
    mat4 matr(1.0f);
    matr[1][1] = glm::cos(angleRadian);
    matr[2][1] = -glm::sin(angleRadian);
    matr[1][2] = glm::sin(angleRadian);
    matr[2][2] = glm::cos(angleRadian);

    // Apply transformation
    m_modelMatrix = matr * m_modelMatrix;
    this->updatePosition(matr);
    this->updateUnits(matr);

    // Translate back
    this->translate(point);
}

void SceneObj::rotatey(float angle, const vec3 &point)
{
    // Translate origin to the axis point
    this->translate(-point);

    // Convert angle to radians
    float angleRadian = glm::radians(angle);

    // Make rotation matrix
    mat4 matr(1.0f);
    matr[0][0] = glm::cos(angleRadian);
    matr[2][0] = glm::sin(angleRadian);
    matr[0][2] = -glm::sin(angleRadian);
    matr[2][2] = glm::cos(angleRadian);

    // Apply transformation
    m_modelMatrix = matr * m_modelMatrix;
    this->updatePosition(matr);
    this->updateUnits(matr);

    // Translate back
    this->translate(point);
}

void SceneObj::rotatez(float angle, const vec3 &point)
{
    // Translate origin to the axis point
    this->translate(-point);

    // Convert angle to radians
    float angleRadian = glm::radians(angle);

    // Make rotation matrix
    mat4 matr(1.0f);
    matr[0][0] = glm::cos(angleRadian);
    matr[1][0] = -glm::sin(angleRadian);
    matr[0][1] = glm::sin(angleRadian);
    matr[1][1] = glm::cos(angleRadian);

    // Apply transformation
    m_modelMatrix = matr * m_modelMatrix;
    this->updatePosition(matr);
    this->updateUnits(matr);
    
    // Translate back
    this->translate(point);
}

void SceneObj::rotateItselfx(float angle)
{
    vec3 pos = m_position;
    this->rotatex(angle, pos);
}

void SceneObj::rotateItselfy(float angle)
{
    vec3 pos = m_position;
    this->rotatey(angle, pos);
}

void SceneObj::rotateItselfz(float angle)
{
    vec3 pos = m_position;
    this->rotatez(angle, pos);
}

void SceneObj::rotateAround(float angle, const vec3 &point, const vec3 &vector)
{
    // Translate origin to the axis point
    this->translate(-point);

    // Compute values for rotation matrices    
    vec3 unit = glm::normalize(vector);
    float d = sqrt(unit.y * unit.y + unit.z * unit.z);
    float cosValuex, sinValuex, sinValuey, cosValuey;
    if (d > 0) {
        cosValuex = unit.z / d;
        sinValuex = unit.y / d;
        sinValuey = unit.x;
        cosValuey = d;

        // Rotate to coincide vector with Z axis
        this->rotatex_util(sinValuex, cosValuex);
        this->rotatey_util(sinValuey, cosValuey);
    }

    // Rotate around vector
    this->rotatez(angle);

    // Rotate back
    if (d > 0) {
        this->rotatey_util(-sinValuey, cosValuey);
        this->rotatex_util(-sinValuex, cosValuex);
    }

    // Translate origin back
    this->translate(point);
}

void SceneObj::scale(float sx, float sy, float sz, const vec3 &point)
{
    // Translate origin to the point
    this->translate(-point);
    
    // Make scale matrix
    mat4 matr(1.0f);
    matr[0][0] = sx;
    matr[1][1] = sy;
    matr[2][2] = sz;

    // Apply transformation
    m_modelMatrix = matr * m_modelMatrix;
    this->updatePosition(matr);

    // Translate origin back
    this->translate(point);
}

void SceneObj::scaleItself(float sx, float sy, float sz)
{
    vec3 pos = m_position;
    this->scale(sx, sy, sz, m_position);
}

void SceneObj::setScales(float sx, float sy, float sz)
{
    this->scaleItself(sx/m_scales.x, sy / m_scales.y, sz / m_scales.z);
}

void SceneObj::reflectx()
{
    this->scale(-1.0, 1.0, 1.0);
}

void SceneObj::reflecty()
{
    this->scale(1.0, -1.0, 1.0);
}

void SceneObj::reflectz()
{
    this->scale(1.0, 1.0, -1.0);
}

void SceneObj::reflect(const vec3 &point, const vec3 &normal)
{
    // Translate origin to the plane position
    this->translate(-point);

    // Compute values for rotation matrices    
    vec3 unit = glm::normalize(normal);
    float d = sqrt(unit.y * unit.y + unit.z * unit.z);
    float cosValuex, sinValuex, cosValuey, sinValuey;

    if (d > 0) {
        cosValuex = unit.z / d;
        sinValuex = unit.y / d;
        cosValuey = d;
        sinValuey = unit.x;

        // Rotate to coincide normal with Z axis
        this->rotatex_util(sinValuex, cosValuex);
        this->rotatey_util(sinValuey, cosValuey);
    }

    // Reflect
    this->reflectz();

    // Rotate back
    if (d > 0) {
        this->rotatey_util(-sinValuey, cosValuey);
        this->rotatex_util(-sinValuex, cosValuex);
    }

    // Translate origin back
    this->translate(point);
}

void SceneObj::coincidez(const vec3 &vector)
{
    // Translate origin to the plane position
    vec3 point = m_position;
    this->translate(-point);

    // Compute values for rotation matrices    
    vec3 unit = glm::normalize(vector);
    float d = sqrt(unit.y * unit.y + unit.z * unit.z);
    float cosValuex, sinValuex, cosValuey, sinValuey;

    if (d > 0) {
        cosValuex = unit.z / d;
        sinValuex = unit.y / d;
        cosValuey = d;
        sinValuey = unit.x;

        // Rotate to coincide vector with Z axis
        this->rotatex_util(-sinValuex, cosValuex);
        this->rotatey_util(-sinValuey, cosValuey);
    }

    // Translate origin back
    this->translate(point);
}

void SceneObj::reset()
{
    m_modelMatrix = mat4(1.0f), // Identity matrix
    m_units = mat3(1.0f), // columns of basic unit vectors (1,0,0), (0,1,0) and (0,0,1)
    m_position = vec3(0.0f, 0.0f, 0.0f);
    m_scales = vec3(1.0f, 1.0f, 1.0f);
}

void SceneObj::rotatex_util(float sinValue, float cosValue)
{
    // Make rotation matrix
    mat4 matr(1.0f);
    matr[1][1] = cosValue;
    matr[2][1] = -sinValue;
    matr[1][2] = sinValue;
    matr[2][2] = cosValue;

    // Apply transformation
    m_modelMatrix = matr * m_modelMatrix;
    this->updatePosition(matr);
    this->updateUnits(matr);
}

void SceneObj::rotatey_util(float sinValue, float cosValue)
{
    // Make rotation matrix
    mat4 matr(1.0f);
    matr[0][0] = cosValue;
    matr[2][0] = -sinValue;
    matr[0][2] = sinValue;
    matr[2][2] = cosValue;

    // Apply transformation
    m_modelMatrix = matr * m_modelMatrix;
    this->updatePosition(matr);
    this->updateUnits(matr);
}

void SceneObj::rotatez_util(float sinValue, float cosValue)
{
    // Make rotation matrix
    mat4 matr(1.0f);
    matr[0][0] = cosValue;
    matr[1][0] = -sinValue;
    matr[0][1] = sinValue;
    matr[1][1] = cosValue;

    // Apply transformation
    m_modelMatrix = matr * m_modelMatrix;
    this->updatePosition(matr);
    this->updateUnits(matr);
}

void SceneObj::updatePosition(const mat4 &t)
{
    m_position = t * vec4(m_position, 1.0f);
}

void SceneObj::updateUnits(const mat4 &t)
{
    mat4 units4(1.0f);
    units4[0] = vec4(m_units[0], 0.0f);
    units4[1] = vec4(m_units[1], 0.0f);
    units4[2] = vec4(m_units[2], 0.0f);

    m_units = t * units4;
}