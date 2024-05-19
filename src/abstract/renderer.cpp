#include "abstract/renderer.h"

void Renderer::attach(RenderProvider *p)
{
    m_provider = p;
}

RenderProvider *Renderer::getProvider()
{
    return m_provider;
}

bool Renderer::providerAttached() const
{
    return (m_provider) ? true : false;
}
