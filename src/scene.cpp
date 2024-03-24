#include "scene.h"

Scene::Scene()
    :m_shape(0, 0)
{
    // Setup shape
    this->makeTestShape1();
    m_shape.scaleItselfTo(vec3(0.2, 0.2, 0.2));
    m_shape.translate(vec3(-0.5, 0.3, 0.0));
    m_shape.reflect(vec3(0.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0));

    // m_shape.translate(vec3(0.0, 0.5, 0.0));
    // m_shape.scale(vec3(1, 2, 1));
    // m_shape.rotateItself(vec3(0, 0, 45));


    // Define camera (view matrix)
    m_viewMatrix = mat4(1.0f);

    // Setup background color
    m_backgroundColor = vec3(0.2f, 0.2f, 0.2f);
}

void Scene::update()
{
    // m_shape.rotate(vec3(0, 0, 1));
    // m_shape.rotateItself(vec3(1, 2, -3));
    // m_shape.rotateAround(1, vec3(0.5, 0.25, 0.0), vec3(1.0, 0.0, 1.0));

    // m_shape.rotateItself(vec3(0, 0, 1));
}

const vec3 &Scene::getBackgroundColor() const
{
    return m_backgroundColor;
}

const mat4 &Scene::getViewMatrix() const
{
    return m_viewMatrix;
}

const Shape &Scene::getShape() const
{
    return m_shape;
}

void Scene::makeTestShape1()
{
    m_shape = Shape(8, 6);

    // Set vertices
    m_shape.setVertex(0, vec3(-0.5f,  0.5f,  0.5f));
    m_shape.setVertex(1, vec3(-0.5f, -0.5f,  0.5f));
    m_shape.setVertex(2, vec3( 0.5f, -0.5f,  0.5f));
    m_shape.setVertex(3, vec3( 0.5f,  0.5f,  0.5f));
    m_shape.setVertex(4, vec3(-0.5f,  0.5f, -0.5f));
    m_shape.setVertex(5, vec3(-0.5f, -0.5f, -0.5f));
    m_shape.setVertex(6, vec3( 0.5f, -0.5f, -0.5f));
    m_shape.setVertex(7, vec3( 0.5f,  0.5f, -0.5f));

    // Define polygones
    m_shape.definePolygon(0, {0, 1, 2, 3}, vec3(1.0f, 0.0f, 0.0f));
    m_shape.definePolygon(1, {4, 5, 6, 7}, vec3(0.0f, 1.0f, 0.0f));
    m_shape.definePolygon(2, {0, 4, 7, 3}, vec3(0.0f, 0.0f, 1.0f));
    m_shape.definePolygon(3, {1, 5, 6, 2}, vec3(1.0f, 0.0f, 1.0f));
    m_shape.definePolygon(4, {3, 7, 6, 2}, vec3(1.0f, 1.0f, 0.0f));
    m_shape.definePolygon(5, {0, 4, 5, 1}, vec3(0.0f, 1.0f, 1.0f));
}
