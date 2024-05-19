#include "abstract/renderprovider.h"

const std::list<RenderableObj*> &RenderProvider::getAllObjects()
{
    return m_allObjects;
}

const std::list<RenderableObj*> &RenderProvider::getNewObjects()
{
    return m_newObjects;
}

const std::list<int> &RenderProvider::getRemovedObjectsIds()
{
    return m_removedObjectsIds;
}

void RenderProvider::changedAck()
{
    m_newObjects.clear();
    m_removedObjectsIds.clear();
}

void RenderProvider::addObject(RenderableObj *r)
{
    m_allObjects.push_back(r);
    m_newObjects.push_back(r);
}

void RenderProvider::removeObject(RenderableObj *r)
{
    int removedId;
    for (auto it = m_allObjects.begin(); it != m_allObjects.end(); ++it) {
        if (*(*it) == *r) {
            removedId = (*it)->getId();
            m_removedObjectsIds.push_back(removedId);

            m_allObjects.erase(it);

            return;
        }
    }
}