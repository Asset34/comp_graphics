#ifndef AXISXY_H_
#define AXISXY_H_

#include "abstract/renderableobj.h"
#include <vector>

class AxisXY : public RenderableObj {
public:
    AxisXY();
    virtual ~AxisXY() {};

    void setSize(float size);
    void setWidth(float width);

    void setColorX(const Color &color);
    void setColorY(const Color &color);

    const RenderData &getRenderData() override;

private:
    void initRenderData();

    // Vertices
    vec2 m_center = {0, 0};
    vec2 m_axisx  = {1, 0};
    vec2 m_axisy  = {0, 1};
    
    // Colors
    static const Color COLOR_X; // Red
    static const Color COLOR_Y; // Green

    // Visuals
    Color m_colorx = COLOR_X;
    Color m_colory = COLOR_Y;
    float m_width = 1.0;

    RenderData m_renderData;

};


#endif // AXISXY_H_