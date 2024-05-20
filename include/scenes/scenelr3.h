#ifndef SCENELR3_H_
#define SCENELR3_H_

#include "scenes/scene2d.h"
#include "interfaces/controllable.h"


class SceneLR2 : public Scene2D, public Controllable {
public:
    SceneLR2();
    ~SceneLR2() {};
    
    void set(int vid, int value) override;
    void set(int vid, float value) override;
    void set(int vid, const float values[]) override;
    void set(int vid, bool value) override;
    void get(int vid, int &receiver) override;
    void get(int vid, float &receiver) override;
    void get(int vid, bool &receiver) override;
    void get(int vid, float receiver[]) override;

    void control(int cmd) override;
    bool updated() override;
    void updateAck() override;
    const std::list<int> &getUpdateList() override;

private:

    enum Commands {
    };

    enum ValueIds {
    };

    // Objects
    
    // Control values
    
    int m_controlPointIndex;
    vec2 m_controlPoint;
    int m_knotIndex;
    float m_knot;
    int m_degree;
    float m_renderStep;
    vec3 m_renderColor;
    float m_knotStep;
    bool m_showControlPoints;
    bool m_showControlPolygon;
    int m_rememberedSplineIndex;

    bool m_updated;
    std::list<int> m_updateList;

    // Render values
    std::vector<int> m_renderableUpdate;
    int m_nextRenderUpdateIndex;

};

#endif // SCENELR3_H_