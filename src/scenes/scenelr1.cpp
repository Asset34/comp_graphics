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
    
    // Setup camera
    Camera &camera = this->getCamera();
    camera.setPerspectiveProjection();
    camera.setVolume(90, 1.0, 0.01, 1000);
    camera.translate({0, 0, 100});
    camera.setZoomLimits(0.3, 5);
    camera.setZoomLimitsFlag(true);

    // Setup Renderables
    this->addRenderable(&m_shape);
    
    // Setup scene background color
    this->setBackgroundColor({0.2, 0.2, 0.2});

    m_shapeX = 0;
    m_shapeY = 0;
    m_shapeZ = 0;
    m_shapeAnglex = 0;
    m_shapeAngley = 0;
    m_shapeAnglez = 0;
    m_shapeRotatex = 0;
    m_shapeRotatey = 0;
    m_shapeRotatez = 0;

    m_shape.translateTo({-40, 20, 0});

    m_changed = true;
}

SceneLR1::~SceneLR1()
{
}

void SceneLR1::update()
{
    m_changed = true;
}

void SceneLR1::control(int controlId)
{
    switch (controlId)
    {
    // Move Shape
    case 0:
        m_shape.translate({m_shapeMovex, m_shapeMovey, m_shapeMovez});
    break;
    case 1:
        m_shape.rotatex(m_shapeRotatex);
        m_shape.rotatey(m_shapeRotatey);
        m_shape.rotatez(m_shapeRotatez);
    break;
    }

    m_shapeMovex = 0;
    m_shapeMovey = 0;
    m_shapeMovez = 0;
    m_shapeRotatex = 0;
    m_shapeRotatey = 0;
    m_shapeRotatez = 0;
    
    m_changed = true;
}

void SceneLR1::receiveValue(int valueId, float sendValue)
{
    switch (valueId)
    {
    case 0:
        m_shapeMovex = sendValue;
    break;
    case 1:
        m_shapeMovey = sendValue;
    break;
    case 2:
        m_shapeMovez = sendValue;
    break;
    case 3:
        m_shapeAnglex += sendValue;
        m_shapeRotatex = sendValue;
    break;
    case 4:
        m_shapeAngley += sendValue;
        m_shapeRotatey = sendValue;
    break;
    case 5:
        m_shapeAnglez += sendValue;
        m_shapeRotatez = sendValue;
    break;
    }
}

void SceneLR1::sendValue(int valueId, float &receiver)
{
    switch (valueId)
    {
    case 0:
        receiver = m_shape.getOrigin().x;
    break;
    case 1:
        receiver = m_shape.getOrigin().y;
    break;
    case 2:
        receiver = m_shape.getOrigin().z;
    break;
    case 3:
        receiver = m_shapeAnglex;
    break;
    case 4:
        receiver = m_shapeAngley;
    break;
    case 5:
        receiver = m_shapeAnglez;
    break;
    }
}

bool SceneLR1::changed()
{
    return m_changed;
}

void SceneLR1::changeAck()
{
    m_changed = false;
}