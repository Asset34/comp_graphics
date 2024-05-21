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
    float getWKnot(int index) const;
    int getWKnotNumber() const;

    void defineUKnots(const std::vector<float> &knots);
    void defineUKnotsUniform(float step);
    void defineUKnotsOpenUniform(float step);
    void setUKnot(int index, float knot);
    float getUKnot(int index) const;
    int getUKnotNumber() const;

    void setWDegree(int degree);
    int getWDegree() const;
    int getWDegreeMax() const;
    
    void setUDegree(int degree);
    int getUDegree() const;
    int getUDegreeMax() const;

    void setWRenderStep(float step);
    float getWRenderStep() const;

    void setURenderStep(float step);
    float getURenderStep() const;

    void setColor(const Color &color);
    const vec3 &getColor() const;

    void setLineWidth(float width);
    
    const RenderData &getRenderData() override;

private:
    void updateWKnots();
    void updateUKnots();
    
    void initRenderData();


    // Default values
    static const Color COLOR_DEFAULT; // BLACK
    
    // Control data
    std::vector<std::vector<vec3>> m_controlPoints;
    std::vector<float> m_wknots;
    std::vector<float> m_uknots;
    int m_worder = 0;
    int m_uorder = 0;

    // Borders
    int m_leftSegment;
    int m_rightSegment;
    int m_bottomSegment;
    int m_topSegment;

    // Computational values


    bool m_autoCompute = false;
    
    // Render Data
    float m_wrenderStep = 0.1;
    float m_urenderStep = 0.05;
    Color m_color = COLOR_DEFAULT;
    float m_lineWidth = 1.0;
    RenderData m_renderData;

};

#endif // BSURFACE_H_