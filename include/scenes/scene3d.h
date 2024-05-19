#ifndef SCENE3D_H_
#define SCENE3D_H_

#include "abstract/renderprovider.h"
#include "abstract/scene.h"
#include "camera3d.h"
#include "objects/axisxyz.h"
#include "objects/plane.h"

class Scene3D : public Scene, public RenderProvider {
public:
    Scene3D();
    virtual ~Scene3D() {};
    
    virtual void update() override {};

    ObservationController3D *getObservationController();
    void setBackgroundColor(const Color &color);
    
    virtual const GlobalRenderData &getGlobalRenderData() override;

protected:

    Camera3D &getCamera();
    AxisXYZ &getXYZ();
    Plane &getGrid();

private:
    // Objects
    Camera3D m_camera;
    AxisXYZ m_xyz;
    Plane m_grid;

    GlobalRenderData m_globalRenderData;

};

#endif // SCENE3D_H_