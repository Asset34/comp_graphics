#ifndef SHAPE_H_
#define SHAPE_H_

#include <vector>
#include <list>
#include "sceneobj.h"

class Shape : public SceneObj {
public:
    Shape();
    ~Shape();

    void setVertices(const std::vector<vec3> &vertices);
    void definePolygon(const std::vector<int> &indices, const vec3 &color);

    virtual SceneObjData compileData() const override;

protected:
    virtual const vec3 &selfOrigin() const override;
    virtual void transformationCallback() override;

private:
    struct Polygon {
        std::vector<int> indices;
        vec3 color;
    };

    vec3 m_centerValue;
    vec3 m_center;

    std::vector<vec3> m_vertices;
    std::vector<Polygon> m_polygons;

};

#endif // SHAPE_H_