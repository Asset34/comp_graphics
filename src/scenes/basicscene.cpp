#include "scenes/basicscene.h"

const glm::vec3 BasicScene::DEFAULT_BACKGROUND_COLOR = {0, 0, 0};

BasicScene::BasicScene()
    :m_backgroundColor(DEFAULT_BACKGROUND_COLOR)
{
}

Camera &BasicScene::getCamera()
{
    return m_camera;
}

void BasicScene::setBackgroundColor(const glm::vec3 &color)
{
    m_backgroundColor = color;
}

RenderProviderData BasicScene::getRenderProviderData()
{
    RenderProviderData data;
    data.ViewMatrix = m_camera.getViewMatrix();
    data.ProjMatrix = m_camera.getProjMatrix();
    data.BackgroundColor = m_backgroundColor;

    return data;
}

const std::vector<Renderable*> &BasicScene::getRenderables()
{
    return m_renderables;
}

std::vector<int> BasicScene::getRenderableUpdateVector()
{
    return {};
}

void BasicScene::addRenderable(Renderable *r)
{
    m_renderables.push_back(r);
}
