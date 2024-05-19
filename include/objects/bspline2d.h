#ifndef BSPLINE2D_H_
#define BSPLINE2D_H_

#include "abstract/renderableobj.h"
#include <vector>

class BSpline2D : public RenderableObj {
public:
    BSpline2D();
    ~BSpline2D() {};

    void setAutocompute(bool value);
    void compute();

    void addControlPoint(const vec2 &cp);
    void setControlPoint(int index, const vec2 &cp);

    void defineKnots(const std::vector<float> &knots);
    void defineKnotsUniform(float step);
    void defineKnotsOpenUniform(float step);
    int getKnotsNumber() const;
    void setKnot(int index, float knot);
    float getKnot(int index);

    void setDegree(int degree);
    int getDegree() const;
    int getDegreeMax() const;

    void setOrder(int order);
    int getOrder() const;
    int getOrderMax() const;

    void setRenderStep(float step);
    float getRenderStep() const;

    void setColor(const Color &color);
    const vec3 &getColor() const;

    void setLineWidth(float width);

    const RenderData &getRenderData() override;

private:
    void computeBorders();
    void updateKnots();

    bool isSegmentEmpty(int index);

    void updateAllSegments();
    void updateSegmentsAffectedByBasis(int basisIndex);
    void updateSegmentsAffectedByKnot(int knotIndex);

    void updateSegment(int index);
    void computeSegment(int index, int basisBegin, float t);
    void updateLast();

    void initRenderData();

    // Default values
    static const Color COLOR_DEFAULT; // BLACK

    // Control Data
    std::vector<vec2> m_contorlPoints;
    std::vector<float> m_knots;
    int m_order = 0;
    
    // Borders
    int m_beginSegment;
    int m_endSegment;

    // Result Data
    std::vector<std::vector<vec2>> m_segments;

    bool m_autoCompute = false;

    // Render Data
    float m_renderStep = 0.05;
    Color m_color = COLOR_DEFAULT;
    float m_lineWidth = 1.0;
    RenderData m_renderData;

};

#endif // BSPLINE2D_H_