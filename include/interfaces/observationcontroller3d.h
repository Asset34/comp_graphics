#ifndef OBSERVATIONCONTROLLER3D_H_
#define OBSERVATIONCONTROLLER3D_H_

class ObservationController3D {
public:
    virtual ~ObservationController3D() {};

    virtual void home() = 0;

    virtual void setAspectRatio(float aspectRatio) = 0;
    virtual void rotateHorizontal(float angle) = 0;
    virtual void rotateVertical(float angle) = 0;
    virtual void zoomIn() = 0;
    virtual void zoomOut() = 0;

};

#endif // OBSERVATIONCONTROLLER3D_H_