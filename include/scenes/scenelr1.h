#ifndef SCENELR1_H_
#define SCENELR1_H_

#include <vector>
#include "abstract/scene.h"
#include "shape.h"

class SceneLR1 : public Scene {
public:
    SceneLR1();
    ~SceneLR1();

    void update() override;

    RenderProviderData getRenderProviderData() override;
    const std::vector<Renderable*> &getRenderables() override;
    std::vector<int> getRenderableUpdateVector() override;

private:
    Shape m_shape;
    std::vector<Renderable*> m_renderables;

    glm::vec3 m_backgroundColor;

};

#endif // SCENELR1_H_