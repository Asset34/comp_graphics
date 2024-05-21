#ifndef SCENELR3_H_
#define SCENELR3_H_

#include "scenes/scene3d.h"
#include "interfaces/controllable.h"
#include "objects/bsurfacepolygon.h"
#include "objects/bsurface.h"

class SceneLR3 : public Scene3D, public Controllable {
public:
    SceneLR3();
    ~SceneLR3() {};
    
    void set(int vid, int value) override;
    void set(int vid, float value) override;
    // void set(int vid, const float values[]) override;
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
    void buildSurface();

    enum Commands {
        CMD_SET_SURFACE_HEIGHT,
        CMD_SET_SURFACE_WIDTH,
        CMD_SET_SURFACE_ROW_VALUE,
        CMD_SET_SURFACE_COLUMN_VALUE,
        CMD_SET_SURFACE_VALUE,
        CMD_HKNOT_SET,
        CMD_HKNOTS_UNIFORM,
        CMD_HKNOTS_OPENUNIFORM,
        CMD_WKNOT_SET,
        CMD_WKNOTS_UNIFORM,
        CMD_WKNOTS_OPENUNIFORM,
        CMD_HDEGREE_SET,
        CMD_WDEGREE_SET,
        CMD_HSTEP_SET,
        CMD_WSTEP_SET,
        CMD_SHOW_CONTROL_POINTS_SWITCH,
        CMD_SHOW_CONTROL_POLYGON_SWITCH
    };

    enum ValueIds {
        VID_SURFACE_HEIGHT,
        VID_SURFACE_WIDTH,
        VID_SURFACE_ROW,
        VID_SURFACE_COLUMN,
        VID_SURFACE_ROW_VALUE,
        VID_SURFACE_COLUMN_VALUE,
        VID_SURFACE_VALUE,
        VID_KNOT_INDEX,
        VID_KNOT_VALUE,
        VID_HKNOT_SIZE,
        VID_WKNOT_SIZE,
        VID_HKNOTS,
        VID_WKNOTS,
        VID_KNOT_STEP,
        VID_HDEGREE_VALUE,
        VID_HDEGREE_MAX,
        VID_WDEGREE_VALUE,
        VID_WDEGREE_MAX,
        VID_HSTEP,
        VID_WSTEP,
        VID_CONTROL_POINTS_FLAG,
        VID_CONTROL_POLYGON_FLAG
    };

    // Objects
    BSurfacePolygon m_surfacePolygon;
    BSurface m_surface;

    // Control values
    int m_surfaceHeight;
    int m_surfaceWidth;
    int m_surfaceRow;
    int m_surfaceColumn;
    float m_surfaceRowValue;
    float m_surfaceColumnValue;
    float m_surfaceValue;

    int m_knotIndex;
    float m_knot;
    float m_knotStep;

    int m_degree;

    float m_renderStep;

    bool m_showControlPoints;
    bool m_showControlPolygon;

    bool m_updated;
    std::list<int> m_updateList;

};

#endif // SCENELR3_H_