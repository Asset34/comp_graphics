#ifndef BASICSCENE_H_
#define BASICSCENE_H_

#include "abstract/scene.h"
#include "interfaces/cameracontroller.h"
#include "camera.h"

class BasicScene : public Scene {
public:
    BasicScene();
    virtual ~BasicScene() {};
    
    CameraController *getCameraController();
    void setBackgroundColor(const glm::vec3 &color);
    
    virtual RenderProviderData getRenderProviderData() override;
    virtual const std::vector<Renderable*> &getRenderables() override;
    virtual std::vector<int> getRenderableUpdateVector() override;

protected:
    void addRenderable(Renderable *r);
    Camera &getCamera();

private:
    static const glm::vec3 DEFAULT_BACKGROUND_COLOR; // {0, 0, 0}

    std::vector<Renderable*> m_renderables;
    Camera m_camera;
    glm::vec3 m_backgroundColor;

};

#endif // BASICSCENE_H_