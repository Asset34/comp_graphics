#ifndef OBSERVATIONCONTROLLER2D_H_
#define OBSERVATIONCONTROLLER2D_H_

class ObservationController2D {
public:
    virtual ~ObservationController2D() {};

    virtual void home() = 0;
    
    virtual void setArea(float width, float aspectRatio) = 0;
    virtual void setAspectRatio(float aspectRatio) = 0;
    virtual void movex(float relativeDx) = 0;
    virtual void movey(float relativeDy) = 0;
    virtual void zoomIn() = 0;
    virtual void zoomOut() = 0;

};

#endif // OBSERVATIONCONTROLLER2D_H_