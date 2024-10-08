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
    void buildSpline();

    enum Commands {
        CMD_CONTROL_POINT_SET,
        CMD_KNOT_SET,
        CMD_DEGREE_SET,
        CMD_STEP_SET,
        CMD_COLOR_SET,
        CMD_SHOW_CONTROL_POINTS_SWITCH,
        CMD_SOW_CONTROL_POLYGON_SWITCH,
        CMD_KNOTS_UNIFORM,
        CMD_KNOTS_OPENUNIFORM,
        CMD_REMEMBER_SPLINE,
        CMD_CLEAR_SPLINES
    };

    enum ValueIds {
        VID_CONTROL_POINT_SIZE,
        VID_CONTROL_POINT_INDEX,
        VID_CONTROL_POINT_VALUE,
        VID_KNOT_SIZE,
        VID_KNOT_INDEX,
        VID_KNOT_VALUE,
        VID_KNOTS,
        VID_DEGREE_MAX,
        VID_DEGREE_VALUE,
        VID_RENDER_STEP,
        VID_RENDER_COLOR,
        VID_CONTROL_POINTS_FLAG,
        VID_CONTROL_POLYGON_FLAG,
        VID_KNOT_STEP
    };

    // Objects
    BSplinePolygon2D m_splinePolygon;
    std::list<BSpline2D> m_rememberedSplines;
    BSpline2D m_spline;
    
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

};

#endif // SCENELR2_H_