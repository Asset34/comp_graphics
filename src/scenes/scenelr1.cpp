#include "scenes/scenelr1.h"

SceneLR1::SceneLR1()
{
    // Setup Shape

    m_shape.setVertexData({
        { -10,  10,  10 },
        { -10, -10,  10 },
        {  10, -10,  10 },
        {  10,  10,  10 },
        { -10,  10, -10 },
        { -10, -10, -10 },
        {  10, -10, -10 },
        {  10,  10, -10 }
    });

    m_shape.defineVertex(0, {1.0, 0.0, 0.0});
    m_shape.defineVertex(1, {1.0, 0.0, 0.0});
    m_shape.defineVertex(2, {1.0, 0.0, 0.0});
    m_shape.defineVertex(3, {1.0, 0.0, 0.0});
    m_shape.defineVertex(4, {0.0, 0.0, 1.0});
    m_shape.defineVertex(5, {0.0, 0.0, 1.0});
    m_shape.defineVertex(6, {0.0, 0.0, 1.0});
    m_shape.defineVertex(7, {0.0, 0.0, 1.0});

    m_shape.definePolygon({0, 1, 2, 3}, {1.0, 0.0, 0.0});
    m_shape.definePolygon({4, 5, 6, 7}, {0.0, 1.0, 0.0});
    m_shape.definePolygon({0, 4, 7, 3}, {0.0, 0.0, 1.0});
    m_shape.definePolygon({1, 5, 6, 2}, {1.0, 0.0, 1.0});
    m_shape.definePolygon({3, 7, 6, 2}, {1.0, 1.0, 0.0});
    m_shape.definePolygon({0, 4, 5, 1}, {0.0, 1.0, 1.0});

    m_shape.defineEdge(0, 1, {1.0, 1.0, 1.0});
    m_shape.defineEdge(1, 2, {1.0, 1.0, 1.0});
    m_shape.defineEdge(2, 3, {1.0, 1.0, 1.0});
    m_shape.defineEdge(3, 0, {1.0, 1.0, 1.0});
    m_shape.defineEdge(4, 5, {1.0, 1.0, 1.0});
    m_shape.defineEdge(5, 6, {1.0, 1.0, 1.0});
    m_shape.defineEdge(6, 7, {1.0, 0.0, 0.0});
    m_shape.defineEdge(7, 4, {1.0, 0.0, 0.0});
    m_shape.defineEdge(0, 4, {1.0, 0.0, 0.0});
    m_shape.defineEdge(1, 5, {1.0, 0.0, 0.0});
    m_shape.defineEdge(2, 6, {1.0, 0.0, 0.0});
    m_shape.defineEdge(3, 7, {1.0, 0.0, 0.0});

    // m_shape.setRenderVerticesFlag(true);
    m_shape.setRenderEdgesFlag(true);
    m_shape.setRenderPolygonsFlag(true);

    m_shape.setUseModelMatrFlag(true);
    m_shape.setUseViewMatrFlag(true);
    m_shape.setUseProjMatrFlag(true);
    
    m_shape.setGlobalPolygonColor({0.0, 0.0, 1.0});
    m_shape.setUseGlobalPolygonColor(true);

    m_shape.setGlobalEdgeColor({0.0, 0.0, 0.25});
    m_shape.setUseGlobalEdgeColor(true);

    m_shape.setGlobalVertexColor({1.0, 0.0, 0.0});
    m_shape.setUseGlobalVertexColor(true);

    m_shape.setEdgeWidth(3);
    // m_shape.setVertexSize(7);

    m_shape.trackAngle(true);
    
    m_shape.translate({-10, 20, 0});

    // Setup Line
    m_line.setBegin({-50, -25, 20});
    m_line.setEnd({50, 25, -20});
    m_line.setColor({1, 0, 0});
    m_line.setEndsColor({1, 1, 0});
    m_line.setWidth(4);
    m_line.setEndsSize(10);

    // Setup Axis XYZ
    m_axisXYZ.setSize(50);
    m_axisXYZ.setWidth(3);

    // Setup camera
    Camera3D &camera = this->getCamera();
    camera.setPerspectiveProjection();
    camera.setVolume(90, 1.0, 0.01, 1000);
    camera.translate({0, 0, 100});
    camera.setZoomLimits(0.3, 50);
    camera.setZoomLimitsFlag(true);
    camera.setHome();

    // Setup Renderables
    this->addRenderable(&m_shape);
    this->addRenderable(&m_line);
    this->addRenderable(&m_axisXYZ);
    
    // Setup scene background color
    this->setBackgroundColor({0.5, 0.5, 0.5});

    // Init control values
    m_shapePos = m_shape.getOrigin();
    m_lineBeginPos = m_line.getBegin();
    m_lineEndPos = m_line.getEnd();
    m_rotationAngle = 0;
    m_updated = false;
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

void SceneLR1::set(int vid, float value)
{
    switch (vid)
    {
    case VID_ROTATION_ANGLE:
        m_rotationAngle = value;    
    break;
    }
}

void SceneLR1::set(int vid, const float values[])
{
    switch (vid)
    {
    case VID_SHAPE_POS:
        m_shapePos.x = values[0];
        m_shapePos.y = values[1];
        m_shapePos.z = values[2];
    break;
    case VID_LINE_BEGIN_POS:
        m_lineBeginPos.x = values[0];
        m_lineBeginPos.y = values[1];
        m_lineBeginPos.z = values[2];
    break;
    case VID_LINE_END_POS:
        m_lineEndPos.x = values[0];
        m_lineEndPos.y = values[1];
        m_lineEndPos.z = values[2];
    break;
    }
}

void SceneLR1::get(int vid, float &receiver)
{
    switch (vid)
    {
    case VID_ROTATION_ANGLE:
        receiver = m_shape.getAngle();
    break;
    }
}

void SceneLR1::get(int vid, float receiver[])
{
    switch (vid)
    {
    case VID_SHAPE_POS:
        receiver[0] = m_shape.getOrigin().x;
        receiver[1] = m_shape.getOrigin().y;
        receiver[2] = m_shape.getOrigin().z;
    break;
    case VID_LINE_BEGIN_POS:
        receiver[0] = m_line.getBegin().x;
        receiver[1] = m_line.getBegin().y;
        receiver[2] = m_line.getBegin().z;
    break;
    case VID_LINE_END_POS:
        receiver[0] = m_line.getEnd().x;
        receiver[1] = m_line.getEnd().y;
        receiver[2] = m_line.getEnd().z;
    break;
    }
}

void SceneLR1::control(int cmd)
{
    switch (cmd)
    {
    case CMD_SHAPE_SET:
        m_shape.translateItselfTo(m_shapePos);
        m_shape.resetAngle();

        m_updated = true;
        m_updateList.push_back(VID_ROTATION_ANGLE);
    break;
    case CMD_LINE_BEGIN_SET:
        m_line.setBegin(m_lineBeginPos);
        m_shape.resetAngle();

        m_updated = true;
        m_updateList.push_back(VID_ROTATION_ANGLE);
    break;
    case CMD_LINE_END_SET:
        m_line.setEnd(m_lineEndPos);
        m_shape.resetAngle();

        m_updated = true;
        m_updateList.push_back(VID_ROTATION_ANGLE);
    break;
    case CMD_ROTATE:
        m_shape.rotateAroundTo(m_rotationAngle, m_line.getBegin(), m_line.getUnit());

        m_updated = true;
        m_updateList.push_back(VID_SHAPE_POS);
    break;
    }
}

bool SceneLR1::updated()
{
    return m_updated;
}

void SceneLR1::updateAck()
{
    m_updated = false;
    m_updateList.clear();
}

std::list<int> SceneLR1::getUpdateList()
{
    return m_updateList;
}
