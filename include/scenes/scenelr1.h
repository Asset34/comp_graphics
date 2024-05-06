#ifndef SCENELR1_H_
#define SCENELR1_H_

#include "interfaces/controllable.h"
#include "scenes/scene3d.h"
#include "objects/shape.h"
#include "objects/line.h"
#include "objects/axisxyz.h"
#include "objects/plane.h"

#include <list>
#include <vector>

class SceneLR1 : public Scene3D, public Controllable {
public:
    SceneLR1();
    ~SceneLR1();

    void update() override;
    std::vector<int> getRenderableUpdateVector() override;

    void set(int vid, float value) override;
    void set(int vid, const float values[]) override;
    void get(int vid, float &receiver) override;
    void get(int vid, float receiver[]) override;

    void control(int cmd) override;
    bool updated() override;
    void updateAck() override;
    std::list<int> getUpdateList() override;

private:
    enum Commands {
        CMD_SHAPE_SET = 0,
        CMD_LINE_BEGIN_SET = 1,
        CMD_LINE_END_SET = 2,
        CMD_ROTATE = 3
    };

    enum ValueIds {
        VID_SHAPE_POS = 0,
        VID_LINE_BEGIN_POS = 1,
        VID_LINE_END_POS = 2,
        VID_ROTATION_ANGLE = 3
    };

    Shape m_shape;
    Line m_line;
    AxisXYZ m_axisXYZ;
    Plane m_plane;
    
    // Control values
    vec3 m_shapePos;
    vec3 m_lineBeginPos, m_lineEndPos;
    float m_rotationAngle;
    bool m_updated;
    std::list<int> m_updateList;

};

#endif // SCENELR1_H_