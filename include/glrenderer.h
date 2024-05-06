#ifndef GLRENDERER_H_
#define GLRENDERER_H_

#include "abstract/renderer.h"
#include "shader.h"
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include <vector>

class GLRenderer : public Renderer {
public:
    ~GLRenderer();

    void init() override;
    void attach(RenderProvider *rp);
    void updateData() override;
    void render() override;

private:
    class GLRendererUnit {
    public:
        GLRendererUnit(Renderable *r);
        ~GLRendererUnit();
        
        void updateData();
        void render(const RenderProviderData &data);

    private:
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

        Renderable *m_renderable;

    };

    std::vector<GLRendererUnit> m_units;

};

#endif // GLRENDERER_H_