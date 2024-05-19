#include "glrenderer.h"

bool GLRenderer::Initialized = false;

void GLRenderer::init() {
    if (Initialized) {
        return;
    }

    // Load GL pointers
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); 

    // Enable possibility of antialiasing (Antialiasing is on by default)
    glEnable(GL_DEPTH_TEST); 
    glEnable(GL_MULTISAMPLE); 

    // Acknowledge initialization
    Initialized = true;
}

void GLRenderer::attach(RenderProvider *p)
{
    Renderer::attach(p);

    m_units.clear();

    // Check for provider
    if (!this->providerAttached()) return;

    // Load all provided renderable objects
    for (auto &obj : p->getAllObjects()) {
        this->loadObject(obj);
    }

    // Acknowledge changes
    this->getProvider()->changedAck();
}

void GLRenderer::update()
{
    // Check for provider
    if (!this->providerAttached()) return;

    // Process provided objects to be removed
    for (int id : this->getProvider()->getRemovedObjectsIds()) {
        this->unloadObect(id);
    }

    // Process provided objects to be added
    for (auto &obj : this->getProvider()->getNewObjects()) {
        this->loadObject(obj);
    }

    // Update objects (if required)
    for (auto &unit : m_units) {
        unit.update();
    }

    // Acknowledge changes
    this->getProvider()->changedAck();
}

void GLRenderer::render()
{
    // Check for provider
    if (!this->providerAttached()) return;

    // Get explicit data (for convenience)
    const GlobalRenderData &data = this->getProvider()->getGlobalRenderData();

    // Prepare render with global data
    glClearColor(data.BackgroundColor.r, data.BackgroundColor.g, data.BackgroundColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render objects
    for (auto &unit : m_units) {
        unit.render(data);
    }
}

void GLRenderer::loadObject(RenderableObj *r)
{
    m_units.push_back(GLRendererUnit(r));
}

void GLRenderer::unloadObect(int id)
{
    for (auto it = m_units.begin(); it != m_units.end(); ++it) {
        if (it->getAssociatedId() == id) {
            m_units.erase(it);
            break;
        }
    }
}
