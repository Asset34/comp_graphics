#include "scenes/scenelr2.h"

SceneLR2::SceneLR2()
{
    // Build objects
    m_spline.beginEdit();
    this->buildSpline();

    // Init objects
    // m_spline.defineKnots({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    m_spline.defineKnots({0, 0, 0, 1, 2, 2, 2});
    m_spline.setOrder(3);
    m_spline.setRenderStep(0.1);
    m_spline.endEdit();

    // Add renderable objects
    this->addRenderable(&m_splinePolygon);
    this->addRenderable(&m_spline);

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
    vector.push_back(this->getNextRenderableUpdateVectorIndex() + 1); // Update spline

    return vector;
}

void SceneLR2::set(int vid, int value)
{
    switch (vid)
    {
    case VID_CONTROL_POINT_INDEX:
        m_controlPointIndex = value;
    break;
    case VID_KNOT_INDEX:
        m_knotIndex = value;
    break;
    case VID_ORDER_VALUE:
        m_order = value;
    break;
    }  
}

void SceneLR2::set(int vid, float value)
{
    switch (vid)
    {
    case VID_KNOT_VALUE:
        m_knot = value;
    break;
    case VID_RENDER_STEP:
        m_renderStep = value;
    break;
    case VID_KNOT_STEP:
        m_knotStep = value;
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
        receiver = m_spline.getKnotsNumber();
    break;
    case VID_ORDER_MAX:
        receiver = m_spline.getOrderMax();
    break;
    case VID_ORDER_VALUE:
        receiver = m_spline.getOrder();
    break;
    }
}

void SceneLR2::get(int vid, float &receiver)
{
    switch (vid)
    {
    case VID_RENDER_STEP:
        receiver = m_spline.getRenderStep();
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
    case VID_KNOTS:
        for (int i = 0; i < m_spline.getKnotsNumber(); i++) {
            receiver[i] = m_spline.getKnot(i);
        }
    break;
    }
}

void SceneLR2::control(int cmd) 
{
    switch (cmd)
    {
    case CMD_CONTROL_POINT_SET:
        m_splinePolygon.setControlPoint(m_controlPointIndex, m_controlPoint);
        m_spline.setControlPoint(m_controlPointIndex, m_controlPoint);
    break;
    case CMD_KNOT_SET:
        m_spline.setKnot(m_knotIndex, m_knot);
    break;
    case CMD_ORDER_SET:
        m_spline.setOrder(m_order);

        m_updated = true;
        m_updateList.push_back(VID_KNOTS);
    break;
    case CMD_STEP_SET:
        m_spline.setRenderStep(m_renderStep);
    break;
    case CMD_SHOW_CONTROL_POINTS_SWITCH:
        m_splinePolygon.showControlPoints(m_showControlPoints);
    break;
    case CMD_SOW_CONTROL_POLYGON_SWITCH:
        m_splinePolygon.showPolygon(m_showControlPolygon);
    break;
    case CMD_KNOTS_UNIFORM:
        m_spline.defineKnotsUniform(m_knotStep);

        m_updated = true;
        m_updateList.push_back(VID_KNOTS);
    break;
    case CMD_KNOTS_OPENUNIFORM:
        m_spline.defineKnotsOpenUniform(m_knotStep);

        m_updated = true;
        m_updateList.push_back(VID_KNOTS);
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

void SceneLR2::buildSpline()
{
    // Define control points
    // std::vector<vec2> controlPoints = {
    //     {1, 1},
    //     {5, 3},
    //     {10, -3},
    //     {13, 10},
    //     {15, 20},
    //     {20, 31},
    //     {25, -5}
    // };
    std::vector<vec2> controlPoints = {
        {0, 0},
        {3, 9},
        {6, 3},
        {9, 6}
    };

    // Add control points
    for (auto cp : controlPoints) {
        m_splinePolygon.addControlPoint(cp);
        m_spline.addControlPoint(cp);
    }

    // Define visuals
    m_splinePolygon.setPolygonColor({1.0, 0.0, 0.0});
    m_splinePolygon.setControlPointsColor({1.0, 0.0, 0.0});
    m_splinePolygon.setPolygonLineWidth(1.0);
    m_splinePolygon.setControlPointSize(6);
    m_spline.setColor({0.0, 0.0, 1.0});
    m_spline.setLineWidth(4.0);

    this->setBackgroundColor({1.0, 1.0, 1.0});
}
