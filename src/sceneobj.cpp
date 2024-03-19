#include "sceneobj.h"

#include <cmath>

SceneObj::SceneObj()
    :m_position(vec3(0.0f, 0.0f, 0.0f)),
     m_rotationAngles(vec3(0.0f, 0.0f, 0.0f)),
     m_scaleFactors(vec3(1.0f, 1.0f, 1.0f)),
     m_modelMatrix(mat4(1.0f)) // Identity matrix
{
}

SceneObj::~SceneObj()
{
}

const vec3 &SceneObj::getPosition() const
{
    return m_position;
}

const vec3 &SceneObj::getRotationAngles() const
{
    return m_rotationAngles;
}

const vec3 &SceneObj::getScaleFactors() const
{
    return m_scaleFactors;
}

const mat4 &SceneObj::getModelMatrix() const
{
    return m_modelMatrix;
}

void SceneObj::translate(const vec3 &dv)
{
    // Make translation matrix
    mat4 translationMatrix(1.0f);
    translationMatrix[3] = vec4(dv, 1.0f);

    // Apply
    m_modelMatrix = translationMatrix * m_modelMatrix;

    // Update position
    m_position += dv;
}

void SceneObj::translateTo(const vec3 &pos)
{
    this->translate(-m_position);
    this->translate(pos);
}

void SceneObj::rotatex(float angle)
{
    // Convert angle to radians
    float angleRadian = glm::radians(angle);

    // Make rotation matrix
    mat4 rotationMatrix(1.0f);
    rotationMatrix[1][1] = cos(angleRadian);
    rotationMatrix[2][1] = -sin(angleRadian);
    rotationMatrix[1][2] = sin(angleRadian);
    rotationMatrix[2][2] = cos(angleRadian);

    // Apply
    m_modelMatrix = rotationMatrix * m_modelMatrix;

    // Update rotation angles
    m_rotationAngles.x += angle;
}

void SceneObj::rotatey(float angle)
{
    // Convert angle to radians
    float angleRadian = glm::radians(angle);

    // Make rotation matrix
    mat4 rotationMatrix(1.0f);
    rotationMatrix[0][0] = cos(angleRadian);
    rotationMatrix[2][0] = -sin(angleRadian);
    rotationMatrix[0][2] = sin(angleRadian);
    rotationMatrix[2][2] = cos(angleRadian);

    // Apply
    m_modelMatrix = rotationMatrix * m_modelMatrix;

    // Update rotation angles
    m_rotationAngles.y += angle;
}

void SceneObj::rotatez(float angle)
{
    // Convert angle to radians
    float angleRadian = glm::radians(angle);

    // Make rotation matrix
    mat4 rotationMatrix(1.0f);
    rotationMatrix[0][0] = cos(angleRadian);
    rotationMatrix[1][0] = -sin(angleRadian);
    rotationMatrix[0][1] = sin(angleRadian);
    rotationMatrix[1][1] = cos(angleRadian);

    // Apply
    m_modelMatrix = rotationMatrix * m_modelMatrix;

    // Update rotation angles
    m_rotationAngles.z += angle;
}

void SceneObj::rotate(const vec3 &angles, const vec3 &point)
{
    // Translate origin to the point
    this->translate(-point);

    // Rotate
    this->rotatex(angles.x);
    this->rotatey(angles.y);
    this->rotatez(angles.z);

    // Translate origin back
    this->translate(point);
}

void SceneObj::rotateTo(const vec3 &angles, const vec3 &point)
{
    this->rotate(-m_rotationAngles, point);
    this->rotate(angles, point);
}

void SceneObj::rotateAround(float angle, const vec3 &axisPos, const vec3 &axisVec)
{
    // Translate origin to the axis point
    this->translate(-axisPos);

    // Compute auxiliary rotation angles
    vec2 auxiliaryAngles = computeAuxiliaryAngles(axisVec);

    // Perform auxiliary rotations
    // to coincide specified axis with Z axis
    this->rotatex(auxiliaryAngles.x);
    this->rotatey(auxiliaryAngles.y);

    // Rotate
    this->rotatez(angle);

    // Undo auxiliary rotations
    this->rotatey(-auxiliaryAngles.x);
    this->rotatex(-auxiliaryAngles.y);

    // Translate origin back
    this->translate(-axisPos);
}

