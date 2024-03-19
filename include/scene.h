#ifndef SCENE_H_
#define SCENE_H_

#include "shape.h"

class Scene {
public:
    Scene();
    ~Scene();

    void update();

    const mat4 &getViewMatrix() const;
    const Shape &getShape() const;

private:
    Shape *m_shape;
    mat4 m_viewMatrix;
    vec3 m_backgroundColor;
    
};

#endif // SCENE_H_