#ifndef BSURFACE_H_
#define BSURFACE_H_

#include "abstract/renderableobj.h"
#include "abstract/transformableobj3d.h"
#include "objects/bsurfacepolygon.h"

class BSurface : public TransformableObj3D, public RenderableObj {
public:
    BSurface();
    ~BSurface() {};

    void setAutocompute(bool value);
    void compute();

    void setControlPoints(const BSurfacePolygon &polygon);

    void defineWKnots(const std::vector<float> &knots);
    void defineWKnotsUniform(float step);
    void defineWKnotsOpenUniform(float step);
    void setWKnot(int index, float knot);
    void setAutoWKnotsOpenUniform(bool value);
    bool getAutoWKnotsOpenUniformStatus() const;
    float getWKnot(int index) const;
    int getWKnotNumber() const;

    void defineUKnots(const std::vector<float> &knots);
    void defineUKnotsUniform(float step);
    void defineUKnotsOpenUniform(float step);
    void setUKnot(int index, float knot);
    void setAutoUKnotsOpenUniform(bool value);
    bool getAutoUKnotsOpenUniformStatus() const;
    float getUKnot(int index) const;
    int getUKnotNumber() const;

    void setWDegree(int degree);
    int getWDegree() const;
    int getWDegreeMax() const;
    
    void setUDegree(int degree);
    int getUDegree() const;
    int getUDegreeMax() const;

    int getWOrderMax() const;    
    int getUOrderMax() const;    

    void setWRenderStep(float step);
    float getWRenderStep() const;

    void setURenderStep(float step);
    float getURenderStep() const;

    void setColor(const Color &color);
    const vec3 &getColor() const;

    void setLineWidth(float width);
    
    const RenderData &getRenderData() override;

private:
    void computeBorders();
    void updateWKnots();
    void updateUKnots();
    void updateOrders();

    void updateAllSegments();
    void updateSegment(int indexw, int indexu);
    vec3 computeSegment(int indexu, int basisBegin, float u);
    vec3 computeIntermediateControlPoint(int indexw, int basisStart, int pointsIndex, float w);

    void initRenderData();

    struct Segment {
        std::vector<std::vector<vec3>> splines;
    };

    // Default values
    static const Color COLOR_DEFAULT; // BLACK
    
    // Control data
    std::vector<std::vector<vec3>> m_controlPoints;
    std::vector<float> m_wknots;
    std::vector<float> m_uknots;
    int m_worder = 0;
    int m_uorder = 0;

    // Data
    std::vector<std::vector<Segment>> m_segments;

    // Computational values
    std::vector<vec3> m_intermediateControlPoints;

    // Borders
    int m_leftSegment;
    int m_rightSegment;
    int m_bottomSegment;
    int m_topSegment;

    bool m_autoCompute = false;
    bool m_uautoOpenUniform = false;
    bool m_wautoOpenUniform = false;
    
    // Render Data
    float m_wrenderStep = 0.1;
    float m_urenderStep = 0.05;
    Color m_color = COLOR_DEFAULT;
    float m_lineWidth = 1.0;
    RenderData m_renderData;

};

#endif // BSURFACE_H_