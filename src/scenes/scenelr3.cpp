#include "scenes/scenelr3.h"

#include <iostream>

SceneLR3::SceneLR3()
{
    // Build objects
    this->buildSurface();

    // Init objects
    m_surface.setWRenderStep(0.1);
    m_surface.setURenderStep(0.04);
    m_surface.setAutocompute(true);
    m_surface.compute();

    m_surfacePolygon.rotateItselfx(-90);
    m_surface.rotateItselfx(-90);

    this->addObject(&m_surfacePolygon);
    this->addObject(&m_surface);

    // Init control values
    m_updated = false;
}

void SceneLR3::update()
{
    // m_surfacePolygon.rotatez(1);
    // m_surface.rotatez(1);
}

void SceneLR3::set(int vid, int value)
{
    switch (vid)
    {
    case VID_SURFACE_HEIGHT:
        m_surfaceHeight = value;
    break;
    case VID_SURFACE_WIDTH:
        m_surfaceWidth = value;
    break;
    case VID_SURFACE_ROW:
        m_surfaceRow = value;
    break;
    case VID_SURFACE_COLUMN:
        m_surfaceColumn = value;
    break;
    case VID_KNOT_INDEX:
        m_knotIndex = value;
    break;
    case VID_HDEGREE_VALUE:
        m_degree = value;
    break;
    case VID_WDEGREE_VALUE:
        m_degree = value;
    break;
    }
}

void SceneLR3::set(int vid, float value)
{
    switch (vid)
    {
    case VID_SURFACE_ROW_VALUE:
        m_surfaceRowValue = value;
    break;
    case VID_SURFACE_COLUMN_VALUE:
        m_surfaceColumnValue = value;
    break;
    case VID_SURFACE_VALUE:
        m_surfaceValue = value;
    break;
    case VID_KNOT_VALUE:
        m_knot = value;
    break;
    case VID_KNOT_STEP:
        m_knotStep = value;
    break;
    case VID_HSTEP:
        m_renderStep = value;
    break;
    case VID_WSTEP:
        m_renderStep = value;
    break;
    }
}

void SceneLR3::set(int vid, bool value)
{
    switch (vid)
    {
    case VID_CONTROL_POINTS_FLAG:
        m_showControlPoints = value;
    break;
    case VID_CONTROL_POLYGON_FLAG:
        m_showControlPolygon = value;
    break;
    case VID_HAUTO_OPEN_UNIFORM_FLAG:
        m_hAutoOpenUniform = value;
    break;
    case VID_WAUTO_OPEN_UNIFORM_FLAG:
        m_wAutoOpenUniform = value;
    break;
    }
}

void SceneLR3::get(int vid, int &receiver)
{
    switch (vid)
    {
    case VID_SURFACE_HEIGHT:
        receiver = m_surfacePolygon.getHeight();
    break;
    case VID_SURFACE_WIDTH:
        receiver = m_surfacePolygon.getWidth();
    break;
    case VID_HKNOT_SIZE:
        receiver = m_surface.getWKnotNumber();
    break;
    case VID_WKNOT_SIZE:
        receiver = m_surface.getUKnotNumber();
    break;
    case VID_HDEGREE_MAX:
        receiver = m_surface.getWDegreeMax();
    break;
    case VID_HDEGREE_VALUE:
        receiver = m_surface.getWDegree();
    break;
    case VID_WDEGREE_MAX:
        receiver = m_surface.getUDegreeMax();
    break;
    case VID_WDEGREE_VALUE:
        receiver = m_surface.getUDegree();
    break;
    }
}

void SceneLR3::get(int vid, float &receiver)
{
    switch (vid)
    {
    case VID_SURFACE_ROW_VALUE:
        receiver = m_surfacePolygon.getRow(m_surfaceRow);
    break;
    case VID_SURFACE_COLUMN_VALUE:
        receiver = m_surfacePolygon.getColumn(m_surfaceColumn);
    break;
    case VID_SURFACE_VALUE:
        receiver = m_surfacePolygon.getControlPointValue(m_surfaceRow, m_surfaceColumn);
    break;
    case VID_HSTEP:
        receiver = m_surface.getWRenderStep();
    break;
    case VID_WSTEP:
        receiver = m_surface.getURenderStep();
    break;
    }
}

