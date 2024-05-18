#ifndef SCENELR2_H_
#define SCENELR2_H_

#include "scenes/scene2d.h"
#include "interfaces/controllable.h"
#include "objects/bsplinepolygon2d.h"
#include "objects/bspline2d.h"

class SceneLR2 : public Scene2D, public Controllable {
public:
    SceneLR2();
    ~SceneLR2() {};
    
    void update() override;
    std::vector<int> getRenderableUpdateVector() override;

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
    std::list<int> getUpdateList() override;

private:
    void buildSpline();
    void initRenderUpdateList();

    void rememberSpline();
    void clearRememberedSplines();

    enum Commands {
        CMD_CONTROL_POINT_SET,
        CMD_KNOT_SET,
        CMD_ORDER_SET,
        CMD_STEP_SET,
        CMD_COLOR_SET,
        CMD_SHOW_CONTROL_POINTS_SWITCH,
        CMD_SOW_CONTROL_POLYGON_SWITCH,
        CMD_KNOTS_UNIFORM,
        CMD_KNOTS_OPENUNIFORM,
        CMD_REMEMBER_SPLINE,
        CMD_CLEAR_REMEMBERED_SPLINES
    };

    enum ValueIds {
        VID_CONTROL_POINT_SIZE,
        VID_CONTROL_POINT_INDEX,
        VID_CONTROL_POINT_VALUE,
        VID_KNOT_SIZE,
        VID_KNOT_INDEX,
        VID_KNOT_VALUE,
        VID_KNOTS,
        VID_ORDER_MAX,
        VID_ORDER_VALUE,
        VID_RENDER_STEP,
        VID_RENDER_COLOR,
        VID_CONTROL_POINTS_FLAG,
        VID_CONTROL_POLYGON_FLAG,
        VID_KNOT_STEP,
        VID_REMEMBERED_SPLINE_SIZE,
        VID_REMEMBERED_SPLINE_INDEX,
        VID_REMEMBERED_SPLINE_KNOTS_SIZE,
        VID_REMEMBERED_SPLINE_KNOTS,
        VID_REMEMBERED_SPLINE_ORDER,
        VID_REMEMBERED_SPLINE_COLOR
    };

    // Objects
    BSplinePolygon2D m_splinePolygon;
    std::vector<BSpline2D> m_rememberedSplines;
    BSpline2D m_spline;
    
    // Control values
    
    int m_controlPointIndex;
    vec2 m_controlPoint;
    int m_knotIndex;
    float m_knot;
    int m_order;
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

#endif // SCENELR2_H_