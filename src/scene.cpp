#include "scene.h"

Scene::Scene()
{
    // TODO: Create shape
    m_shape = new Shape(6);
    Polygon p[6];

    p[0].vertices = {
        vec3(50.0f ,  50.0f, 50.0f),
        vec3(50.0f , -50.0f, 50.0f),
        vec3(-50.0f, -50.0f, 50.0f),
        vec3(-50.0f,  50.0f, 50.0f)
    };
    p[1].vertices = {
        vec3(50.0f ,  50.0f, -50.0f),
        vec3(50.0f , -50.0f, -50.0f),
        vec3(-50.0f, -50.0f, -50.0f),
        vec3(-50.0f,  50.0f, -50.0f)
    };
    p[2].vertices = {
        vec3(50.0f,  50.0f,  50.0f),
        vec3(50.0f, -50.0f,  50.0f),
        vec3(50.0f, -50.0f, -50.0f),
        vec3(50.0f,  50.0f, -50.0f)
    };
    p[3].vertices = {
        vec3(-50.0f,  50.0f,  50.0f),
        vec3(-50.0f, -50.0f,  50.0f),
        vec3(-50.0f, -50.0f, -50.0f),
        vec3(-50.0f,  50.0f, -50.0f)
    };
    p[4].vertices = {
        vec3(50.0f , 50.0f,  50.0f),
        vec3(50.0f , 50.0f, -50.0f),
        vec3(-50.0f, 50.0f, -50.0f),
        vec3(-50.0f, 50.0f,  50.0f)
    };
    p[5].vertices = {
        vec3(50.0f , -50.0f,  50.0f),
        vec3(50.0f , -50.0f, -50.0f),
        vec3(-50.0f, -50.0f, -50.0f),
        vec3(-50.0f, -50.0f,  50.0f)
    };

    p[0].color = vec3(0.25f, 0.25f, 0.25f);
    p[1].color = vec3(1.0f, 0.0f, 0.0f);
    p[2].color = vec3(0.0f, 1.0f, 0.0f);
    p[3].color = vec3(0.0f, 0.0f, 1.0f);
    p[4].color = vec3(1.0f, 1.0f, 0.0f);
    p[5].color = vec3(1.0f, 0.0f, 1.0f);

    for (int i = 0; i < 6; i++) {
        m_shape->setPolygon(i, p[i]);
    }

    // TODO: Define camera (view matrix)
    m_viewMatrix = mat4(1.0f);

    // TODO: Setup background color
    m_backgroundColor = vec3(1.0f, 1.0f, 1.0f);
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
