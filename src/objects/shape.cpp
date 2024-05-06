#include "objects/shape.h"

const vec3 Shape::COLOR_DEFAULT = {0, 0, 0};

Shape::Shape()
    : m_centerValue(0),
      m_center(0),
      m_globalVertexColor(COLOR_DEFAULT),
      m_globalEdgeColor(COLOR_DEFAULT),
      m_globalPolygonColor(COLOR_DEFAULT),
      m_renderVertices(false),
      m_renderEdges(false),
      m_renderPolygons(true),
      m_useModelMatr(true),
      m_useViewMatr(true),
      m_useProjMatr(true),
      m_useGlobalVertexColor(false),
      m_useGlobalEdgeColor(false),
      m_useGlobalPolygonColor(false),
      m_edgeWidth(1.0),
      m_vertexSize(1.0)
{
}

Shape::~Shape()
{
}

void Shape::setVertexData(const std::vector<vec3> &vertexData)
{
    m_vertexData = vertexData;

    // Compute center value
    int n = vertexData.size();
    double sumx, sumy, sumz;
    for (int i = 0; i < n; i++) {
        sumx += vertexData[i].x;
        sumy += vertexData[i].y;
        sumz += vertexData[i].z;
    }
    m_centerValue = vec3(sumx/n, sumy/n, sumz/n);
}

void Shape::defineVertex(int index, const vec3 &color)
{
    Vertex v;
    v.index = index;
    v.color = color;

    m_vertices.push_back(v);
}

void Shape::defineEdge(int indexBegin, int indexEnd, const vec3 &color)
{
    Edge e;
    e.indexBegin = indexBegin;
    e.indexEnd = indexEnd;
    e.color = color;

    m_edges.push_back(e);
}

void Shape::definePolygon(const std::vector<int> &indices, const vec3 &color)
{
    Polygon p;
    p.indices = indices;
    p.color = color;

    m_polygons.push_back(p);
}

void Shape::setGlobalVertexColor(const vec3 &color)
{
    m_globalVertexColor = color;
}

void Shape::setGlobalEdgeColor(const vec3 &color)
{
    m_globalEdgeColor = color;
}

void Shape::setGlobalPolygonColor(const vec3 &color)
{
    m_globalPolygonColor = color;
}

void Shape::setRenderVerticesFlag(bool value)
{
    m_renderVertices = value;
}

void Shape::setRenderEdgesFlag(bool value)
{
    m_renderEdges = value;
}

void Shape::setRenderPolygonsFlag(bool value)
{
    m_renderPolygons = value;
}

void Shape::setUseModelMatrFlag(bool value)
{
    m_useModelMatr = value;
}

void Shape::setUseViewMatrFlag(bool value)
{
    m_useViewMatr = value;
}

void Shape::setUseProjMatrFlag(bool value)
{
    m_useProjMatr = value;
}

void Shape::setUseGlobalVertexColor(bool value)
{
    m_useGlobalVertexColor = value;
}

void Shape::setUseGlobalEdgeColor(bool value)
{
    m_useGlobalEdgeColor = value;
}

void Shape::setUseGlobalPolygonColor(bool value)
{
    m_useGlobalPolygonColor = value;
}

void Shape::setEdgeWidth(float width)
{
    m_edgeWidth = width;
}

void Shape::setVertexSize(float size)
{
    m_vertexSize = size;
}

RenderData Shape::getRenderData()
{
    RenderData data;

    // Setup Flags
    data.DrawVertices = m_renderVertices;
    data.DrawEdges    = m_renderEdges;
    data.DrawPolygons = m_renderPolygons;
    data.UseModelMatr = m_useModelMatr;
    data.UseViewMatr  = m_useViewMatr;
    data.UseProjMatr  = m_useProjMatr;
    data.UseGlobalVertexColor = m_useGlobalVertexColor;
    data.UseGlobalEdgeColor = m_useGlobalEdgeColor;
    data.UseGlobalPolygonColor = m_useGlobalPolygonColor;

    // Setup Data

    data.VertexData = m_vertexData;

    data.Vertices.reserve(m_vertices.size());
    for (auto v : m_vertices) {
        RenderData::Vertex dv;
        dv.index = v.index;
        dv.color = v.color;

        data.Vertices.push_back(dv);
    }

    data.Edges.reserve(m_edges.size());
    for (auto e : m_edges) {
        data.Edges.push_back({e.indexBegin, e.indexEnd});

        RenderData::Edge de;
        de.begin = e.indexBegin;
        de.end = e.indexEnd;
        de.color = e.color;

        data.Edges.push_back(de);
    }

    data.Polygons.reserve(m_polygons.size());
    for (auto p : m_polygons) {
        RenderData::Polygon dp;
        dp.indices = p.indices;
        dp.color = p.color;

        data.Polygons.push_back(dp);
    }

    // Setup Global values
    data.GlobalVertexColor = m_globalVertexColor;
    data.GlobalEdgeColor = m_globalEdgeColor;
    data.GlobalPolygonColor = m_globalPolygonColor;

    // Setup Misc Visual values
    data.EdgeWidth = m_edgeWidth;
    data.VertexSize = m_vertexSize;

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