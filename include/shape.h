#ifndef SHAPE_H_
#define SHAPE_H_

#include <vector>
#include "sceneobj.h"

struct Polygon {
    std::vector<vec3> vertices;
    vec3 color;
};

class Shape : public SceneObj {
    public:
    Shape(int size);

    void setPolygon(int i, const Polygon &polygon);
    const Polygon &getPolygon(int i) const;
    int getPolygonsNumber() const;
    int getVerticesNumber() const;

private:
    std::vector<Polygon> m_polygons;

};

#endif // SHAPE_H_