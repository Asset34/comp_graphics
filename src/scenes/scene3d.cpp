#include "scenes/scene3d.h"

const glm::vec3 Scene3D::DEFAULT_BACKGROUND_COLOR = {0, 0, 0};

Scene3D::Scene3D()
    :m_backgroundColor(DEFAULT_BACKGROUND_COLOR)
{
}

ObservationController3D *Scene3D::getObservationController()
{
    return &m_camera;
}

void Scene3D::setBackgroundColor(const glm::vec3 &color)
{
    m_backgroundColor = color;
}

RenderProviderData Scene3D::getRenderProviderData()
{
    RenderProviderData data;
    data.ViewMatrix = m_camera.getViewMatrix();
    data.ProjMatrix = m_camera.getProjMatrix();
    data.BackgroundColor = m_backgroundColor;

    return data;
}

const std::vector<Renderable*> &Scene3D::getRenderables()
{
    return m_renderables;
}

std::vector<int> Scene3D::getRenderableUpdateVector()
{
    return {};
}

void Scene3D::addRenderable(Renderable *r)
{
    m_renderables.push_back(r);
}

Camera3D &Scene3D::getCamera()
{
    return m_camera;
}
