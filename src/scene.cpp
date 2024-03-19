#include "scene.h"

Scene::Scene()
{
    // TODO: Create shape


    // TODO: Define camera (view matrix)


    // TODO: Setup background color
}

Scene::~Scene()
{
    delete m_shape;
}

void Scene::update()
{
}

const mat4 &Scene::getViewMatrix() const
{
    return m_viewMatrix;
}

const Shape &Scene::getShape() const
{
    return *m_shape;
}
