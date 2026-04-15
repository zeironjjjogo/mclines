#include "../include/diag.hpp"

#include <iostream>
#include <cmath>


diag_calcer::diag_calcer(int p0x, int p0y, int p1x, int p1y)
 : m_p0({ p0x, p0y }), m_p1({ p1x, p1y }),
    m_n_w(p1x - p0x), m_n_h(p1y - p0y),
    m_slope(static_cast<float>(m_n_h) / m_n_w)
{
}

diag_calcer::diag_calcer(int p1x, int p1y) : diag_calcer(0, 0, p1x, p1y) {}

diag_line diag_calcer::calc_block(float &p0x, float &p0y)
{
    int next_x_int = static_cast<int>(p0x + 1);
    int next_y_int = static_cast<int>(p0y + 1);

    float p1x = next_y_int / m_slope;
    float p1y = m_slope * next_x_int;

    if (next_x_int < p1x)
        p1x = p1y / m_slope;

    if (next_y_int < p1y)
        p1y = m_slope * p1x;

    f_point p0 { p0x, p0y };
    p0x = p1x;
    p0y = p1y;

    return diag_line { p0, f_point { p1x, p1y } };
}

std::vector<diag_line> diag_calcer::calc_line()
{
    float x = 0;
    float y = 0;
    std::vector<diag_line> results {};

    while (x < m_n_w && y < m_n_h)
    {
        results.push_back(calc_block(x, y));
    }

    return results;
}

f_point diag_calcer::calc_padding()
{
    float o_slope = -1 / m_slope;

    constexpr auto calc_x = [](float a, int scale = 1)
    {
        return scale / std::sqrt(1 + a * a);
    };
    constexpr auto calc_y = [](float a, int scale = 1)
    {
        return a * scale / std::sqrt(1 + a * a);
    };

    return { calc_x(o_slope, PIXEL_SIZE), calc_y(o_slope, PIXEL_SIZE) };
}
   
size_property diag_calcer::calc_size()
{
    constexpr int SIZE = PIXEL_SIZE * N_SPLIT;

    f_point pad = calc_padding();
    float absx = std::abs(pad.x), absy = std::abs(pad.y);

    return {
        SIZE + absx * 2,
        SIZE + absy * 2,
        pad.x, pad.y,
        absx, absy
    };
}

diag_line diag_calcer::move_origin(const diag_line& line)
{
    constexpr int SCALE = PIXEL_SIZE * N_SPLIT;

    int floored_x = std::floor(line.p0.x);
    int floored_y = std::floor(line.p0.y);

    return {
        { (line.p0.x - floored_x) * SCALE, (line.p0.y - floored_y) * SCALE },
        { (line.p1.x - floored_x) * SCALE, (line.p1.y - floored_y) * SCALE }
    };
}
