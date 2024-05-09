#ifndef SCENE2D_H_
#define SCENE2D_H_

#include "abstract/scene.h"
#include "camera2d.h"

class Scene2D : public Scene {
public:
    Scene2D();
    virtual ~Scene2D() {};
    
    ObservationController2D *getObservationController();
    void setBackgroundColor(const glm::vec3 &color);
    
    virtual RenderProviderData getRenderProviderData() override;
    virtual const std::vector<Renderable*> &getRenderables() override;
    virtual std::vector<int> getRenderableUpdateVector() override;

protected:
    void addRenderable(Renderable *r);

    Camera2D &getCamera();

private:
    Camera2D m_camera;

    std::vector<Renderable*> m_renderables;
    glm::vec3 m_backgroundColor;

};

#endif // SCENE2D_H_