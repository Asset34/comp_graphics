#ifndef SCENE_H_
#define SCENE_H_

#include "shape.h"
#include "camera.h"

class Scene {
public:
    Scene();

    void update();

    void setCameraAspectRatio(float aspectRatio);
    void cameraRotateYaw(float angle);
    void cameraRotatePitch(float angle);

    const vec3 &getBackgroundColor() const;
    const mat4 &getViewMatrix();
    const mat4 &getProjectionMatrix() const;
    const Shape &getShape() const;

private:
    // Cube in NDC coordinates
    void makeTestShape1();
    void shapeInit1();
    // Cube in word coordinates
    void makeTestShape2();
    void shapeInit2();

    void shapeIdleUpdate();

    Shape m_shape;
    Camera m_camera;

    vec3 m_backgroundColor;

};

#endif // SCENE_H_