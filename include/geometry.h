#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <vector>
#include "glm/glm.hpp"

// Aliases
typedef glm::vec3 Color;
using glm::vec2;
using glm::vec3;
using glm::mat3;
using glm::mat4;

// Structures
struct Vertex {
    int index;
    Color color;
};

struct Edge {
    int begin;
    int end;
    Color color;
};

struct Polygon {
    std::vector<int> indices;
    Color color;
};

#endif // GEOMETRY_H_