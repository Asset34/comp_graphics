#ifndef SCENE_H_
#define SCENE_H_

#include "shape.h"

class Scene {
public:
    Scene();

    void update();

    const vec3 &getBackgroundColor() const;
    const mat4 &getViewMatrix() const;
    const Shape &getShape() const;

private:
    Shape m_shape;
    mat4 m_viewMatrix;
    vec3 m_backgroundColor;

    void makeTestShape1();
};

#endif // SCENE_H_