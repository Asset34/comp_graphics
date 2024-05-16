#ifndef BSPLINE2D_H_
#define BSPLINE2D_H_

#include "abstract/transformableobj2d.h"
#include "interfaces/renderable.h"
#include <vector>

class BSpline2D : public Renderable {
public:
    BSpline2D();
    ~BSpline2D();

    void beginEdit();
    void endEdit();

    void addControlPoint(const vec2 &cp);
    void setControlPoint(int index, const vec2 &cp);

    void defineKnots(const std::vector<float> &knots);
    int getKnotsNumber() const;
    void setKnot(int index, float knot);
    float getKnot(int index);

    void setOrder(int order);
    int getOrder() const;
    int getOrderMax() const;

    void setRenderStep(float step);
    float getRenderStep() const;

    void setColor(const vec3 &color);
    void setLineWidth(float width);

    RenderData getRenderData() override;
    glm::mat4 getTransformation() override;

private:
    void updateSegmentsBorders();
    void updateKnots();
    void updateAllSegments();
    void updateSegment(int index);
    void computeSegment(int index, int basisBegin, int basisEnd, float t);

    // Default values
    static const vec3 COLOR_DEFAULT; // BLACK

    // Data
    std::vector<vec2> m_contorlPoints;
    std::vector<float> m_knots;
    
    std::vector<std::vector<vec2>> m_segments;

    int m_knotBeginIndex, m_knotEndIndex;
    int m_order;
    float m_renderStep;

    bool m_autoupdate;

    // Visuals
    vec3 m_color;
    float m_lineWidth;

};

#endif // BSPLINE2D_H_