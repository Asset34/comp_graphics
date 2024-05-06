#ifndef AXISXYZ_H_
#define AXISXYZ_H_

#include "abstract/transformableobj.h"
#include "interfaces/renderable.h"
#include <vector>

using glm::vec3;

class AxisXYZ : public TransformableObj,  public Renderable {
public:
    AxisXYZ();
    virtual ~AxisXYZ();

    void setSize(float size);
    void setWidth(float width);

    void setColorX(const vec3 &color);
    void setColorY(const vec3 &color);
    void setColorZ(const vec3 &color);

    RenderData getRenderData() override;
    glm::mat4 getTransformation() override;

private:
    vec3 m_center;
    vec3 m_axisx, m_axisy, m_axisz;
    
    // Colors
    static const vec3 COLOR_X;
    static const vec3 COLOR_Y;
    static const vec3 COLOR_Z;

    // Visuals
    vec3 m_colorx;
    vec3 m_colory;
    vec3 m_colorz;
    float m_width;

};


#endif // AXISXYZ_H_