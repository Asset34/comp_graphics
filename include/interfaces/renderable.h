#ifndef RENDERABLE_H_
#define RENDERABLE_H_

#include <vector>
#include "glm/glm.hpp"

struct RenderData {
    // Types
    typedef glm::vec3 Vertex;
    typedef glm::vec3 Color;
    typedef glm::vec2 Edge;
    struct Polygon {
        std::vector<int> Indices;
        Color color;
    };

    // Sizes
    static const int VertexSize = 3;
    static const int EdgeSize = 2;

    // Flags
    // bool DrawVertices = false;
    bool DrawEdges    = false;
    bool DrawPolygons = false;
    bool UseModelMatr = false;
    bool UseViewMatr  = false;
    bool UseProjMatr  = false;

    // Data
    std::vector<Vertex> Vertices;
    std::vector<Edge>   Edges;
    std::vector<Polygon>Polygons;

    // Visual
    Color EdgeColor;
};

class Renderable {
public:
    virtual RenderData getRenderData() = 0;
    virtual glm::mat4 getTransformation() = 0;

    virtual ~Renderable() {};

};

#endif // RENDERABLE_H_