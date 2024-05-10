#include "workspace.h"

Workspace::Workspace()
    : m_scene(nullptr),
      m_renderer(nullptr),
      m_uiManager(nullptr)
{
}

Workspace::~Workspace()
{
    if (m_scene) delete m_scene;   
    if (m_renderer) delete m_renderer;   
    if (m_uiManager) delete m_uiManager;   
}

void Workspace::attach(Scene *scene, Renderer *renderer, UiManager *manager)
{
    m_scene = scene;
    m_renderer = renderer;
    m_uiManager = manager;
}

void Workspace::run()
{
    if (m_scene) m_scene->update();
    if (m_renderer) {
        m_renderer->updateData();
        m_renderer->render();
    }
    if (m_uiManager) m_uiManager->manage();
}

void Workspace::update()
{
    m_uiManager->update();
}

UiManager *Workspace::getUiManager() const
{
    return m_uiManager;
}