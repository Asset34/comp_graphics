#ifndef SHAPE_H_
#define SHAPE_H_

#include <vector>
#include <list>

#include "interfaces/renderable.h"
#include "abstract/transformableobj.h"

class Shape : public TransformableObj, public Renderable {
public:
    Shape();
    ~Shape();

    void setVertexData(const std::vector<vec3> &vertexData);
    void defineVertex(int index, const vec3 &color);
    void defineEdge(int indexBegin, int indexEnd, const vec3 &color); 
    void definePolygon(const std::vector<int> &indices, const vec3 &color);

    void setGlobalVertexColor(const vec3 &color);
    void setGlobalEdgeColor(const vec3 &color);
    void setGlobalPolygonColor(const vec3 &color);

    void setRenderVerticesFlag(bool value);
    void setRenderEdgesFlag(bool value);
    void setRenderPolygonsFlag(bool value);
    void setUseModelMatrFlag(bool value);
    void setUseViewMatrFlag(bool value);
    void setUseProjMatrFlag(bool value);
    void setUseGlobalVertexColor(bool value);
    void setUseGlobalEdgeColor(bool value);
    void setUseGlobalPolygonColor(bool value);

    RenderData getRenderData() override;
    glm::mat4 getTransformation() override;

protected:
    const vec3 &selfOrigin() const override;
    void transformationCallback() override;

private:
    // Default vales
    static const vec3 COLOR_DEFAULT; // BLACK

    // Types
    struct Vertex {
        int index;
        vec3 color;
    };
    struct Edge {
        int indexBegin;
        int indexEnd;
        vec3 color;
    };
    struct Polygon {
        std::vector<int> indices;
        vec3 color;
    };

    // Data
    std::vector<vec3> m_vertexData;
    std::vector<Vertex> m_vertices;
    std::vector<Edge> m_edges;
    std::vector<Polygon> m_polygons;

    // Colors
    vec3 m_globalVertexColor;
    vec3 m_globalEdgeColor;
    vec3 m_globalPolygonColor;

    vec3 m_centerValue;
    vec3 m_center;

    // Flags
    bool m_renderVertices;
    bool m_renderEdges;
    bool m_renderPolygons;
    bool m_useModelMatr;
    bool m_useViewMatr;
    bool m_useProjMatr;
    bool m_useGlobalVertexColor;
    bool m_useGlobalEdgeColor;
    bool m_useGlobalPolygonColor;

};

#endif // SHAPE_H_