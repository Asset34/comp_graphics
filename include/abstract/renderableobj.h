#ifndef RENDERABLEOBJ_H_
#define RENDERABLEOBJ_H_

#include "glm/glm.hpp"
#include "geometry.h"
#include <vector>

struct RenderData {
    
    // Sizes
    static const int VERTEX_PURE_SIZE = 3; // number of coords per Vertex Data
    static const int EDGE_UNIT_SIZE   = 2; // number of indices per Edge
    static const int VERTEX_UNIT_SIZE = 1; // number of indices per Vertex

    // Flags
    bool DrawVertices          = false; // enable/disable drawing of the Vertices
    bool DrawEdges             = false; // enable/disable drawing of Edges
    bool DrawPolygons          = false; // enable/disable drawing of the Polygons
    bool UseModelMatr          = false; // enable/disable Model matrix usage
    bool UseViewMatr           = false; // enable/disable View matrix usage
    bool UseProjMatr           = false; // enable/disable Projection matrix usage
    bool UseGlobalVertexColor  = false; // enable/disable usage of the uniform color for all Vertices (GlobalVertexColor)
    bool UseGlobalEdgeColor    = false; // enable/disable usage of the uniform color for all Edges (GlobalEdgeColor)
    bool UseGlobalPolygonColor = false; // enable/disable usage of the uniform color for all Polygons (GlobalPolygonColor)

    // Data
    std::vector<glm::vec3> VertexData;
    std::vector<Vertex> Vertices;
    std::vector<Edge> Edges;
    std::vector<Polygon> Polygons;

    // Global uniform values
    Color GlobalVertexColor;
    Color GlobalEdgeColor;
    Color GlobalPolygonColor;

    // Visuals
    float EdgeWidth  = 1.0;
    float VertexSize = 1.0;

    // Transformation matrix
    glm::mat4 ModelMatrix = glm::mat4(1); // default: Identity Matrix

};

class RenderableObj{
public:
    RenderableObj();
    RenderableObj(const RenderableObj &obj);
    virtual ~RenderableObj() {};

    virtual const RenderData &getRenderData() = 0;

    int getId();
    bool updated();
    void updateAck();
    void forceUpdate();

    bool operator==(const RenderableObj &obj);
    bool operator!=(const RenderableObj &obj);
    RenderableObj &operator=(const RenderableObj &obj);


protected:
    void setUpdated();

private:
    void assignId();

    static int NextId;

    int m_id = -1;
    bool m_updated = false;

};

#endif // RENDERABLEOBJ_H_