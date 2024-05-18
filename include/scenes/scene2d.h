#ifndef SCENE2D_H_
#define SCENE2D_H_

#include "abstract/scene.h"
#include "camera2d.h"
#include "objects/axisxy.h"


class Scene2D : public Scene {
public:
    Scene2D();
    virtual ~Scene2D() {};
    
    ObservationController2D *getObservationController();
    void setBackgroundColor(const glm::vec3 &color);
    
    virtual GlobalRenderData getGlobalRenderData() override;
    virtual const std::vector<Renderable*> &getRenderables() override;
    virtual std::vector<int> getRenderableUpdateVector() override;

protected:
    void addRenderable(Renderable *r);
    int getNextRenderableUpdateVectorIndex();

    Camera2D &getCamera();

private:
    Camera2D m_camera;
    AxisXY m_xy;

    std::vector<Renderable*> m_renderables;
    glm::vec3 m_backgroundColor;

};

#endif // SCENE2D_H_