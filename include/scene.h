#ifndef SCENE_H_
#define SCENE_H_

#include "shape.h"
#include "camera.h"

class Scene {
public:
    Scene();

    void update();

    const vec3 &getBackgroundColor() const;
    const mat4 &getViewMatrix() const;
    const mat4 &getProjectionMatrix() const;
    const Shape &getShape() const;

private:
    Shape m_shape;
    Camera m_camera;

    vec3 m_backgroundColor;

    // Cube in NDC coordinates
    void makeTestShape1();
    void shapeInit1();
    // Cube in word coordinates
    void makeTestShape2();
    void shapeInit2();

    void shapeIdleUpdate();
};

#endif // SCENE_H_