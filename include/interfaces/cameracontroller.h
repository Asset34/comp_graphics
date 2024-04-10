#ifndef CAMERACONTROLLER_H_
#define CAMERACONTROLLER_H_

class CameraController {
public:
    virtual ~CameraController() {};

    // Projection control
    virtual void setAspectRatio(float aspectRatio) = 0;
    virtual void setFov(float fov) = 0;

    // Rotation controls
    virtual void rotateYaw(float angle) = 0;
    virtual void rotatePitch(float angle) = 0;

    // Zoom controls
    virtual void ZoomIn() = 0;
    virtual void ZoomOut() = 0;

};

#endif // CAMERACONTROLLER_H_