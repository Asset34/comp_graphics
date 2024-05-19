#ifndef SHAPE_H_
#define SHAPE_H_

#include <vector>
#include <list>

#include "geometry.h"
#include "abstract/renderableobj.h"
#include "abstract/transformableobj3d.h"

class Shape3D : public TransformableObj3D, public RenderableObj {
public:
    ~Shape3D() {};

    void setVertexData(const std::vector<vec3> &vertexData);
    void defineVertex(int index, const Color &color);
    void defineEdge(int indexBegin, int indexEnd, const Color &color); 
    void definePolygon(const std::vector<int> &indices, const Color &color);

    void setGlobalVertexColor(const Color &color);
    void setGlobalEdgeColor(const Color &color);
    void setGlobalPolygonColor(const Color &color);

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

    const RenderData &getRenderData() override;

protected:
    const vec3 &selfOrigin() const override;
    void transformationCallback() override;

private:
    // Default values
    static const Color COLOR_DEFAULT; // BLACK

    // Data
    std::vector<vec3> m_vertexData;
    std::vector<Vertex> m_vertices;
    std::vector<Edge> m_edges;
    std::vector<Polygon> m_polygons;

    // Colors
    Color m_globalVertexColor  = COLOR_DEFAULT;
    Color m_globalEdgeColor    = COLOR_DEFAULT;
    Color m_globalPolygonColor = COLOR_DEFAULT;

    vec3 m_centerValue = {0, 0, 0};
    vec3 m_center      = {0, 0, 0};

    // Flags
    bool m_renderVertices        = false;
    bool m_renderEdges           = false;
    bool m_renderPolygons        = true;
    bool m_useModelMatr          = true;
    bool m_useViewMatr           = true;
    bool m_useProjMatr           = true;
    bool m_useGlobalVertexColor  = false;
    bool m_useGlobalEdgeColor    = false;
    bool m_useGlobalPolygonColor = false;

    // Misc Visuals
    float m_edgeWidth  = 1.0;
    float m_vertexSize = 1.0;

    RenderData m_renderData;

};

#endif // SHAPE_H_