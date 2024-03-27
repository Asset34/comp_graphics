#ifndef SCENEOBJ_H_
#define SCENEOBJ_H_

#include "glm/glm.hpp"

using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;

class SceneObj {

public:
    SceneObj();
    virtual ~SceneObj() = 0;

    const mat4 &getModelMatrix() const;
    const mat3 &getUnits() const;
    const vec3 &getPosition() const;
    const vec3 &getScales() const;

    void translate(const vec3 &t);
    void setPosition(const vec3 &pos);

    void rotatex(float angle, const vec3 &point = {0.0f, 0.0f, 0.0f});
    void rotatey(float angle, const vec3 &point = {0.0f, 0.0f, 0.0f});
    void rotatez(float angle, const vec3 &point = {0.0f, 0.0f, 0.0f});
    void rotateItselfx(float angle);
    void rotateItselfy(float angle);
    void rotateItselfz(float angle);
    void rotateAround(float angle, const vec3 &point, const vec3 &vector);
    // void setAngles(float anglex, float angley, float anglez);

    void scale(float sx, float sy, float sz, const vec3 &point = {0.0f, 0.0f, 0.0f});
    void scaleItself(float sx, float sy, float sz);
    void setScales(float sx, float sy, float sz);

    void reflectx();
    void reflecty();
    void reflectz();
    void reflect(const vec3 &point, const vec3 &normal);

    void coincidez(const vec3 &vector);

    void reset();

private:
    void rotatex_util(float sinValue, float cosValue);
    void rotatey_util(float sinValue, float cosValue);
    void rotatez_util(float sinValue, float cosValue);

    void updatePosition(const mat4 &t);
    void updateUnits(const mat4 &t);

    mat4 m_modelMatrix;
    
    mat3 m_units;
    vec3 m_position;
    vec3 m_scales;
    // vec3 m_angles;

};

#endif // SCENEOBJ_H_