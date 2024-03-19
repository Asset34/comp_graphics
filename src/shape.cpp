#include "shape.h"


Shape::Shape(int size)
    :m_polygons(size)
{
}

void Shape::setPolygon(int i, const Polygon &polygon)
{
    m_polygons[i] = polygon;
}

const Polygon &Shape::getPolygon(int i) const
{
    return m_polygons[i];
}

int Shape::getPolygonsNumber() const
{
    return m_polygons.size();
}

int Shape::getVerticesNumber() const
{
    int n = 0;

    for (int i = 0; i < m_polygons.size(); i++) {
        n += m_polygons[i].vertices.size();
    }

    return n;
}
