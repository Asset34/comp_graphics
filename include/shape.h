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

    void setVertices(const std::vector<vec3> &vertices);
    void defineEdge(int indexBegin, int indexEnd); 
    void definePolygon(const std::vector<int> &indices, const vec3 &color);

    void setEdgeColor(const vec3 &color);

    void setRenderEdgesFlag(bool value);
    void setRenderPolygonsFlag(bool value);
    void setUseModelMatrFlag(bool value);
    void setUseModelViewFlag(bool value);
    void setUseModelProjFlag(bool value);

    RenderData getRenderData() override;
    glm::mat4 getTransformation() override;

protected:
    const vec3 &selfOrigin() const override;
    void transformationCallback() override;

private:
    // Types
    struct Edge {
        int indexBegin;
        int indexEnd;
    };
    struct Polygon {
        std::vector<int> indices;
        vec3 color;
    };

    // Data
    std::vector<vec3> m_vertices;
    std::vector<Edge> m_edges;
    std::vector<Polygon> m_polygons;

    vec3 m_edgeColor;

    vec3 m_centerValue;
    vec3 m_center;

    // Flags
    bool m_renderEdges;
    bool m_renderPolygons;
    bool m_useModelMatr;
    bool m_useViewMatr;
    bool m_useProjMatr;

};

#endif // SHAPE_H_