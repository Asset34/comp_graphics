#include "shape.h"

Shape::Shape(int size, int polygonsNumber)
    :m_vertices(size),
     m_polygons(polygonsNumber),
     m_polygonsOverallSize(0)
{
    // this->polygonBegin();
}

Shape::~Shape()
{
}

int Shape::getSize() const
{
    return m_vertices.size();
}

const vec3 &Shape::getVertex(int i) const
{
    return m_vertices[i];
}

int Shape::getPolygonsNumber() const
{
    return m_polygons.size();
}

int Shape::getPolygonSize(int i) const
{
    return m_polygons[i].indices.size();
}

int Shape::getPolygonsOverallSize() const
{
    return m_polygonsOverallSize;
}

const std::vector<int> &Shape::getPolygonIndices(int i) const
{
    return m_polygons[i].indices;
}

const vec3 &Shape::getPolygonColor(int i) const
{
    return m_polygons[i].color;
}

void Shape::setVertex(int i, const vec3 &vertex)
{
    m_vertices[i] = vertex;
}

void Shape::definePolygon(int i, const std::vector<int> &indices, const vec3 &color)
{
    m_polygons[i].indices = indices;
    m_polygons[i].color = color;

    m_polygonsOverallSize += indices.size();
}
