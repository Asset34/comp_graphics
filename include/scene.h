#ifndef SCENE_H_
#define SCENE_H_

#include "shape.h"
#include "camera.h"
#include "line.h"

class Scene {
public:
    Scene();

    void update();

    void setCameraAspectRatio(float aspectRatio);
    void cameraRotateYaw(float angle);
    void cameraRotatePitch(float angle);
    void cameraZoomIn();
    void cameraZoomOut();

    const vec3 &getBackgroundColor() const;
    const mat4 &getViewMatrix();
    const mat4 &getProjectionMatrix() const;

    const Shape &getShape() const;
    const Line &getLine() const;

private:
    // Cube in NDC coordinates
    void makeTestShape1();
    void shapeInit1();
    // Cube in word coordinates
    void makeTestShape2();
    void shapeInit2();

    void makeTestLine();

    void shapeIdleUpdate();

    Shape m_shape;
    Line m_line;
    Camera m_camera;

    vec3 m_backgroundColor;

};

#endif // SCENE_H_