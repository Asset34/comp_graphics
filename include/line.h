#ifndef LINE_H_
#define LINE_H_

#include "sceneobj.h"

class Line : public SceneObj {
public:
    Line(const vec3 &begin = vec3(0.0f, 0.0f, 0.0f), const vec3 &end = vec3(0.0f, 0.0f, 0.0f));
    ~Line();

    const vec3 &getBegin() const;
    const vec3 &getEnd() const;
    const vec3 &getColor() const;
    
    vec3 getPoint() const;
    vec3 getUnit() const;

    void setBegin(const vec3 &begin);
    void setEnd(const vec3 &end);
    void setColor(const vec3 &color);

private:
    vec3 m_begin, m_end;
    vec3 m_color;

};

#endif // LINE_H_