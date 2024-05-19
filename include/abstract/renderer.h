#ifndef RENDERER_H_
#define RENDERER_H_

#include "abstract/renderprovider.h"

class Renderer {
public:
    virtual ~Renderer() {};

    virtual void attach(RenderProvider *p);
    virtual void update() = 0;
    virtual void render() = 0;

protected:
    RenderProvider *getProvider();
    bool providerAttached() const;

private:
    RenderProvider *m_provider = nullptr;
    
};

#endif // RENDERER_H_