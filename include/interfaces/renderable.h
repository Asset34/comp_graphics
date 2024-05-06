#ifndef RENDERABLE_H_
#define RENDERABLE_H_

#include <vector>
#include "glm/glm.hpp"

struct RenderData {
    // Types
    typedef glm::vec3 Color;
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

    // Sizes
    static const int VertexDataSize = 3;
    static const int EdgeIndexSize = 2;
    static const int VertexIndexSize = 1;

    // Flags
    bool DrawVertices          = false;
    bool DrawEdges             = false;
    bool DrawPolygons          = false;
    bool UseModelMatr          = false;
    bool UseViewMatr           = false;
    bool UseProjMatr           = false;
    bool UseGlobalVertexColor  = false;
    bool UseGlobalEdgeColor    = false;
    bool UseGlobalPolygonColor = false;

    // Data
    std::vector<glm::vec3> VertexData;
    std::vector<Vertex> Vertices;
    std::vector<Edge> Edges;
    std::vector<Polygon> Polygons;

    // Global values
    Color GlobalVertexColor;
    Color GlobalEdgeColor;
    Color GlobalPolygonColor;

    // Misc Visuals
    float EdgeWidth = 1.0;
    float VertexSize = 1.0;

};

class Renderable {
public:
    virtual RenderData getRenderData() = 0;
    virtual glm::mat4 getTransformation() = 0;

    virtual ~Renderable() {};

};

#endif // RENDERABLE_H_