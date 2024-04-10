#include "shape.h"

Shape::Shape()
    : m_centerValue(0),
      m_center(0),
      m_edgeColor({0, 0, 0})
{
}

Shape::~Shape()
{
}

void Shape::setVertices(const std::vector<vec3> &vertices)
{
    m_vertices = vertices;

    // Compute center value
    int n = vertices.size();
    double sumx, sumy, sumz;
    for (int i = 0; i < n; i++) {
        sumx += vertices[i].x;
        sumy += vertices[i].y;
        sumz += vertices[i].z;
    }
    m_centerValue = vec3(sumx/n, sumy/n, sumz/n);
}

void Shape::defineEdge(int indexBegin, int indexEnd)
{
    Edge e;
    e.indexBegin = indexBegin;
    e.indexEnd = indexEnd;

    m_edges.push_back(e);
}

void Shape::definePolygon(const std::vector<int> &indices, const vec3 &color)
{
    Polygon p;
    p.indices = indices;
    p.color = color;

    m_polygons.push_back(p);
}

RenderData Shape::getRenderData()
{
    RenderData data;

    // Setup Flags
    data.DrawPolygons = true;
    data.UseModelMatr = true;
    data.UseViewMatr = true;
    data.UseProjMatr = true;

    // Setup Data
    data.Vertices = m_vertices;

    data.Edges.reserve(m_edges.size());
    for (auto e : m_edges) {
        data.Edges.push_back({e.indexBegin, e.indexEnd});
    }

    data.Polygons.reserve(m_polygons.size());
    for (auto p : m_polygons) {
        RenderData::Polygon dp;
        dp.Indices = p.indices;
        dp.Color = p.color;

        data.Polygons.push_back(dp);
    }

    // Setup Visuals
    data.EdgeColor = m_edgeColor;

    return data;
}

glm::mat4 Shape::getTransformation()
{
    return this->getModelMatrix();
}

const vec3 &Shape::selfOrigin() const
{
    return m_center;
}

void Shape::transformationCallback()
{
    TransformableObj::transformationCallback();

    // Update center
    m_center = this->getModelMatrix() * vec4(m_centerValue, 1);
}