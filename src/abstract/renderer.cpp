#include "abstract/renderer.h"

Renderer::Renderer()
    : m_provider(nullptr)
{
}

void Renderer::attach(RenderProvider *rp)
{
    m_provider = rp;
}
