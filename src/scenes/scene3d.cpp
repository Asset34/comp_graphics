#include "scenes/scene3d.h"

Scene3D::Scene3D()
{
    // Setup default XYZ
    m_xyz.setSize(15);
    m_xyz.setColorX({0.95, 0.3, 0.4});
    m_xyz.setColorY({0.5, 0.8, 0.25});
    m_xyz.setColorZ({0.3, 0.55, 0.9});
    m_xyz.setWidth(3);
    m_xyz.translate({0, 1, 0});

    // Setup default Grid
    m_grid.setColor({0.3, 0.3, 0.3});
    m_grid.setGridThickness(2);
    m_grid.defineGrid(20, 10, 10);
    m_grid.setNormal({0, 1, 0});

    // Setup default Camera
    m_camera.setPerspectiveProjection();
    m_camera.setVolume(90, 1.0, 0.01, 10000);
    m_camera.setZoomLimits(0.3, 50);
    m_camera.setZoomLimitsFlag(true);
    m_camera.translate({0, 0, 100});
    m_camera.rotateHorizontal(40);
    m_camera.rotateVertical(-40);
    m_camera.setHome();

    // Add default renderable objects
    m_renderables.push_back(&m_xyz);
    m_renderables.push_back(&m_grid);

    // Setup default background color
    m_backgroundColor = {0.25, 0.25, 0.25};
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

int Scene3D::getNextRenderableUpdateVectorIndex()
{
    return 2;
}
Camera3D &Scene3D::getCamera()
{
    return m_camera;
}

AxisXYZ &Scene3D::getXYZ()
{
    return m_xyz;
}

Plane &Scene3D::getGrid()
{
    return m_grid;
}
