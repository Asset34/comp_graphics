#ifndef SHAPE_H_
#define SHAPE_H_

#include <vector>
#include "sceneobj.h"

class Shape : public SceneObj {
public:
    Shape(int size, int polygonsNumber);
    ~Shape();

    int getSize() const;
    const vec3 &getVertex(int i) const;
    int getPolygonsNumber() const;
    int getPolygonSize(int i) const;
    int getPolygonsOverallSize() const;
    const std::vector<int> &getPolygonIndices(int i) const;
    const vec3 &getPolygonColor(int i) const;
 
    void setVertex(int i, const vec3 &vertex);
    void definePolygon(int i, const std::vector<int> &indices, const vec3 &color);

private:
    struct Polygon {
        std::vector<int> indices;
        vec3 color;
    };

    int m_polygonsOverallSize;

    std::vector<vec3> m_vertices;
    std::vector<Polygon> m_polygons;

};

#endif // SHAPE_H_