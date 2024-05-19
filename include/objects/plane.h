#ifndef PLANE_H_
#define PLANE_H_

#include "geometry.h"
#include "abstract/transformableobj3d.h"
#include "abstract/renderableobj.h"
#include <vector>

class Plane : public TransformableObj3D, public RenderableObj {
public:
    Plane(const vec3 &point = {0, 0, 0}, const vec3 &normal = {0, 0, 1});
    virtual ~Plane() {};

    void setNormal(const vec3 &normal);
    const vec3 &getNormal() const;

    void setColor(const Color &color);
    void setGridThickness(float thickness);

    void defineGrid(float cellSize, int quadrantCellWidthNumber, int quadrantCellHeightNumber);

    const RenderData &getRenderData() override;

private:
    void update(const vec3 &normal);
    void initRenderData();

    static const Color DEFAULT_COLOR; // BLACK

    // Data
    std::vector<vec3> m_gridVertexData;
    std::vector<Edge> m_gridEdges;

    // Visuals
    Color m_color = DEFAULT_COLOR;
    float m_gridThickness = 1.0;

    RenderData m_renderData;

};

#endif // PLANE_H_