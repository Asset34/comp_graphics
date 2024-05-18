#ifndef SCENE3D_H_
#define SCENE3D_H_

#include "abstract/scene.h"
#include "camera3d.h"
#include "objects/axisxyz.h"
#include "objects/plane.h"

class Scene3D : public Scene {
public:
    Scene3D();
    virtual ~Scene3D() {};
    
    ObservationController3D *getObservationController();
    void setBackgroundColor(const glm::vec3 &color);
    
    virtual GlobalRenderData getGlobalRenderData() override;
    virtual const std::vector<Renderable*> &getRenderables() override;
    virtual std::vector<int> getRenderableUpdateVector() override;

protected:
    void addRenderable(Renderable *r);
    int getNextRenderableUpdateVectorIndex();

    Camera3D &getCamera();
    AxisXYZ &getXYZ();
    Plane &getGrid();

private:
    Camera3D m_camera;
    AxisXYZ m_xyz;
    Plane m_grid;

    std::vector<Renderable*> m_renderables;
    glm::vec3 m_backgroundColor;

};

#endif // SCENE3D_H_