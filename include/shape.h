#ifndef SHAPE_H_
#define SHAPE_H_

#include <vector>
#include <list>
#include "sceneobj.h"

class Shape : public SceneObj {
public:
    Shape(int size);

    int getSize() const;
    const std::vector<vec3> &getVertices() const;
    int getPolygonsNumber() const;
    int getPolygonSize() const;
    int getPolygonsOverallSize() const;
    const std::vector<int> &getPolygonIndices() const;
    const vec3 &getPolygonColor() const;

    void polygonBegin();
    void polygonNext();
    bool polygonEnd() const;

    void setVertex(int i, const vec3 &vertex);
    void definePolygon(const std::vector<int> &indices, const vec3 &color);

private:

    struct Polygon {
        std::vector<int> indices;
        vec3 color;
    };

    int m_polygonsOverallSize;

    std::vector<vec3> m_vertices;
    std::list<Polygon> m_polygons;
    std::list<Polygon>::iterator m_polygonsIterator;

};

#endif // SHAPE_H_