void SceneLR3::get(int vid, bool &receiver)
{
    switch (vid)
    {
    case VID_CONTROL_POINTS_FLAG:
        receiver = m_surfacePolygon.getControlPointsShowStatus();
    break;
    case VID_CONTROL_POLYGON_FLAG:
        receiver = m_surfacePolygon.getPolygonShowStatus();
    break;
    case VID_HAUTO_OPEN_UNIFORM_FLAG:
        receiver = m_surface.getAutoWKnotsOpenUniformStatus();
    break;
    case VID_WAUTO_OPEN_UNIFORM_FLAG:
        receiver = m_surface.getAutoUKnotsOpenUniformStatus();
    break;
    }
}

void SceneLR3::get(int vid, float receiver[])
{
    switch (vid)
    {
    case VID_HKNOTS:
        for (int i = 0; i < m_surface.getWKnotNumber(); i++) {
            receiver[i] = m_surface.getWKnot(i);
        }
    break;
    case VID_WKNOTS:
        for (int i = 0; i < m_surface.getUKnotNumber(); i++) {
            receiver[i] = m_surface.getUKnot(i);
        }
    break;
    }
}

void SceneLR3::control(int cmd)
{
    switch(cmd)
    {
    case CMD_SET_SURFACE_HEIGHT:
        m_surfacePolygon.setHeight(m_surfaceHeight);
        m_surface.setControlPoints(m_surfacePolygon);

        m_updated = true;
        m_updateList.push_back(VID_SURFACE_VALUE);
        m_updateList.push_back(VID_SURFACE_ROW_VALUE);
        m_updateList.push_back(VID_HKNOTS);
        m_updateList.push_back(VID_HDEGREE_MAX);
    break;
    case CMD_SET_SURFACE_WIDTH:
        m_surfacePolygon.setWidth(m_surfaceWidth);
        m_surface.setControlPoints(m_surfacePolygon);

        m_updated = true;
        m_updateList.push_back(VID_SURFACE_VALUE);
        m_updateList.push_back(VID_SURFACE_COLUMN_VALUE);
        m_updateList.push_back(VID_WKNOTS);
        m_updateList.push_back(VID_WDEGREE_MAX);
    break;
    case CMD_SET_SURFACE_ROW_VALUE:
        m_surfacePolygon.setRow(m_surfaceRow, m_surfaceRowValue);
        m_surface.setControlPoints(m_surfacePolygon);
    break;
    case CMD_SET_SURFACE_COLUMN_VALUE:
        m_surfacePolygon.setColumn(m_surfaceColumn, m_surfaceColumnValue);
        m_surface.setControlPoints(m_surfacePolygon);
    break;
    case CMD_SET_SURFACE_VALUE:
        m_surfacePolygon.setControlPointValue(m_surfaceRow, m_surfaceColumn, m_surfaceValue);
        m_surface.setControlPoints(m_surfacePolygon);
    break;
    case CMD_HKNOT_SET:
        m_surface.setWKnot(m_knotIndex, m_knot);
    break;
    case CMD_WKNOT_SET:
        m_surface.setUKnot(m_knotIndex, m_knot);
    break;
    case CMD_HKNOTS_UNIFORM:
        m_surface.defineWKnotsUniform(m_knotStep);

        m_updated = true;
        m_updateList.push_back(VID_HKNOTS);
    break;
    case CMD_HKNOTS_OPENUNIFORM:
        m_surface.defineWKnotsOpenUniform(m_knotStep);

        m_updated = true;
        m_updateList.push_back(VID_HKNOTS);
    break;
    case CMD_WKNOTS_UNIFORM:
        m_surface.defineUKnotsUniform(m_knotStep);

        m_updated = true;
        m_updateList.push_back(VID_WKNOTS);
    break;
    case CMD_WKNOTS_OPENUNIFORM:
        m_surface.defineUKnotsOpenUniform(m_knotStep);

        m_updated = true;
        m_updateList.push_back(VID_WKNOTS);
    break;
    case CMD_HDEGREE_SET:
        m_surface.setWDegree(m_degree);

        m_updated = true;
        m_updateList.push_back(VID_HKNOTS);
    break;
    case CMD_WDEGREE_SET:
        m_surface.setUDegree(m_degree);

        m_updated = true;
        m_updateList.push_back(VID_WKNOTS);
    break;
    case CMD_HSTEP_SET:
        m_surface.setWRenderStep(m_renderStep);
    break;
    case CMD_WSTEP_SET:
        m_surface.setURenderStep(m_renderStep);
    break;
    case CMD_SHOW_CONTROL_POINTS_SWITCH:
        m_surfacePolygon.showControlPoints(m_showControlPoints);
    break;
    case CMD_SHOW_CONTROL_POLYGON_SWITCH:
        m_surfacePolygon.showPolygon(m_showControlPolygon);
    break;
    case CMD_HAUTO_OPEN_UNIFORM_SWITCH:
        m_surface.setAutoWKnotsOpenUniform(m_hAutoOpenUniform);
    break;
    case CMD_WAUTO_OPEN_UNIFORM_SWITCH:
        m_surface.setAutoUKnotsOpenUniform(m_wAutoOpenUniform);
    break;
    }
}

