#include "sceneobj.h"

#include <cmath>

SceneObj::SceneObj()
    :center(glm::vec2(0.0f, 0.0f)),
     unit(glm::vec2(0.0f, 1.0f)),
     scaleFactor(glm::vec2(1.0f, 1.0f)),
     modelMatr(glm::mat3(1.0f))
{
}

void SceneObj::translate(const glm::vec2 &tv)
{
    glm::mat3 translationMatr = this->createTranslationMatrix(tv);

    this->updateModemMatr(translationMatr);
    this->updateCenter(translationMatr);
}

void SceneObj::translateTo(const glm::vec2 &pos)
{
    // Compute translation vector
    glm::vec2 vt = pos - center;

    // Translate
    this->translate(vt);
}

void SceneObj::rotate(float angle, const glm::vec2 &origin)
{
    glm::mat3 rotationMatrix = this->createRotationMatrix(angle, origin);

    this->updateModemMatr(rotationMatrix);
    this->updateCenter(rotationMatrix);
    this->updateUnit(rotationMatrix);
}

void SceneObj::rotateModel(float angle)
{
    this->rotate(angle, center);
}

void SceneObj::rotateModelTo(float angle)
{
    float currentAngle = this->getAngle();
    float dAngle = angle - currentAngle;

    this->rotateModel(dAngle);
}

void SceneObj::scale(const glm::vec2 &sv, const glm::vec2 &origin)
{
    glm::mat3 scaleMatrix = this->createScaleMatrix(sv, origin);

    this->updateModemMatr(scaleMatrix);
    this->updateCenter(scaleMatrix);
    this->updateScaleFactor(scaleMatrix);
}

void SceneObj::scaleModel(const glm::vec2 &sv)
{
    this->scale(sv, center);
}

void SceneObj::scaleModelTo(const glm::vec2 &sv)
{
    float sx = sv.x / scaleFactor.x;
    float sy = sv.y / scaleFactor.y;
    glm::vec2 dScale(sx, sy);

    this->scaleModel(dScale);
}

const glm::vec2 &SceneObj::getCenter() const
{
    return this->center;
}

float SceneObj::getAngle() const
{
    glm::vec2 originalUnit(0.0f, 1.0f);

    // Comoute value (using Dot Product)
    float dotProduct = originalUnit.x * unit.x + originalUnit.y * unit.y;
    float denominator= glm::length(originalUnit) * glm::length(unit);
    float angleR = acos(dotProduct / denominator);

    // Compute sign (using Perp Dot Product)
    float perpDotProduct = originalUnit.x * unit.y - originalUnit.y * unit.x;
    if (perpDotProduct < 0) {
        angleR = -angleR;
    }

    return glm::degrees(angleR);
}

const glm::mat3 &SceneObj::getModelMatrix() const
{
    return modelMatr;
}

glm::mat3 SceneObj::createTranslationMatrix(const glm::vec2 &tv) const
{
    glm::mat3 matr(1.0f);
    matr[2] = glm::vec3(tv.x, tv.y, 1.0f);

    return matr;
}

glm::mat3 SceneObj::createRotationMatrix(float angle, const glm::vec2 &origin) const
{
    // Transform angle from degree to radian
    float angleR = glm::radians(angle);

    // Steps:
    // 1. translate system to the origin
    // 2. rotate
    // 3. translate back
    glm::mat3 translationMatr1(1.0f), rotationMatr(1.0f), translationMatr2(1.0f);
    translationMatr1[2] = glm::vec3(-origin.x, -origin.y, 1.0f);
    rotationMatr[0] = glm::vec3(cos(angleR), sin(angleR), 1.0f);
    rotationMatr[1] = glm::vec3(-sin(angleR), cos(angleR), 1.0f);
    translationMatr2[2] = glm::vec3(origin.x, origin.y, 1.0f);

    return translationMatr2 * rotationMatr * translationMatr1;
}

glm::mat3 SceneObj::createScaleMatrix(const glm::vec2 &sv, const glm::vec2 &origin) const
{
    glm::mat3 matr(1.0f);

    // Steps:
    // 1. translate system to the origin
    // 2. scale
    // 3. translate back
    glm::mat3 translationMatr1(1.0f), scaleMatr(1.0f), translationMatr2(1.0f);
    translationMatr1[2] = glm::vec3(-origin.x, -origin.y, 1.0f);
    scaleMatr[0][0] = sv.x;
    scaleMatr[1][1] = sv.y;
    translationMatr2[2] = glm::vec3(origin.x, origin.y, 1.0f);

    return translationMatr2 * scaleMatr * translationMatr1;
}

void SceneObj::updateModemMatr(const glm::mat3 &t)
{
    modelMatr = t * modelMatr;
}

void SceneObj::updateCenter(const glm::mat3 &t)
{
    center = t * glm::vec3(center.x, center.y, 1.0f);
}

void SceneObj::updateUnit(const glm::mat3 &t)
{
    unit = t * glm::vec3(unit.x, unit.y, 1.0f);
    glm::normalize(unit);
}

void SceneObj::updateScaleFactor(const glm::mat3 &t)
{
    scaleFactor = t * glm::vec3(scaleFactor.x, scaleFactor.y, 1.0f);
}
