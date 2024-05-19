#include "scenes/scene2d.h"

Scene2D::Scene2D()
{
    // Setup default XY
    m_xy.setSize(100000);
    m_xy.setColorX({0.95, 0.3, 0.4});
    m_xy.setColorY({0.5, 0.8, 0.25});
    m_xy.setWidth(3);

    // Add initial objects for 2D scenes
    this->addObject(&m_xy);
}

ObservationController2D *Scene2D::getObservationController()
{
    return &m_camera;
}

const GlobalRenderData &Scene2D::getGlobalRenderData()
{
    // Setup Global Transformation Matrices
    m_globalRenderData.ViewMatrix = m_camera.getViewMatrix();
    m_globalRenderData.ProjMatrix = m_camera.getClippingMatrix();

    // Setup Global Visuals
    m_globalRenderData.BackgroundColor = this->getBackgroundColor();

    return m_globalRenderData;
}

Camera2D &Scene2D::getCamera()
{
    return m_camera;
}