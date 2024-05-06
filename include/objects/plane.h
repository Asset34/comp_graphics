#ifndef PLANE_H_
#define PLANE_H_

#include "abstract/transformableobj.h"
#include "interfaces/renderable.h"
#include <vector>

class Plane : public TransformableObj, public Renderable {
public:
    Plane(const vec3 &point = {0, 0, 0}, const vec3 &normal = {0, 0, 1});
    virtual ~Plane();

    void setNormal(const vec3 &normal);
    const vec3 &getNormal() const;

    void setColor(const vec3 &color);
    void setGridThickness(float thickness);

    void defineGrid(float cellSize, int quadrantCellWidthNumber, int quadrantCellHeightNumber);

    RenderData getRenderData() override;
    glm::mat4 getTransformation() override;

private:
    void update(const vec3 &normal);

    static const vec3 DEFAULT_COLOR; // BLACK

    struct Edge {
        int begin;
        int end;
    };

    // Data
    std::vector<vec3> m_gridVertexData;
    std::vector<Edge> m_gridEdges;

    // Visuals
    vec3 m_color;
    float m_gridThickness;

};

#endif // PLANE_H_