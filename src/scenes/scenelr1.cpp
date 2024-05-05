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

    m_shape.setEdgeColor({0, 1, 0});
    // m_shape.setRenderPolygonsFlag(true);
    m_shape.setRenderEdgesFlag(true);
    m_shape.setUseModelMatrFlag(true);
    m_shape.setUseViewMatrFlag(true);
    m_shape.setUseProjMatrFlag(true);
    
    // Setup Line
    m_line.setBegin({0, 0, 0});
    m_line.setEnd({1, 0, 0});
    m_line.setColor({1, 0, 0});

    // Setup camera
    Camera3D &camera = this->getCamera();
    camera.setPerspectiveProjection();
    camera.setVolume(90, 1.0, 0.01, 1000);
    camera.translate({0, 0, 100});
    camera.setZoomLimits(0.3, 5);
    camera.setZoomLimitsFlag(true);

    // Setup Renderables
    this->addRenderable(&m_shape);
    this->addRenderable(&m_line);
    
    // Setup scene background color
    this->setBackgroundColor({0.2, 0.2, 0.2});

    m_shapeMove = {0, 0, 0};
    m_lineBegin = {30, -30, 20};
    m_lineEnd = {30, 30, -20};
    m_angle = 0;
    m_rotationAngle = 0;

    // m_changed = true;
    m_lineFlag = false;
}

SceneLR1::~SceneLR1()
{
}

void SceneLR1::update()
{
}

std::vector<int> SceneLR1::getRenderableUpdateVector()
{
    return {1}; // Update only line data
}

void SceneLR1::control(int cmd)
{
}

bool SceneLR1::updated()
{
    return false;
}

void SceneLR1::updateAck()
{
}

std::list<int> SceneLR1::getUpdateList()
{
    return std::list<int>();
}
