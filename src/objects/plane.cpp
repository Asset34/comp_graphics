#include "objects/plane.h"

const vec3 Plane::DEFAULT_COLOR = {0.0, 0.0, 0.0};

Plane::Plane(const vec3 &point, const vec3 &normal)
    : m_color(DEFAULT_COLOR),
      m_gridThickness(1.0)
{
    this->translateTo(point);
    this->update(normal);
}

Plane::~Plane()
{
}

void Plane::setNormal(const vec3 &normal)
{
    this->update(normal);
}

const vec3 &Plane::getNormal() const
{
    return this->getUnitz();
}

void Plane::setColor(const vec3 &color)
{
    m_color = color;
}

void Plane::setGridThickness(float thickness)
{
    m_gridThickness = thickness;
}

void Plane::defineGrid(float cellSize, int quadrantCellWidthNumber, int quadrantCellHeightNumber)
{
    float quadrantWidth = cellSize * quadrantCellWidthNumber;
    float quadrantHeight = cellSize * quadrantCellHeightNumber;

    // Prepare
    m_gridVertexData.clear();
    int horN = 2 * quadrantCellWidthNumber - 1;
    int verN = 2 * quadrantCellHeightNumber - 1;
    m_gridVertexData.reserve(2 * (horN = verN));
    m_gridEdges.clear();
    m_gridEdges.reserve(horN = verN);
    int i;

    // Horizontal lines
    i = 0;
    for (int x = -quadrantWidth; x <= quadrantWidth; x += cellSize) {
        m_gridVertexData.push_back({x, 0.0, -quadrantHeight});
        m_gridVertexData.push_back({x, 0.0, quadrantHeight});
        m_gridEdges.push_back({i, i + 1});

        i += 2;
    }

    // Vertical lines
    for (int z = -quadrantHeight; z <= quadrantHeight; z += cellSize) {
        m_gridVertexData.push_back({-quadrantWidth, 0.0, z});
        m_gridVertexData.push_back({quadrantWidth, 0.0, z});
        m_gridEdges.push_back({i, i + 1});

        i += 2;
    }
}

RenderData Plane::getRenderData()
{
    RenderData data;

    // Setup Flags
    data.DrawEdges = true;
    data.UseModelMatr = true;
    data.UseViewMatr = true;
    data.UseProjMatr = true;
    data.UseGlobalEdgeColor = true;

    // Setup Data

    data.VertexData = m_gridVertexData;
    data.Edges.reserve(m_gridEdges.size());
    for (auto e : m_gridEdges) {
        data.Edges.push_back({e.begin, e.end});
    }

    // Setup Visuals
    data.EdgeWidth = m_gridThickness;
    data.GlobalEdgeColor = m_color;

    return data;
}

glm::mat4 Plane::getTransformation()
{
    return this->getModelMatrix();
}

void Plane::update(const vec3 &normal)
{
    this->coincideWithZ(this->getUnity());
    this->coincideWithZReverse(normal);
}
