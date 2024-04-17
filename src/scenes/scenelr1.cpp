#include "scenes/scenelr1.h"

#include <iostream>

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
    Camera &camera = this->getCamera();
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
    m_lineBegin = {0, 0, 0};
    m_lineEnd = {1, 0, 0};
    m_angle = 0;
    m_rotationAngle = 0;

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
        m_shape.translate(m_shapeMove);
        m_shapeMove = {0, 0, 0};
    break;
    // Set Line Points
    case 1:
        m_line.setBegin(m_lineBegin);
        m_line.setEnd(m_lineEnd);
    break;
    // Rotation Around Line
    case 2:
        vec3 unit = m_line.getUnit();
        vec3 point = m_line.getBegin();

        m_shape.rotateAround(m_rotationAngle, point, unit);
        m_rotationAngle = 0;
        // m_angle += m_rotationAngle;
    break;
    }

    // m_angle += m_rotationAngle;
    m_changed = true;
}

void SceneLR1::receiveValue(int valueId, float sendValue)
{
    switch (valueId)
    {
    case 0:
        m_shapeMove.x = sendValue;
    break;
    case 1:
        m_shapeMove.y = sendValue;
    break;
    case 2:
        m_shapeMove.z = sendValue;
    break;

    case 6:
        m_lineBegin.x = sendValue;
    break;
    case 7:
        m_lineBegin.y = sendValue;
    break;
    case 8:
        m_lineBegin.z = sendValue;
    break;
    case 9:
        m_lineEnd.x = sendValue;
    break;
    case 10:
        m_lineEnd.y = sendValue;
    break;
    case 11:
        m_lineEnd.z = sendValue;
    break;

    case 12:
        m_rotationAngle = sendValue;
        m_angle += sendValue;
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
        receiver = m_angle;
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

std::vector<int> SceneLR1::getRenderableUpdateVector()
{
    return {1}; // Update only line data
}