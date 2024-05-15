#include "objects/shape3d.h"

const vec3 Shape3D::COLOR_DEFAULT = {0, 0, 0};

Shape3D::Shape3D()
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

Shape3D::~Shape3D()
{
}

void Shape3D::setVertexData(const std::vector<vec3> &vertexData)
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

void Shape3D::defineVertex(int index, const vec3 &color)
{
    Vertex v;
    v.index = index;
    v.color = color;

    m_vertices.push_back(v);
}

void Shape3D::defineEdge(int indexBegin, int indexEnd, const vec3 &color)
{
    Edge e;
    e.indexBegin = indexBegin;
    e.indexEnd = indexEnd;
    e.color = color;

    m_edges.push_back(e);
}

void Shape3D::definePolygon(const std::vector<int> &indices, const vec3 &color)
{
    Polygon p;
    p.indices = indices;
    p.color = color;

    m_polygons.push_back(p);
}

void Shape3D::setGlobalVertexColor(const vec3 &color)
{
    m_globalVertexColor = color;
}

void Shape3D::setGlobalEdgeColor(const vec3 &color)
{
    m_globalEdgeColor = color;
}

void Shape3D::setGlobalPolygonColor(const vec3 &color)
{
    m_globalPolygonColor = color;
}

void Shape3D::setRenderVerticesFlag(bool value)
{
    m_renderVertices = value;
}

void Shape3D::setRenderEdgesFlag(bool value)
{
    m_renderEdges = value;
}

void Shape3D::setRenderPolygonsFlag(bool value)
{
    m_renderPolygons = value;
}

void Shape3D::setUseModelMatrFlag(bool value)
{
    m_useModelMatr = value;
}

void Shape3D::setUseViewMatrFlag(bool value)
{
    m_useViewMatr = value;
}

void Shape3D::setUseProjMatrFlag(bool value)
{
    m_useProjMatr = value;
}

void Shape3D::setUseGlobalVertexColor(bool value)
{
    m_useGlobalVertexColor = value;
}

void Shape3D::setUseGlobalEdgeColor(bool value)
{
    m_useGlobalEdgeColor = value;
}

void Shape3D::setUseGlobalPolygonColor(bool value)
{
    m_useGlobalPolygonColor = value;
}

void Shape3D::setEdgeWidth(float width)
{
    m_edgeWidth = width;
}

void Shape3D::setVertexSize(float size)
{
    m_vertexSize = size;
}

RenderData Shape3D::getRenderData()
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
        RenderData::RenderVertex dv;
        dv.index = v.index;
        dv.color = v.color;

        data.Vertices.push_back(dv);
    }

    data.Edges.reserve(m_edges.size());
    for (auto e : m_edges) {
        data.Edges.push_back({e.indexBegin, e.indexEnd});

        RenderData::RenderEdge de;
        de.begin = e.indexBegin;
        de.end = e.indexEnd;
        de.color = e.color;

        data.Edges.push_back(de);
    }

    data.Polygons.reserve(m_polygons.size());
    for (auto p : m_polygons) {
        RenderData::RenderPolygon dp;
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

glm::mat4 Shape3D::getTransformation()
{
    return this->getModelMatrix();
}

const vec3 &Shape3D::selfOrigin() const
{
    return m_center;
}

void Shape3D::transformationCallback()
{
    TransformableObj3D::transformationCallback();

    // Update center
    m_center = this->getModelMatrix() * vec4(m_centerValue, 1);
}