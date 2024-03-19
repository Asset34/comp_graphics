#ifndef SCENEOBJ_H_
#define SCENEOBJ_H_

#include "glm/glm.hpp"

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

class SceneObj {

public:
    SceneObj();
    virtual ~SceneObj() = 0;

    const vec3 &getPosition() const;
    const vec3 &getRotationAngles() const;
    const vec3 &getScaleFactors() const;
    const mat4 &getModelMatrix() const;

    void translate(const vec3 &dv);
    void translateTo(const vec3& pos);
    void rotatex(float angle);
    void rotatey(float angle);
    void rotatez(float angle);
    void rotate(const vec3 &angles, const vec3 &point = vec3(0.0f, 0.0f, 0.0f));
    void rotateTo(const vec3 &angles, const vec3 &point = vec3(0.0f, 0.0f, 0.0f));
    void rotateAround(float angle, const vec3 &axisPos, const vec3 &axisVec);
    void rotateItself(const vec3 &angles);
    void rotateItselfTo(const vec3 &angles);
    void scale(const vec3 &factors, const vec3 &point = vec3(0.0f, 0.0f, 0.0f));
    void scaleTo(const vec3 &factors, const vec3 &point = vec3(0.0f, 0.0f, 0.0f));
    void scaleItself(const vec3 &factors);
    void scaleItselfTo(const vec3 &factors);
    void reflect(const vec3 &planePos, const vec3 &planeNormal);
    void reflectxy();

    void reset();

private:
    vec2 computeAuxiliaryAngles(const vec3 &v);

    vec3 m_position;
    vec3 m_rotationAngles;
    vec3 m_scaleFactors;
    mat4 m_modelMatrix;

};

#endif // SCENEOBJ_H_