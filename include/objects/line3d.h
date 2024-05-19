#ifndef LINE_H_
#define LINE_H_

#include "abstract/renderableobj.h"
#include "abstract/transformableobj3d.h"

class Line3D : public TransformableObj3D, public RenderableObj {
public:
    Line3D(const vec3 &b = {0, 0, 0}, const vec3 &e = {0, 0, 0});
    ~Line3D() {};

    void setBegin(const vec3 &p);
    void setEnd(const vec3 &p);

    const vec3 &getBegin() const;
    const vec3 &getEnd() const;
    vec3 getUnit() const;

    void setColor(const Color &color);
    void setEndsColor(const Color &color);
    void setWidth(float width);
    void setEndsSize(float size);

    const RenderData &getRenderData() override;

protected:
    void transformationCallback() override;
    const vec3 &selfOrigin() const override;

private:
    void updateCenter();
    void initRenderData();

    // Default values
    static const Color COLOR_DEFAULT; // BLACK

    vec3 m_begin, m_end;
    vec3 m_center;

    // Colors
    Color m_color     = COLOR_DEFAULT;
    Color m_endsColor = COLOR_DEFAULT;

    // Misc Visuals
    float m_width    = 1.0;
    float m_endsSize = 1.0;

    RenderData m_renderData;

};

#endif // LINE_H_