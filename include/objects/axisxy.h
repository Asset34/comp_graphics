#ifndef AXISXY_H_
#define AXISXY_H_

#include "abstract/transformableobj2d.h"
#include "interfaces/renderable.h"
#include <vector>

using glm::vec2;
using glm::vec3;

class AxisXY : public TransformableObj2D,  public Renderable {
public:
    AxisXY();
    virtual ~AxisXY();

    void setSize(float size);
    void setWidth(float width);

    void setColorX(const vec3 &color);
    void setColorY(const vec3 &color);

    RenderData getRenderData() override;
    glm::mat4 getTransformation() override;

private:
    vec2 m_center;
    vec2 m_axisx, m_axisy;
    
    // Colors
    static const vec3 COLOR_X;
    static const vec3 COLOR_Y;

    // Visuals
    vec3 m_colorx;
    vec3 m_colory;
    float m_width;

};


#endif // AXISXY_H_