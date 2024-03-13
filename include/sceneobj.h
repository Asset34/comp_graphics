#ifndef SCENEOBJ_H_
#define SCENEOBJ_H_

#include "glm/glm.hpp"

class SceneObj {
private:
    glm::vec2 center;
    glm::vec2 unit;
    glm::vec2 scaleFactor;

    glm::mat3 modelMatr;

public:
    SceneObj();
    virtual ~SceneObj() = 0;

    void translate(const glm::vec2 &tv);
    void translateTo(const glm::vec2 &pos);

    void rotate(float angle, const glm::vec2 &origin = glm::vec2(0.0f, 0.0f));
    void rotateModel(float angle);
    void rotateModelTo(float angle);

    void scale(const glm::vec2 &sv, const glm::vec2 &origin = glm::vec2(0.0f, 0.0f));
    void scaleModel(const glm::vec2 &sv);
    void scaleModelTo(const glm::vec2 &sv);

    const glm::vec2 &getCenter() const;
    float getAngle() const;
    const glm::mat3 &getModelMatrix() const;

private:
    glm::mat3 createTranslationMatrix(const glm::vec2 &tv) const;
    glm::mat3 createRotationMatrix(float angle, const glm::vec2 &origin) const;
    glm::mat3 createScaleMatrix(const glm::vec2 &sv, const glm::vec2 &origin) const;

    void updateModemMatr(const glm::mat3 &t);
    void updateCenter(const glm::mat3 &t);
    void updateUnit(const glm::mat3 &t);
    void updateScaleFactor(const glm::mat3 &t);

};

#endif // SCENEOBJ_H_