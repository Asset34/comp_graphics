#include "line.h"

Line::Line(const vec3 &begin, const vec3 &end)
    :m_begin(begin),
     m_end(end),
     m_color(1.0f, 1.0f, 1.0f)
{
}

Line::~Line()
{
}

const vec3 &Line::getBegin() const
{
    return m_begin;
}

const vec3 &Line::getEnd() const
{
    return m_end;
}

const vec3 &Line::getColor() const
{
    return m_color;
}

vec3 Line::getPoint() const
{
    return getModelMatrix() * vec4(m_begin, 1.0f);
}

vec3 Line::getUnit() const
{
    vec3 d = m_end - m_begin;

    vec3 td = this->getModelMatrix() * vec4(d, 1.0f);

    return glm::normalize(td);
}

void Line::setBegin(const vec3 &begin)
{
    m_begin = begin;
}

void Line::setEnd(const vec3 &end)
{
    m_end = end;
}

void Line::setColor(const vec3 &color)
{
    m_color = color;
}
