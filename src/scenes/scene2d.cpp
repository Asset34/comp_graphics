#include "scenes/scene2d.h"

Scene2D::Scene2D()
{
}

ObservationController2D *Scene2D::getObservationController()
{
    return &m_camera;
}

void Scene2D::setBackgroundColor(const glm::vec3 &color)
{
    m_backgroundColor = color;
}

RenderProviderData Scene2D::getRenderProviderData()
{
    RenderProviderData data;
    data.ViewMatrix = m_camera.getViewMatrix();
    data.ProjMatrix = m_camera.getClippingMatrix();
    data.BackgroundColor = m_backgroundColor;

    return data;
}

const std::vector<Renderable *> &Scene2D::getRenderables()
{
    return m_renderables;
}

std::vector<int> Scene2D::getRenderableUpdateVector()
{
    return {};
}

void Scene2D::addRenderable(Renderable *r)
{
    m_renderables.push_back(r);
}

Camera2D &Scene2D::getCamera()
{
    return m_camera;
}
