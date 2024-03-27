#include "scene.h"

#include <iostream>

Scene::Scene()
    :m_shape(0, 0)
{
    // Setup shape
    this->makeTestShape2();
    this->shapeInit2();

    // Setup Camera
    // m_camera.setPosition(vec3(0.0f, 50.0f, 100.0f));
    m_camera.setPosition(vec3(-40.0f, -60.0f, 100.0f));
    // m_camera.rotateItselfx(-20);
    m_camera.lookAt();
    // m_camera.rotatex(-45);
    // m_camera.rotateItselfx(30);
    m_camera.setVolume(90.0, 1.0, 10, 1000.0);
    m_camera.setPerspectiveProjection();

    // Setup background color
    m_backgroundColor = vec3(0.2f, 0.2f, 0.2f);
}

void Scene::update()
{
    this->shapeIdleUpdate();
}

void Scene::setCameraAspectRatio(float aspectRatio)
{
    m_camera.setAspectRatio(aspectRatio);
}

const vec3 &Scene::getBackgroundColor() const
{
    return m_backgroundColor;
}

const mat4 &Scene::getViewMatrix()
{
    return m_camera.getViewMatrix();
}

const mat4 &Scene::getProjectionMatrix() const
{
    return m_camera.getProjectionMatrix();
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

    // Define polygons
    m_shape.definePolygon(0, {0, 1, 2, 3}, vec3(1.0f, 0.0f, 0.0f));
    m_shape.definePolygon(1, {4, 5, 6, 7}, vec3(0.0f, 1.0f, 0.0f));
    m_shape.definePolygon(2, {0, 4, 7, 3}, vec3(0.0f, 0.0f, 1.0f));
    m_shape.definePolygon(3, {1, 5, 6, 2}, vec3(1.0f, 0.0f, 1.0f));
    m_shape.definePolygon(4, {3, 7, 6, 2}, vec3(1.0f, 1.0f, 0.0f));
    m_shape.definePolygon(5, {0, 4, 5, 1}, vec3(0.0f, 1.0f, 1.0f));
}

void Scene::shapeInit1()
{
}

void Scene::makeTestShape2()
{
    m_shape = Shape(8, 6);

    // Set vertices
    m_shape.setVertex(0, vec3(-10.0f,  10.0f, -10.0f));
    m_shape.setVertex(1, vec3(-10.0f, -10.0f, -10.0f));
    m_shape.setVertex(2, vec3( 10.0f, -10.0f, -10.0f));
    m_shape.setVertex(3, vec3( 10.0f,  10.0f, -10.0f));
    m_shape.setVertex(4, vec3(-10.0f,  10.0f,  10.0f));
    m_shape.setVertex(5, vec3(-10.0f, -10.0f,  10.0f));
    m_shape.setVertex(6, vec3( 10.0f, -10.0f,  10.0f));
    m_shape.setVertex(7, vec3( 10.0f,  10.0f,  10.0f));

    // Define polygons
    m_shape.definePolygon(0, {0, 1, 2, 3}, vec3(1.0f, 0.0f, 0.0f));
    m_shape.definePolygon(1, {4, 5, 6, 7}, vec3(0.0f, 1.0f, 0.0f));
    m_shape.definePolygon(2, {0, 4, 7, 3}, vec3(0.0f, 0.0f, 1.0f));
    m_shape.definePolygon(3, {1, 5, 6, 2}, vec3(1.0f, 0.0f, 1.0f));
    m_shape.definePolygon(4, {3, 7, 6, 2}, vec3(1.0f, 1.0f, 0.0f));
    m_shape.definePolygon(5, {0, 4, 5, 1}, vec3(0.0f, 1.0f, 1.0f));
}

void Scene::shapeInit2()
{
    // m_shape.translate(vec3(-30.0f, 20.0f, 0.0f));
}

void Scene::shapeIdleUpdate()
{
    // m_shape.rotateAround(1, vec3(-20.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f));
    // m_shape.rotateItselfy(-1);

    // m_camera.rotatex(1);
    // m_camera.lookAt();

    // m_camera.rotateItselfx(-0.5);
    // m_camera.rotateItselfy(0.1);

    // vec3 pos = m_camera.getPosition();
    // std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
}