bool SceneLR3::updated()
{
    return m_updated;
}

void SceneLR3::updateAck()
{
    m_updated = false;
    m_updateList.clear();
}

const std::list<int> &SceneLR3::getUpdateList()
{
    return m_updateList;
}

void SceneLR3::buildSurface()
{
    // Build polygon

    m_surfacePolygon.setHeight(3);
    m_surfacePolygon.setWidth(4);

    m_surfacePolygon.setColumn(0, 1);
    m_surfacePolygon.setColumn(1, 20);
    m_surfacePolygon.setColumn(2, 40);
    m_surfacePolygon.setColumn(3, 60);

    m_surfacePolygon.setRow(0, 1);
    m_surfacePolygon.setRow(1, 20);
    m_surfacePolygon.setRow(2, 40);

    m_surfacePolygon.setControlPointValue(0, 0, 20);
    m_surfacePolygon.setControlPointValue(1, 0, 30);
    m_surfacePolygon.setControlPointValue(2, 0, 20);

    m_surfacePolygon.setControlPointValue(0, 1, 25);
    m_surfacePolygon.setControlPointValue(1, 1, 40);
    m_surfacePolygon.setControlPointValue(2, 1, 25);

    m_surfacePolygon.setControlPointValue(0, 2, 25);
    m_surfacePolygon.setControlPointValue(1, 2, 40);
    m_surfacePolygon.setControlPointValue(2, 2, 25);

    m_surfacePolygon.setControlPointValue(0, 3, 20);
    m_surfacePolygon.setControlPointValue(1, 3, 30);
    m_surfacePolygon.setControlPointValue(2, 3, 20);

    // Build surface
    m_surface.setControlPoints(m_surfacePolygon);
    m_surface.setWDegree(2);
    m_surface.setUDegree(3);
    m_surface.defineWKnotsOpenUniform(1.0);
    m_surface.defineUKnotsOpenUniform(1.0);
    
    // Define visuals
    m_surfacePolygon.setPolygonColor({1.0, 1.0, 0.0});
    m_surfacePolygon.setControlPointsColor({1.0, 0.0, 0.0});
    m_surfacePolygon.setPolygonLineWidth(2.0);
    m_surfacePolygon.setControlPointSize(5);
    m_surface.setColor({0.0, 1.0, 0.0});
    m_surface.setLineWidth(3.0);

}
