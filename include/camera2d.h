#ifndef CAMERA2D_H_
#define CAMERA2D_H_

#include "abstract/transformableobj2d.h"
#include "interfaces/observationcontroller2d.h"

using glm::mat4;
using glm::vec4;

class Camera2D : public TransformableObj2D, public ObservationController2D {
public:
    Camera2D(float height = 100, float aspectRatio = 1.0);
    ~Camera2D();

    const mat4 &getViewMatrix();
    const mat4 &getClippingMatrix();

    void home() override;
    void setHome();

    void setZoomLimitsFlag(bool flag);
    void setZoomLimits(float min, float max);
    void setZoomFactor(float factor);

    void setArea(float height, float aspectRatio) override;
    void setAspectRatio(float aspectRatio) override;
    void movex(float dx) override;
    void movey(float dy) override;
    void zoomIn() override;
    void zoomOut() override;

private:
    void computeClipMatrix();

    static constexpr const float ZOOM_FACTOR_DEFAULT = 0.9;
    static constexpr const float ZOOM_LIMIT_MIN_DEFAULT = 0.1;
    static constexpr const float ZOOM_LIMIT_MAX_DEFAULT = 10;

    mat4 m_viewMatrix;
    mat4 m_clipMatrix;

    // Camera values
    float m_aspectRatio;
    float m_width, m_height;

    // Zoom values
    float m_zoom;
    float m_zoomFactor;
    float m_zoomMin, m_zoomMax;
    bool m_zoomLimitFlag;

    vec2 m_originHome;

};

#endif // CAMERA2D_H_