#ifndef BASICSCENE_H_
#define BASICSCENE_H_

#include "abstract/scene.h"
#include "camera.h"

class BasicScene : public Scene {
public:
    BasicScene();
    virtual ~BasicScene() {};
    
    Camera &getCamera();
    void setBackgroundColor(const glm::vec3 &color);
    
    virtual RenderProviderData getRenderProviderData() override;
    const std::vector<Renderable*> &getRenderables() override;
    virtual std::vector<int> getRenderableUpdateVector() override;

protected:
    void addRenderable(Renderable *r);

private:
    static const glm::vec3 DEFAULT_BACKGROUND_COLOR; // {0, 0, 0}

    std::vector<Renderable*> m_renderables;
    Camera m_camera;
    glm::vec3 m_backgroundColor;

};

#endif // BASICSCENE_H_