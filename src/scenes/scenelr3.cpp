#include "scenes/scenelr3.h"

SceneLR3::SceneLR3()
{
    // Build objects
    this->buildSurface();

    // Init objects
    m_surfacePolygon.setPolygonColor({0.0, 1.0, 0.0});
    m_surfacePolygon.setControlPointsColor({1.0, 1.0, 0.0});
    m_surfacePolygon.setPolygonLineWidth(2.0);
    m_surfacePolygon.setControlPointSize(5);

    m_surfacePolygon.rotateItselfx(-90);

    this->addObject(&m_surfacePolygon);
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
    }
}

void SceneLR3::control(int cmd)
{
    switch(cmd)
    {
    case CMD_SET_SURFACE_HEIGHT:
        m_surfacePolygon.setHeight(m_surfaceHeight);

        m_updated = true;
        m_updateList.push_back(VID_SURFACE_VALUE);
        m_updateList.push_back(VID_SURFACE_ROW_VALUE);
    break;
    case CMD_SET_SURFACE_WIDTH:
        m_surfacePolygon.setWidth(m_surfaceWidth);

        m_updated = true;
        m_updateList.push_back(VID_SURFACE_VALUE);
        m_updateList.push_back(VID_SURFACE_COLUMN_VALUE);
    break;
    case CMD_SET_SURFACE_ROW_VALUE:
        m_surfacePolygon.setRow(m_surfaceRow, m_surfaceRowValue);
    break;
    case CMD_SET_SURFACE_COLUMN_VALUE:
        m_surfacePolygon.setColumn(m_surfaceColumn, m_surfaceColumnValue);
    break;
    case CMD_SET_SURFACE_VALUE:
        m_surfacePolygon.setControlPointValue(m_surfaceRow, m_surfaceColumn, m_surfaceValue);
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
}
