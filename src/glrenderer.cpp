#include "glrenderer.h"

bool GLRenderer::m_initialized = false;

GLRenderer::~GLRenderer()
{
}

void GLRenderer::init() {
    if (m_initialized) {
        return;
    }

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE); 

    m_initialized = true;
}

void GLRenderer::attach(RenderProvider *rp)
{
    Renderer::attach(rp);

    const std::vector<Renderable*> renderables = rp->getRenderables();
    m_units.reserve(renderables.size());
    for (auto r : renderables) {
        m_units.push_back(GLRendererUnit(r));
    }
}

void GLRenderer::updateData()
{
    if (!m_provider) {
        return;
    }

    std::vector<int> v = m_provider->getRenderableUpdateVector();
    for (auto i : v) {
        m_units[i].updateData();
    }
}

void GLRenderer::render()
{
    if (!m_provider && !m_initialized) {
        return;
    }

    GlobalRenderData data = m_provider->getGlobalRenderData();

    // Render global
    glClearColor(data.BackgroundColor.r, data.BackgroundColor.g, data.BackgroundColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render renderables
    for (auto u : m_units) {
        u.render(data);
    }
}
