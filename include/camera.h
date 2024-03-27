#ifndef CAMERA_H_
#define CAMERA_H_

#include "sceneobj.h"

class Camera : public SceneObj {
public:
    Camera(float hfov = 45.0, float aspectRatio = 1.0, float near = 0.01, float far = 100.0);
    ~Camera();

    const mat4 &getViewMatrix();
    const mat4 &getProjectionMatrix() const;

    void setAspectRatio(float aspectRatio);
    void setHFov(float hfov);
    void setVolume(float hfov, float aspectRatio, float near, float far);
    void setNoProjection();
    void setOrthoProjection();
    void setPerspectiveProjection();

    void lookAt(const vec3 &point = vec3(0.0f, 0.0f, 0.0f));

private:
    void computeTop(float hfov);
    void computeRight(float aspectRatio);
    void computeProjection();

    enum ProjType {
        No,
        Ortho,
        Perspective
    };

    mat4 m_viewMatrix;
    mat4 m_projMatrix;
    ProjType m_projType;

    float m_right, m_top;
    float m_near, m_far;

};

#endif // CAMERA_H_