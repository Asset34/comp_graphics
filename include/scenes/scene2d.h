#ifndef SCENE2D_H_
#define SCENE2D_H_

#include "abstract/scene.h"
#include "abstract/renderprovider.h"
#include "camera2d.h"
#include "objects/axisxy.h"

class Scene2D : public Scene, public RenderProvider {
public:
    Scene2D();
    virtual ~Scene2D() {};
    
    virtual void update() override {};

    ObservationController2D *getObservationController();
    
    virtual const GlobalRenderData &getGlobalRenderData() override;

protected:
    Camera2D &getCamera();

private:
    // Objects
    Camera2D m_camera;
    AxisXY m_xy;

    GlobalRenderData m_globalRenderData;

};

#endif // SCENE2D_H_