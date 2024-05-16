#ifndef BSPLINEPOLYGON2D_H_
#define BSPLINEPOLYGON2D_H_

#include "geometry.h"
#include "interfaces/renderable.h"
#include "abstract/transformableobj2d.h"

class BSplinePolygon2D : public TransformableObj2D, public Renderable {
public:
    BSplinePolygon2D();
    ~BSplinePolygon2D();

    void addControlPoint(const vec2 &point);
    void setControlPoint(int index, const vec2 &point);
    void removeControlPoint(int index);
    void moveControlPoint(int index, int destinationIndex);

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

    RenderData getRenderData() override;
    glm::mat4 getTransformation() override;

private:
    std::vector<vec2> m_controlPoints;

    // Colors
    static const vec3 POLYGON_COLOR;
    static const vec3 CONTROL_POINT_COLOR;

    // Flags
    bool m_showPolygon;
    bool m_showControlPoints;

    // Visuals
    vec3 m_polygonColor;
    vec3 m_controlPointColor;
    float m_polygonLineWidth;
    float m_controlPointSize;

};

#endif // BSPLINEPOLYGON2D_H_