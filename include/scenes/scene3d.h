#ifndef SCENE3D_H_
#define SCENE3D_H_

#include "abstract/scene.h"
#include "camera3d.h"

class Scene3D : public Scene {
public:
    Scene3D();
    virtual ~Scene3D() {};
    
    ObservationController3D *getObservationController();
    void setBackgroundColor(const glm::vec3 &color);
    
    virtual RenderProviderData getRenderProviderData() override;
    virtual const std::vector<Renderable*> &getRenderables() override;
    virtual std::vector<int> getRenderableUpdateVector() override;

protected:
    void addRenderable(Renderable *r);
    Camera3D &getCamera();

private:
    static const glm::vec3 DEFAULT_BACKGROUND_COLOR; // {0, 0, 0}

    std::vector<Renderable*> m_renderables;
    Camera3D m_camera;
    glm::vec3 m_backgroundColor;

};

#endif // SCENE3D_H_