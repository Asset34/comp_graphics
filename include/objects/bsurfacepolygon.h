#ifndef BSURFACEPOLYGON_H_
#define BSURFACEPOLYGON_H_

#include "geometry.h"
#include "abstract/renderableobj.h"
#include "abstract/transformableobj3d.h"

class BSurfacePolygon : public TransformableObj3D, public RenderableObj {
public:
    BSurfacePolygon();
    ~BSurfacePolygon() {};

    void setHeight(int height);
    void setWidth(int width);
    void setRow(int index, float value);
    void setColumn(int index, float value);
    void setControlPointValue(int row, int column, float value);

    int getHeight() const;
    int getWidth() const;
    float getRow(int index) const;
    float getColumn(int index) const;
    float getControlPointValue(int row, int column) const;

    void setControlPointsColor(const Color &color);
    void setPolygonColor(const Color &color);
    void setPolygonLineWidth(float width);
    void setControlPointSize(float size);

    void showPolygon(bool flag);
    void showControlPoints(bool flag);
    bool getPolygonShowStatus() const;
    bool getControlPointsShowStatus() const;

    std::vector<std::vector<vec3>> getControlPoints() const;

    const RenderData &getRenderData() override;

private:
    void initRenderData();

    std::vector<std::vector<vec3>> m_controlPoints;

    std::vector<float> m_columnValues;
    std::vector<float> m_rowValues;
    std::vector<std::vector<float>> m_controlPointsValues;

    static const Color POLYGON_COLOR;       // Black
    static const Color CONTROL_POINT_COLOR; // Black
    static const float DEFAULT_COLUMN_VALUE; // 0
    static const float DEFAULT_ROW_VALUE; // 0
    static const float DEFAULT_CONTROL_POINT_VALUE; // 0

    // Flags
    bool m_showPolygon       = true;
    bool m_showControlPoints = true;

    // Visuals
    Color m_polygonColor      = POLYGON_COLOR;
    Color m_controlPointColor = CONTROL_POINT_COLOR;
    float m_polygonLineWidth = 1.0;
    float m_controlPointSize = 1.0;

    RenderData m_renderData;

};

#endif // BSURFACEPOLYGON_H_