#ifndef AXISXYZ_H_
#define AXISXYZ_H_

#include "abstract/renderableobj.h"
#include "abstract/transformableobj3d.h"
#include <vector>

using glm::vec3;

class AxisXYZ : public TransformableObj3D,  public RenderableObj {
public:
    AxisXYZ();
    virtual ~AxisXYZ() {};

    void setSize(float size);
    void setWidth(float width);

    void setColorX(const Color &color);
    void setColorY(const Color &color);
    void setColorZ(const Color &color);

    const RenderData &getRenderData() override;

private:
    void initRenderData();

    // Vertices
    vec3 m_center = {0, 0, 0};
    vec3 m_axisx  = {1, 0, 0};
    vec3 m_axisy  = {0, 1, 0};
    vec3 m_axisz  = {0, 0, 1};
    
    // Colors
    static const Color COLOR_X; // Red
    static const Color COLOR_Y; // Green
    static const Color COLOR_Z; // Blue

    // Visuals
    Color m_colorx = COLOR_X;
    Color m_colory = COLOR_Y;
    Color m_colorz = COLOR_Z;
    float m_width = 1.0;

    RenderData m_renderData;

};


#endif // AXISXYZ_H_