#include "objects/plane.h"

const Color Plane::DEFAULT_COLOR = {0.0, 0.0, 0.0};

Plane::Plane(const vec3 &point, const vec3 &normal)
{
    this->initRenderData();
    this->translateTo(point);
    this->update(normal);
}

void Plane::setNormal(const vec3 &normal)
{
    this->update(normal);
    this->setUpdated();
}

const vec3 &Plane::getNormal() const
{
    return this->getUnitz();
}

void Plane::setColor(const Color &color)
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

    this->setUpdated();
}

const RenderData &Plane::getRenderData()
{
    // Setup Transformation Matrix
    m_renderData.ModelMatrix = this->getModelMatrix();

    // Setup Data
    m_renderData.VertexData = m_gridVertexData;
    m_renderData.Edges = m_gridEdges;

    // Setup Visuals
    m_renderData.EdgeWidth = m_gridThickness;
    m_renderData.GlobalEdgeColor = m_color;

    return m_renderData;
}

void Plane::update(const vec3 &normal)
{
    this->coincideWithZ(this->getUnity());
    this->coincideWithZReverse(normal);
}

void Plane::initRenderData()
{
    // Setup Flags
    m_renderData.DrawEdges          = true;
    m_renderData.UseModelMatr       = true;
    m_renderData.UseViewMatr        = true;
    m_renderData.UseProjMatr        = true;
    m_renderData.UseGlobalEdgeColor = true;
}