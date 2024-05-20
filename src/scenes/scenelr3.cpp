#include "scenes/scenelr3.h"

SceneLR3::SceneLR3()
{
}

void SceneLR3::control(int cmd)
{
}

bool SceneLR3::updated()
{
    return false;
}

void SceneLR3::updateAck()
{
}

const std::list<int> &SceneLR3::getUpdateList()
{
    return m_updateList;
}
