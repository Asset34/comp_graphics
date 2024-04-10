#include "scenes/scenelr1.h"

SceneLR1::SceneLR1()
{
    // Setup Shape
    m_shape.setVertices({
        { -0.5f,  0.5f,  0.5f },
        { -0.5f, -0.5f,  0.5f },
        {  0.5f, -0.5f,  0.5f },
        {  0.5f,  0.5f,  0.5f },
        { -0.5f,  0.5f, -0.5f },
        { -0.5f, -0.5f, -0.5f },
        {  0.5f, -0.5f, -0.5f },
        {  0.5f,  0.5f, -0.5f }
    });
    m_shape.definePolygon({0, 1, 2, 3}, {1.0, 0.0, 0.0});
    m_shape.definePolygon({4, 5, 6, 7}, {0.0, 1.0, 0.0});
    m_shape.definePolygon({0, 4, 7, 3}, {0.0, 0.0, 1.0});
    m_shape.definePolygon({1, 5, 6, 2}, {1.0, 0.0, 1.0});
    m_shape.definePolygon({3, 7, 6, 2}, {1.0, 1.0, 0.0});
    m_shape.definePolygon({0, 4, 5, 1}, {0.0, 1.0, 1.0});
    
    // Setup Renderables
    m_renderables.reserve(1);
    m_renderables.push_back(&m_shape);
    
    // Setup scrne background color
    m_backgroundColor = {0.2, 0.2, 0.2};
}

SceneLR1::~SceneLR1()
{
}

void SceneLR1::update()
{
}

RenderProviderData SceneLR1::getRenderProviderData()
{
    RenderProviderData data;

    data.BackgroundColor = m_backgroundColor;

    return data;
}

const std::vector<Renderable*> &SceneLR1::getRenderables()
{
    return m_renderables;
}

std::vector<int> SceneLR1::getRenderableUpdateVector()
{
    return {};
}
