#ifndef BSPLINEPOLYGON2D_H_
#define BSPLINEPOLYGON2D_H_

#include "geometry.h"
#include "abstract/renderableobj.h"

class BSplinePolygon2D : public RenderableObj {
public:
    BSplinePolygon2D();
    ~BSplinePolygon2D() {};

    void addControlPoint(const vec2 &point);
    void setControlPoint(int index, const vec2 &point);

    void setControlPointsColor(const vec3 &color);
    void setPolygonColor(const vec3 &color);
    void setPolygonLineWidth(float width);
    void setControlPointSize(float size);

    const vec2 &getControlPoint(int index) const;
    int getSize() const;

    void showPolygon(bool flag);
    void showControlPoints(bool flag);

    bool getPolygonShowStatus() const;
    bool getControlPointsShowStatus() const;

    const RenderData &getRenderData() override;

private:
    void initRenderData();

    std::vector<vec2> m_controlPoints;

    // Colors
    static const Color POLYGON_COLOR;       // Black
    static const Color CONTROL_POINT_COLOR; // Black

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

#endif // BSPLINEPOLYGON2D_H_