#include "scenes/scene2d.h"

Scene2D::Scene2D()
{
    // Setup default XY
    m_xy.setSize(15);
    m_xy.setColorX({0.95, 0.3, 0.4});
    m_xy.setColorY({0.5, 0.8, 0.25});
    m_xy.setWidth(3);

    // Add default renderable objects
    m_renderables.push_back(&m_xy);

    // Setup default background color
    m_backgroundColor = {0.25, 0.25, 0.25};
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

int Scene2D::getNextRenderableUpdateVectorIndex()
{
    return 1;
}
Camera2D &Scene2D::getCamera()
{
    return m_camera;
}