void SceneObj::rotateItself(const vec3 &angles)
{
    this->rotate(angles, m_position);
}

void SceneObj::rotateItselfTo(const vec3 &angles)
{
    this->rotateTo(angles, m_position);
}

void SceneObj::scale(const vec3 &factors, const vec3 &point)
{
    // Translate origin to the point
    this->translate(-point);

    // Make scale matrix
    mat4 scaleMatrix(1.0f);
    scaleMatrix[0][0] = factors.x;
    scaleMatrix[1][1] = factors.y;
    scaleMatrix[2][2] = factors.z;

    // Apply matrix
    m_modelMatrix = scaleMatrix * m_modelMatrix;

    // Translate origin back
    this->translate(point);

    // Update scale factors
    m_scaleFactors *= factors;

    // Update rotation angles
    if (m_scaleFactors.x < 0) {
        m_rotationAngles.y = -m_rotationAngles.y;
        m_rotationAngles.z = -m_rotationAngles.z;
    }
    if (m_scaleFactors.y < 0) {
        m_rotationAngles.x = -m_rotationAngles.x;
        m_rotationAngles.z = -m_rotationAngles.z;
    }
    if (m_scaleFactors.z < 0) {
        m_rotationAngles.x = -m_rotationAngles.x;
        m_rotationAngles.y = -m_rotationAngles.y;
    }
}

void SceneObj::scaleTo(const vec3 &factors, const vec3 &point)
{
    vec3 reverseFactors;
    reverseFactors.x = 1.0 / m_scaleFactors.x;
    reverseFactors.y = 1.0 / m_scaleFactors.y;
    reverseFactors.z = 1.0 / m_scaleFactors.z;

    this->scale(reverseFactors, point);
    this->scale(factors, point);
}

void SceneObj::scaleItself(const vec3 &factors)
{
    this->scale(factors, m_position);
}

void SceneObj::scaleItselfTo(const vec3 &factors)
{
    this->scaleTo(factors, m_position);
}

void SceneObj::reflect(const vec3 &planePos, const vec3 &planeNormal)
{
    // Translate origin to the plane position
    this->translate(-planePos);

    // Compute auxiliary rotation angles
    vec2 auxiliaryAngles = computeAuxiliaryAngles(planeNormal);

    // Perform auxiliary rotations
    // to coincide plane normal with Z axis
    this->rotatex(auxiliaryAngles.x);
    this->rotatey(auxiliaryAngles.y);

    // Reflect relative to the XY plane
    reflectxy();

    // Undo auxiliary rotations
    this->rotatex(-auxiliaryAngles.x);
    this->rotatey(-auxiliaryAngles.y);

    // Translate origin back
    this->translate(planePos);
}

void SceneObj::reflectxy()
{
    vec3 factors(m_scaleFactors);
    factors.z = -factors.z;

    this->scale(factors);
}

void SceneObj::reset()
{
    m_position = vec3(0.0f, 0.0f, 0.0f);
    m_rotationAngles = vec3(0.0f, 0.0f, 0.0f);
    m_scaleFactors = vec3(1.0f, 1.0f, 1.0f);
    m_modelMatrix = mat4(1.0f);
}

vec2 SceneObj::computeAuxiliaryAngles(const vec3 &v) {
    vec3 unit = glm::normalize(v);
    vec2 auxiliaryAngles;

    float unitProjLength = sqrt(unit.y * unit.y + unit.z * unit.z);
    float anglexRadians = acos(unit.z / unitProjLength);
    float angleyRadians = acos(unitProjLength);

    auxiliaryAngles.x = glm::degrees(anglexRadians);
    auxiliaryAngles.y = glm::degrees(angleyRadians);

    return auxiliaryAngles;
}