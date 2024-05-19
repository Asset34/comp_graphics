#ifndef GLRENDERER_H_
#define GLRENDERER_H_

#include "abstract/renderer.h"
#include "shader.h"
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include <list>

class GLRenderer : public Renderer {
public:
    ~GLRenderer() {};

    static void init();

    void attach(RenderProvider *p) override;
    void update() override;
    void render() override;

private:
    static bool Initialized;

    class GLRendererUnit {
    public:
        GLRendererUnit(RenderableObj *r);
        ~GLRendererUnit() {};
        
        void update();
        void render(const GlobalRenderData &data);

        int getAssociatedId();

    private:
        void load();
        void render();

        void loadVertexData(const RenderData &data);
        void loadVertices(const RenderData &data);
        void loadEdges(const RenderData &data);
        void loadPolygons(const RenderData &data);

        void renderVertices(const RenderData &data);
        void renderEdges(const RenderData &data);
        void renderPolygons(const RenderData &data);

        // Buffers
        GLuint m_vao, m_vbo;
        GLuint m_eboVertices, m_eboPolygons, m_eboEdges;

        Shader m_shader;

        RenderableObj *m_obj;

        int m_associatedId;

    };

    void loadObject(RenderableObj *r);
    void unloadObect(int id);
    
    std::list<GLRendererUnit> m_units;

};

#endif // GLRENDERER_H_