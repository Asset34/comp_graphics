#ifndef CAMERA3D_H_
#define CAMERA3D_H_

#include "abstract/transformableobj.h"
#include "interfaces/observationcontroller3d.h"

class Camera3D : public TransformableObj, public ObservationController3D {
public:
    Camera3D(float hfov = 45.0, float aspectRatio = 1.0, float near = 0.01, float far = 100.0);
    ~Camera3D();

    const mat4 &getViewMatrix();
    const mat4 &getProjMatrix() const;

    void home() override;

    void setAspectRatio(float aspectRatio) override;
    void setFov(float fov);
    void setVolume(float hfov, float aspectRatio, float near, float far);
    
    void setNoProjection();
    void setOrthoProjection();
    void setPerspectiveProjection();

    void setHorizontalLimits(float min, float max);
    void setVerticalLimits(float min, float max);
    void setZoomLimits(float min, float max);
    void setZoomFactor(float factor);

    void translateForward(float d) override;
    void translateSide(float d) override;
    void rotateHorizontal(float angle) override;
    void rotateVertical(float angle) override;
    void zoomIn() override;
    void zoomOut() override;

    void setZoomLimitsFlag(bool flag);
    void setHorizontalLimitsFlag(bool flag);
    void setVerticalLimitsFlag(bool flag);

    vec3 getForwardUnit() const;
    vec3 getSideUnit() const;

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
    static constexpr const float HORIZONTAL_MIN_DEFAULT = -90;
    static constexpr const float HORIZONTAL_MAX_DEFAULT = 90;
    static constexpr const float VERTICAL_MIN_DEFAULT = -90;
    static constexpr const float VERTICAL_MAX_DEFAULT = 90;
    static constexpr const float ZOOM_LIMIT_MIN_DEFAULT = 0.1;
    static constexpr const float ZOOM_LIMIT_MAX_DEFAULT = 10;

    // Camera values
    vec3 m_viewPoint;
    float m_horizontal, m_vertical;
    float m_zoom;
    float m_zoomFactor;

    // Volume
    float m_right, m_top, m_near, m_far;

    // Limits
    float m_horizontalMin, m_horizontalMax;
    float m_verticalMin, m_verticalMax;
    float m_zoomMin, m_zoomMax;

    // Flags
    bool m_horizontalLimitFlag, m_verticalLimitFlag, m_zoomLimitFlag;

};

#endif // CAMERA3D_H_