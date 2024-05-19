#include "objects/shape3d.h"

const Color Shape3D::COLOR_DEFAULT = {0, 0, 0};

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

void Shape3D::defineVertex(int index, const Color &color)
{
    Vertex v;
    v.index = index;
    v.color = color;

    m_vertices.push_back(v);
}

void Shape3D::defineEdge(int indexBegin, int indexEnd, const Color &color)
{
    Edge e;
    e.begin = indexBegin;
    e.end = indexEnd;
    e.color = color;

    m_edges.push_back(e);
}

void Shape3D::definePolygon(const std::vector<int> &indices, const Color &color)
{
    Polygon p;
    p.indices = indices;
    p.color = color;

    m_polygons.push_back(p);
}

void Shape3D::setGlobalVertexColor(const Color &color)
{
    m_globalVertexColor = color;
}

void Shape3D::setGlobalEdgeColor(const Color &color)
{
    m_globalEdgeColor = color;
}

void Shape3D::setGlobalPolygonColor(const Color &color)
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

const RenderData &Shape3D::getRenderData()
{
    // Setup Transformation Matrix
    m_renderData.ModelMatrix = this->getModelMatrix();

    // Setup Flags
    m_renderData.DrawVertices          = m_renderVertices;
    m_renderData.DrawEdges             = m_renderEdges;
    m_renderData.DrawPolygons          = m_renderPolygons;
    m_renderData.UseModelMatr          = m_useModelMatr;
    m_renderData.UseViewMatr           = m_useViewMatr;
    m_renderData.UseProjMatr           = m_useProjMatr;
    m_renderData.UseGlobalVertexColor  = m_useGlobalVertexColor;
    m_renderData.UseGlobalEdgeColor    = m_useGlobalEdgeColor;
    m_renderData.UseGlobalPolygonColor = m_useGlobalPolygonColor;

    // Setup Data
    m_renderData.VertexData = m_vertexData;
    m_renderData.Vertices = m_vertices;
    m_renderData.Edges = m_edges;
    m_renderData.Polygons = m_polygons;

    // Setup Visual valies
    m_renderData.GlobalVertexColor  = m_globalVertexColor;
    m_renderData.GlobalEdgeColor    = m_globalEdgeColor;
    m_renderData.GlobalPolygonColor = m_globalPolygonColor;
    m_renderData.EdgeWidth          = m_edgeWidth;
    m_renderData.VertexSize         = m_vertexSize;

    return m_renderData;
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