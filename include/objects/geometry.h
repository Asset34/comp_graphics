#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <vector>
#include "glm/glm.hpp"

using glm::vec3;

struct Vertex {
    int index;
    vec3 color;
};

struct Edge {
    int begin;
    int end;
    vec3 color;
};

struct Polygon {
    std::vector<int> indices;
    vec3 color;
};

#endif // GEOMETRY_H_