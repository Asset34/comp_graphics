#include "scenes/scenelr2.h"

SceneLR2::SceneLR2()
{
    // Init objects
    this->buildSplinePolygon();

    // Add renderable objects
    this->addRenderable(&m_splinePolygon);

    // Init control values
    m_updated = false;
}

void SceneLR2::update()
{
}

std::vector<int> SceneLR2::getRenderableUpdateVector()
{
    std::vector<int> vector = Scene2D::getRenderableUpdateVector();
    vector.push_back(this->getNextRenderableUpdateVectorIndex()); // Update spline polygon

    return vector;
}

void SceneLR2::set(int vid, int value)
{
    switch (vid)
    {
    case VID_CONTROL_POINT_INDEX:
        m_controlPointIndex = value;
    break;
    case VID_DEGREE_VALUE:
        m_degree = value;
    break;
    }  
}

void SceneLR2::set(int vid, float value)
{
    switch (vid)
    {
    case VID_STEP:
        m_step = value;
    break;
    }
}

void SceneLR2::set(int vid, const float values[])
{
    switch (vid)
    {
    case VID_CONTROL_POINT_VALUE:
        m_controlPoint.x = values[0];
        m_controlPoint.y = values[1];
    break;
    }  
}

void SceneLR2::set(int vid, bool value)
{
    switch (vid)
    {
    case VID_CONTROL_POINTS_FLAG:
        m_showControlPoints = value;
    break;
    case VID_CONTROL_POLYGON_FLAG:
        m_showControlPolygon = value;
    break;
    }
}

void SceneLR2::get(int vid, int &receiver)
{
    switch (vid)
    {
    case VID_CONTROL_POINT_SIZE:
        receiver = m_splinePolygon.getSize();
    break;
    case VID_KNOT_SIZE:
        // TODO
        receiver = 5;
    break;
    case VID_DEGREE_MAX:
        // TODO
        receiver = 7;
    break;
    case VID_DEGREE_VALUE:
        // TODO
        receiver = 4;
    break;
    }
}

void SceneLR2::get(int vid, float &receiver)
{
    switch (vid)
    {
    case VID_STEP:
        // TODO
        receiver = 0.1;
    break;
    }
}

void SceneLR2::get(int vid, bool &receiver)
{
    switch (vid)
    {
    case VID_CONTROL_POINTS_FLAG:
        receiver = m_splinePolygon.getControlPointsShowStatus();
    break;
    case VID_CONTROL_POLYGON_FLAG:
        receiver = m_splinePolygon.getPolygonShowStatus();
    break;
    }
}

void SceneLR2::get(int vid, float receiver[])
{
    switch (vid)
    {
    case VID_CONTROL_POINT_VALUE:
        receiver[0] = m_splinePolygon.getControlPoint(m_controlPointIndex).x;
        receiver[1] = m_splinePolygon.getControlPoint(m_controlPointIndex).y;
    break;
    }
}

void SceneLR2::control(int cmd) 
{
    switch (cmd)
    {
    case CMD_CONTROL_POINT_SET:
        m_splinePolygon.setControlPoint(m_controlPointIndex, m_controlPoint);
    break;
    case CMD_KNOT_SET:
        // TODO
    break;
    case CMD_DEGREE_SET:
        // TODO
    break;
    case CMD_STEP_SET:
        // TODO
    break;
    case CMD_SHOW_CONTROL_POINTS_SWITCH:
        // TODO
        m_splinePolygon.showControlPoints(m_showControlPoints);
    break;
    case CMD_SOW_CONTROL_POLYGON_SWITCH:
        // TODO
        m_splinePolygon.showPolygon(m_showControlPolygon);
    break;
    }
}

bool SceneLR2::updated()
{
    return m_updated;
}

void SceneLR2::updateAck()
{
    m_updated = false;
    m_updateList.clear();
}

std::list<int> SceneLR2::getUpdateList()
{
    return m_updateList;
}

void SceneLR2::buildSplinePolygon()
{
    m_splinePolygon.addControlPoint({1, 1});
    m_splinePolygon.addControlPoint({5, 3});
    m_splinePolygon.addControlPoint({10, -3});
    m_splinePolygon.addControlPoint({13, 10});
    m_splinePolygon.addControlPoint({15, 20});
    m_splinePolygon.addControlPoint({20, 31});
    m_splinePolygon.addControlPoint({25, -5});

    m_splinePolygon.setPolygonColor({1.0, 1.0, 0.0});
    m_splinePolygon.setControlPointsColor({1.0, 0.0, 0.0});
    m_splinePolygon.setPolygonLineWidth(2.0);
    m_splinePolygon.setControlPointSize(10);
}
