#include "scenes/scenelr1.h"

SceneLR1::SceneLR1()
{
    // Setup Shape

    m_shape.setVertices({
        { -10,  10,  10 },
        { -10, -10,  10 },
        {  10, -10,  10 },
        {  10,  10,  10 },
        { -10,  10, -10 },
        { -10, -10, -10 },
        {  10, -10, -10 },
        {  10,  10, -10 }
    });
    m_shape.definePolygon({0, 1, 2, 3}, {1.0, 0.0, 0.0});
    m_shape.definePolygon({4, 5, 6, 7}, {0.0, 1.0, 0.0});
    m_shape.definePolygon({0, 4, 7, 3}, {0.0, 0.0, 1.0});
    m_shape.definePolygon({1, 5, 6, 2}, {1.0, 0.0, 1.0});
    m_shape.definePolygon({3, 7, 6, 2}, {1.0, 1.0, 0.0});
    m_shape.definePolygon({0, 4, 5, 1}, {0.0, 1.0, 1.0});
    m_shape.defineEdge(0, 1);
    m_shape.defineEdge(1, 2);
    m_shape.defineEdge(2, 3);
    m_shape.defineEdge(3, 0);
    m_shape.defineEdge(4, 5);
    m_shape.defineEdge(5, 6);
    m_shape.defineEdge(6, 7);
    m_shape.defineEdge(7, 4);
    m_shape.defineEdge(0, 4);
    m_shape.defineEdge(1, 5);
    m_shape.defineEdge(2, 6);
    m_shape.defineEdge(3, 7);

    // m_shape.translate({-40, 20, 0});
    // m_shape.reflect({-30, 10, 0}, {-1, 0.3, 0});

    m_shape.setEdgeColor({0, 1, 0});
    // m_shape.setRenderPolygonsFlag(true);
    m_shape.setRenderEdgesFlag(true);
    m_shape.setUseModelMatrFlag(true);
    m_shape.setUseViewMatrFlag(true);
    m_shape.setUseProjMatrFlag(true);
    
    // Setup camera
    Camera &camera = this->getCamera();
    camera.setVolume(90, 1.0, 0.01, 1000);
    camera.translateTo({0, 0, 100});
    camera.setPerspectiveProjection();

    // Setup Renderables
    this->addRenderable(&m_shape);
    
    // Setup scene background color
    this->setBackgroundColor({0.2, 0.2, 0.2});
}

SceneLR1::~SceneLR1()
{
}

void SceneLR1::update()
{
    // m_shape.rotateAround(1, {0, 0, 0}, {-1, 1, 0});
}
