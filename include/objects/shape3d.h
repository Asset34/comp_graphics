#ifndef SHAPE_H_
#define SHAPE_H_

#include <vector>
#include <list>

#include "geometry.h"
#include "interfaces/renderable.h"
#include "abstract/transformableobj3d.h"

class Shape3D : public TransformableObj3D, public Renderable {
public:
    Shape3D();
    ~Shape3D();

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

    void setEdgeWidth(float width);
    void setVertexSize(float size);

    RenderData getRenderData() override;
    glm::mat4 getTransformation() override;

protected:
    const vec3 &selfOrigin() const override;
    void transformationCallback() override;

private:
    // Default values
    static const vec3 COLOR_DEFAULT; // BLACK

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

    // Misc Visuals
    float m_edgeWidth;
    float m_vertexSize;

};

#endif // SHAPE_H_