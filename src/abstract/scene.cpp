#include "abstract/scene.h"

const Color Scene::BACKGROUND_COLOR = {0.25, 0.25, 0.25};

void Scene::setBackgroundColor(const Color &color)
{
    m_backgroundColor = color;
}

const Color &Scene::getBackgroundColor() const
{
    return m_backgroundColor;
}
