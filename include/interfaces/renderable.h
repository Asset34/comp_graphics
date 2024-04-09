#ifndef RENDERABLE_H_
#define RENDERABLE_H_

#include <vector>
#include "glm/glm.hpp"

struct RenderData {
    // Types
    typedef glm::vec3 Vertex;
    typedef glm::vec3 Color;
    struct Edge {
        Vertex begin;
        Vertex end;
    };
    struct Polygon {
        std::vector<float> Indices;
        Color Color;
    };

    // Flags
    bool DrawVertices = false;
    bool DrawEdges    = false;
    bool DrawPolygons = false;
    bool UseModelMatr = false;
    bool UseViewMatr  = false;
    bool UseProjMatr  = false;

    // Data
    std::vector<Vertex>  Vertices;
    std::vector<Edge>    Edges;
    std::vector<Polygon> Polygons;

};

class Renderable {
public:
    virtual RenderData getRenderData() = 0;
    virtual glm::mat4 getTransformation() = 0;

    virtual ~Renderable() {};

};

#endif // RENDERABLE_H_