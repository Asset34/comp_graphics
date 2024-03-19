#include "shape.h"

Shape::Shape(int size)
    :m_vertices(size),
     m_polygonsOverallSize(0)
{
    this->polygonBegin();
}

int Shape::getSize() const
{
    return m_vertices.size();
}

const std::vector<vec3> &Shape::getVertices() const
{
    return m_vertices;
}

int Shape::getPolygonsNumber() const
{
    return m_polygons.size();
}

int Shape::getPolygonSize() const
{
    return m_polygonsIterator->indices.size();
}

int Shape::getPolygonsOverallSize() const
{
    return m_polygonsOverallSize;
}

const std::vector<int> &Shape::getPolygonIndices() const
{
    return m_polygonsIterator->indices;
}

const vec3 &Shape::getPolygonColor() const
{
    return m_polygonsIterator->color;
}

void Shape::polygonBegin()
{
    m_polygonsIterator = m_polygons.begin();
}

void Shape::polygonNext()
{
    ++m_polygonsIterator;
}

bool Shape::polygonEnd() const
{
    return m_polygonsIterator == m_polygons.end();
}

void Shape::setVertex(int i, const vec3 &vertex)
{
    m_vertices[i] = vertex;
}

void Shape::definePolygon(const std::vector<int> &indices, const vec3 &color)
{
    m_polygonsOverallSize += indices.size();
}
