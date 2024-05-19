#include "abstract/renderableobj.h"

int RenderableObj::NextId = 0;

RenderableObj::RenderableObj()
{
    this->assignId();
}

RenderableObj::RenderableObj(const RenderableObj &obj)
{
    m_updated = false;
}

int RenderableObj::getId()
{
    return m_id;
}

bool RenderableObj::updated()
{
    return m_updated;
}

void RenderableObj::updateAck()
{
    m_updated = false;
}

void RenderableObj::forceUpdate()
{
    m_updated = true;
}

bool RenderableObj::operator==(const RenderableObj &obj)
{
    return m_id == obj.m_id;
}

bool RenderableObj::operator!=(const RenderableObj &obj)
{
    return m_id != obj.m_id;
}

RenderableObj &RenderableObj::operator=(const RenderableObj &obj)
{
    this->assignId();

    return *this;
}

void RenderableObj::setUpdated()
{
    m_updated = true;
}

void RenderableObj::assignId()
{
    m_id = RenderableObj::NextId;
    RenderableObj::NextId++;
}