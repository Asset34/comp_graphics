#ifndef OBSERVATIONCONTROLLER2D_H_
#define OBSERVATIONCONTROLLER2D_H_

class ObservationController2D {
public:
    virtual ~ObservationController2D() {};

    virtual void home() = 0;
    
    virtual void setArea(float width, float height) = 0;
    virtual void setAspectRatio(float aspectRatio) = 0;
    virtual void movex(float dx) = 0;
    virtual void movey(float dy) = 0;
    virtual void zoomIn() = 0;
    virtual void zoomOut() = 0;

};

#endif // OBSERVATIONCONTROLLER2D_H_