#ifndef TRANSFORMABLECOBJ2D_H_
#define TRANSFORMABLECOBJ2D_H_

#include "geometry.h"
#include <vector>
#include "glm/glm.hpp"

class TransformableObj2D {
public:
    TransformableObj2D();
    virtual ~TransformableObj2D() {};

    const mat3 &getModelMatrix() const;
    const mat3 &getNormalMatrix() const;
    const vec2 &getUnitx() const;
    const vec2 &getUnity() const;
    const vec2 &getOrigin() const;
    const vec2 &getScales() const;

    void reset();

    void translate(const vec2 &t);
    void translateTo(const vec2 &pos);
    void translateItselfTo(const vec2 &pos);
    void rotate(float angle, const vec2 &point = {0, 0});
    void rotateItself(float angle);
    void scale(float sx, float sy, const vec2 &point = {0, 0});
    void scale(float s, const vec2 &point = {0, 0});
    void scaleTo(float sx, float sy, const vec2 &point = {0, 0});
    void scaleTo(float s, const vec2 &point = {0, 0});
    void scaleItself(float sx, float sy);
    void scaleItself(float s);
    void scaleItselfTo(float sx, float sy);
    void scaleItselfTo(float s);

    void reflectx();
    void reflecty();

    void resetAngle();
    void trackAngle(bool value);
    float getAngle() const;

protected:
    virtual void transformationCallback();
    virtual const vec2 &selfOrigin() const;

private:
    void translate_base(const vec2 &t);
    void rotate_base(float angle);
    void scale_base(float sx, float sy);

    // Default values
    static const vec2 UNITX_DEFAULT;  // {1, 0}
    static const vec2 UNITY_DEFAULT;  // {0, 1}
    static const vec2 ORIGIN_DEFAULT; // {0, 0}
    static const vec2 SCALES_DEFAULT; // {1, 1}

    // Transformation matrices
    mat3 m_modelMatrix;
    mat3 m_normalMatrix;
    mat3 m_scaleMatrix;

    // Geometrical values
    vec2 m_unitx, m_unity;
    vec2 m_origin;
    vec2 m_scales;

    // Tracking values
    float m_angle;
    bool m_angleTrack;

};

#endif // TRANSFORMABLECOBJ2D_H_