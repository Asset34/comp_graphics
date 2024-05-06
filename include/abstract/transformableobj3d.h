#ifndef GRAPHICOBJ_H_
#define GRAPHICOBJ_H_

#include <vector>
#include "glm/glm.hpp"

using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;

class TransformableObj3D {
public:
    TransformableObj3D();
    virtual ~TransformableObj3D() {};

    const mat4 &getModelMatrix() const;
    const mat4 &getNormalMatrix() const;
    const vec3 &getUnitx() const;
    const vec3 &getUnity() const;
    const vec3 &getUnitz() const;
    const vec3 &getOrigin() const;
    const vec3 &getScales() const;

    void reset();

    void translate(const vec3 &t);
    void translateTo(const vec3 &pos);
    void translateItselfTo(const vec3 &pos);

    void rotatex(float angle, const vec3 &point = {0, 0, 0});
    void rotatey(float angle, const vec3 &point = {0, 0, 0});
    void rotatez(float angle, const vec3 &point = {0, 0, 0});
    void rotateItselfx(float angle);
    void rotateItselfy(float angle);
    void rotateItselfz(float angle);
    void rotateAround(float angle, const vec3 &point, const vec3 &vector);
    void rotateAroundTo(float angle, const vec3 &point, const vec3 &vector);

    void scale(float sx, float sy, float sz, const vec3 &point = {0, 0, 0});
    void scale(float s, const vec3 &point = {0, 0, 0});
    void scaleTo(float sx, float sy, float sz, const vec3 &point = {0, 0, 0});
    void scaleTo(float s, const vec3 &point = {0, 0, 0});
    void scaleItself(float sx, float sy, float sz);
    void scaleItself(float s);
    void scaleItselfTo(float sx, float sy, float sz);
    void scaleItselfTo(float s);

    void reflectx();
    void reflecty();
    void reflectz();
    void reflect(const vec3 &point, const vec3 &normal);

    void coincideWithZ(const vec3 &vector);
    void coincideWithZReverse(const vec3 &vector);

    void resetAngle();
    void trackAngle(bool value);
    float getAngle() const;

protected:
    virtual void transformationCallback();
    virtual const vec3 &selfOrigin() const;

private:
    void translate_base(const vec3 &t);
    void rotatex_base(float angle);
    void rotatey_base(float angle);
    void rotatez_base(float angle);
    void rotatex_base_values(float sinValue, float cosValue);
    void rotatey_base_values(float sinValue, float cosValue);
    void rotatez_base_values(float sinValue, float cosValue);
    void rotateAround_base(float angle, const vec3 &point, const vec3 &vector);
    void scale_base(float sx, float sy, float sz);

    void coincidez_values(const vec3 &vector, float &sinx, float &cosx, float &siny, float &cosy);

    // Default values
    static const vec3 UNITX_DEFAULT;  // {1, 0, 0}
    static const vec3 UNITY_DEFAULT;  // {0, 1, 0}
    static const vec3 UNITZ_DEFAULT;  // {0, 0, 1}
    static const vec3 ORIGIN_DEFAULT; // {0, 0, 0}
    static const vec3 SCALES_DEFAULT; // {1, 1, 1}

    // Transformation matrices
    mat4 m_modelMatrix;
    mat4 m_normalMatrix;
    mat4 m_scaleMatrix;
    
    // Geometrical values
    vec3 m_unitx, m_unity, m_unitz;
    vec3 m_origin;
    vec3 m_scales;

    // Tracking values
    float m_angle;
    bool m_angleTrack;

};

#endif // GRAPHICOBJ_H_