#ifndef LINE_H_
#define LINE_H_

#include "interfaces/renderable.h"
#include "abstract/transformableobj.h"

class Line : public TransformableObj, public Renderable {
public:
    Line(const vec3 &b = {0, 0, 0}, const vec3 &e = {0, 0, 0});
    ~Line();

    void setBegin(const vec3 &p);
    void setEnd(const vec3 &p);

    const vec3 &getBegin() const;
    const vec3 &getEnd() const;
    vec3 getUnit() const;

    void setColor(const vec3 &color);
    const vec3 &getColor() const;

    virtual RenderData getRenderData() override;
    virtual glm::mat4 getTransformation() override;

protected:
    void transformationCallback() override;
    const vec3 &selfOrigin() const override;

private:
    void updateCenter();

    vec3 m_begin, m_end;
    vec3 m_center;

    vec3 m_color;

};

#endif // LINE_H_