#ifndef RENDERPROVIDER_H_
#define RENDERPROVIDER_H_

#include "abstract/renderableobj.h"
#include "glm/glm.hpp"
#include <list>

struct GlobalRenderData {

    // Visual
    Color BackgroundColor;

    // Transformation Matrices
    mat4 ViewMatrix = mat4(1); // default: Identity Matrix
    mat4 ProjMatrix = mat4(1); // default: Identity Matrix

};

class RenderProvider {
public:
    virtual ~RenderProvider() {};

    virtual const GlobalRenderData &getGlobalRenderData() = 0;

    const std::list<RenderableObj*> &getAllObjects();
    const std::list<RenderableObj*> &getNewObjects();
    const std::list<int> &getRemovedObjectsIds();
    void changedAck();

protected:
    void addObject(RenderableObj *r);
    void removeObject(RenderableObj *r);

private:
    std::vector<RenderableObj*> m_renderObjects;

    std::list<RenderableObj*> m_allObjects;
    std::list<RenderableObj*> m_newObjects;
    std::list<int> m_removedObjectsIds;

};

#endif// RENDERPROVIDER_H_