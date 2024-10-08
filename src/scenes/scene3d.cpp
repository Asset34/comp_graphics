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

    // Add initial objects for 3D scenes
    this->addObject(&m_xyz);
    this->addObject(&m_grid);
}

ObservationController3D *Scene3D::getObservationController()
{
    return &m_camera;
}

const GlobalRenderData &Scene3D::getGlobalRenderData()
{
    m_globalRenderData.ViewMatrix = m_camera.getViewMatrix();
    m_globalRenderData.ProjMatrix = m_camera.getProjMatrix();
    m_globalRenderData.BackgroundColor = this->getBackgroundColor();

    return m_globalRenderData;
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
