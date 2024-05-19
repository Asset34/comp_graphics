#include "scenes/scenelr1.h"

SceneLR1::SceneLR1()
{
    // Build objects
    this->buildShape();
    this->buildLine();

    // Init objects
    m_shape.translate({-20, 30, 0});
    m_shape.trackAngle(true);

    // Add scene objects
    this->addObject(&m_shape);
    this->addObject(&m_line);

    // Init control values
    m_shapePos = m_shape.getOrigin();
    m_lineBeginPos = m_line.getBegin();
    m_lineEndPos = m_line.getEnd();
    m_rotationAngle = 0;
    m_updated = false;
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

const std::list<int> &SceneLR1::getUpdateList()
{
    return m_updateList;
}

void SceneLR1::buildShape()
{
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

    // Define vertices
    m_shape.defineVertex(0, {1.0, 0.0, 0.0});
    m_shape.defineVertex(1, {1.0, 0.0, 0.0});
    m_shape.defineVertex(2, {1.0, 0.0, 0.0});
    m_shape.defineVertex(3, {1.0, 0.0, 0.0});
    m_shape.defineVertex(4, {0.0, 0.0, 1.0});
    m_shape.defineVertex(5, {0.0, 0.0, 1.0});
    m_shape.defineVertex(6, {0.0, 0.0, 1.0});
    m_shape.defineVertex(7, {0.0, 0.0, 1.0});

    // Define polygons
    m_shape.definePolygon({0, 1, 2, 3}, {1.0, 0.0, 0.0});
    m_shape.definePolygon({4, 5, 6, 7}, {0.0, 1.0, 0.0});
    m_shape.definePolygon({0, 4, 7, 3}, {0.0, 0.0, 1.0});
    m_shape.definePolygon({1, 5, 6, 2}, {1.0, 0.0, 1.0});
    m_shape.definePolygon({3, 7, 6, 2}, {1.0, 1.0, 0.0});
    m_shape.definePolygon({0, 4, 5, 1}, {0.0, 1.0, 1.0});

    // Define edges
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

    // Set Flags
    m_shape.setRenderEdgesFlag(true);
    m_shape.setRenderPolygonsFlag(true);
    m_shape.setUseModelMatrFlag(true);
    m_shape.setUseViewMatrFlag(true);
    m_shape.setUseProjMatrFlag(true);
    m_shape.setUseGlobalPolygonColor(true);
    m_shape.setUseGlobalEdgeColor(true);
    m_shape.setUseGlobalVertexColor(true);
    
    // Setu Visuals
    m_shape.setGlobalPolygonColor({0.1, 0.2, 0.6});
    m_shape.setGlobalEdgeColor({0.05, 0.1, 0.3});
    m_shape.setEdgeWidth(4);
}

void SceneLR1::buildLine()
{
    // Set Data
    m_line.setBegin({-40, 50, -70});
    m_line.setEnd({50, 25, -20});

    // Set Visuals
    m_line.setColor({0.75, 0, 0});
    m_line.setEndsColor({1, 1, 1});
    m_line.setWidth(3);
    m_line.setEndsSize(5);
}
