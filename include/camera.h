#ifndef CAMERA_H_
#define CAMERA_H_

#include "abstract/transformableobj.h"
#include "interfaces/cameracontroller.h"

class Camera : public TransformableObj, public CameraController {
public:
    Camera(float hfov = 45.0, float aspectRatio = 1.0, float near = 0.01, float far = 100.0);
    ~Camera();

    const mat4 &getViewMatrix();
    const mat4 &getProjMatrix() const;

    void setAspectRatio(float aspectRatio) override;
    void setFov(float fov) override;
    void setVolume(float hfov, float aspectRatio, float near, float far) override;
    
    void setNoProjection() override;
    void setOrthoProjection() override;
    void setPerspectiveProjection() override;

    void setYawLimits(float min, float max);
    void setPitchLimits(float min, float max);
    void setZoomLimits(float min, float max);
    void setZoomFactor(float factor);

    void rotateYaw(float angle) override;
    void rotatePitch(float angle) override;
    void ZoomIn() override;
    void ZoomOut() override;

    void setZoomLimitsFlag(bool flag);
    void setYawLimitsFlag(bool flag);
    void setPitchLimitsFlag(bool flag);

private:
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

    static constexpr const float ZOOM_FACTOR_DEFAULT = 0.9;
    static constexpr const float YAW_LIMIT_MIN_DEFAULT = -90;
    static constexpr const float YAW_LIMIT_MAX_DEFAULT = 90;
    static constexpr const float PITCH_LIMIT_MIN_DEFAULT = -90;
    static constexpr const float PITCH_LIMIT_MAX_DEFAULT = 90;
    static constexpr const float ZOOM_LIMIT_MIN_DEFAULT = 0.1;
    static constexpr const float ZOOM_LIMIT_MAX_DEFAULT = 10;

    // Camera values
    float m_yaw, m_pitch;
    float m_zoom;
    float m_zoomFactor;

    // Volume
    float m_right, m_top, m_near, m_far;

    // Limits
    float m_yawMin, m_yawMax;
    float m_pitchMin, m_pitchMax;
    float m_zoomMin, m_zoomMax;

    // Flags
    bool m_yawLimitFlag, m_pitchLimitFlag, m_zoomLimitFlag;
    bool m_callbackOccured;

};

#endif // CAMERA_H_