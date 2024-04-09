#include "shape.h"

Shape::Shape()
    : SceneObj(),
      m_centerValue(0),
      m_center(0)
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

void Shape::definePolygon(const std::vector<int> &indices, const vec3 &color)
{
    Polygon p;
    p.indices = indices;
    p.color = color;

    m_polygons.push_back(p);
}

SceneObjData Shape::compileData() const
{
    SceneObjData data;

    // Setup sizes
    data.VertexSize = 3;
    data.VertexNumber = m_vertices.size();
    data.PolygonNumber = m_polygons.size();

    // Compile vertices data
    std::vector<float> vertices(m_vertices.size() * 3);
    int k = 0;
    for (int i = 0; i < m_vertices.size(); i++) {
        vertices[k] = m_vertices[i].x;
        vertices[k + 1] = m_vertices[i].y;
        vertices[k + 2] = m_vertices[i].z;
        k += 3;
    }
    data.Vertices = vertices;

    // Compile polygon data
    std::vector<int> polygonIndices;
    std::vector<int> polygonSizes;
    std::vector<vec3> polygonColors;
    int indicesSize = 0;
    for (auto p: m_polygons) {
        indicesSize += p.indices.size();
    }

    polygonIndices.resize(indicesSize);
    polygonSizes.resize(m_polygons.size());
    polygonColors.resize(m_polygons.size());
    k = 0;
    for (int i = 0; i < m_polygons.size(); i++) {
        int polygonSize = m_polygons[i].indices.size();

        polygonSizes[i] = polygonSize;
        polygonColors[i] = m_polygons[i].color;

        for (int j = 0; j < polygonSize; j++) {
            polygonIndices[k + j] = m_polygons[i].indices[j];
        }
        k += polygonSize;
    }

    data.PolygonIndices = polygonIndices;
    data.PolygonSizes = polygonSizes;
    data.PolygonColors = polygonColors;

    // Model Matrix
    data.ModelMatrix = this->getModelMatrix();

    return data;
}

const vec3 &Shape::selfOrigin() const
{
    return m_center;
}

void Shape::transformationCallback()
{
    SceneObj::transformationCallback();

    // Update center
    m_center = this->getModelMatrix() * vec4(m_centerValue, 1);
}