#ifndef CAMERA_H_
#define CAMERA_H_

#include "abstract/transformableobj.h"

class Camera : public TransformableObj {
public:
    Camera(float hfov = 45.0, float aspectRatio = 1.0, float near = 0.01, float far = 100.0);
    ~Camera();

    const mat4 &getViewMatrix();
    const mat4 &getProjMatrix() const;

    void setAspectRatio(float aspectRatio);
    void setFov(float fov);
    void setVolume(float hfov, float aspectRatio, float near, float far);
    
    void setNoProjection();
    void setOrthoProjection();
    void setPerspectiveProjection();

    void setYawLimits(float min, float max);
    void setPitchLimits(float min, float max);
    // void setZoomLimits(float min, float max);

    void rotateYaw(float angle);
    void rotatePitch(float angle);

    void ZoomIn();
    void ZoomOut();

protected:
    virtual void transformationCallback() override;

private:
    void lookAt(const vec3 &point = {0, 0, 0});
    void computeTop(float fov);
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

    static constexpr const float ZOOM_IN_FACTOR = 0.9;
    static constexpr const float ZOOM_OUT_FACTOR = 0.9;

    // Camera values
    float m_yaw, m_pitch;

    // Volume
    float m_right, m_top, m_near, m_far;

    // Limits
    float m_yawMin, m_yawMax;
    float m_pitchMin, m_pitchMax;
    // float m_zoomMin, m_zoomMax;

    // Flags
    bool m_yawLimit, m_pitchLimit, m_zoomLimit;
    bool m_callbackOccured;

};

#endif // CAMERA_H_