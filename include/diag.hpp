#ifndef MCLINES_DIAG_HPP_
#define MCLINES_DIAG_HPP_

#include <ostream>
#include <vector>

template <typename T>
struct point_t
{
    T x, y;
    friend bool operator==(const point_t<T>& lh, const point_t<T>& rh)
    { return lh.x == rh.x && lh.y == rh.y; }
    friend std::ostream& operator <<(std::ostream& os, const point_t<T>& point)
    { return os << "(" << point.x << ", " << point.y << ")"; }
};

using f_point = point_t<float>;
using i_point = point_t<int>;

template <typename T>
struct diag_line_t
{
    point_t<T> p0, p1;
    friend bool operator==(const diag_line_t<T>& lh, const diag_line_t<T>& rh)
    { return lh.p0 == rh.p0 && lh.p1 == rh.p1; }
    friend std::ostream& operator <<(std::ostream& os, const diag_line_t<T>& line)
    { return os << "{" << line.p0 << ", " << line.p1 << "}"; }
};

using diag_line = diag_line_t<float>;

struct size_property
{
    float x, y, padx, pady, abspadx, abspady;
};

struct pad_t
{
    float padx, pady;
};

diag_line calc(float &x, float& y);

class diag_calcer
{
    constexpr static int N_SPLIT = 16;
    constexpr static int N_LINE = 2;
    constexpr static int PIXEL_SIZE = 8;

    i_point m_p0, m_p1;
    int m_n_w, m_n_h;
    float m_slope;
public: 
    diag_calcer(int p0x, int p0y, int p1x, int p1y);
    diag_calcer(int p1x, int p1y);
    f_point calc_padding();
    diag_line calc_block(float &p0x, float &p0y);
    std::vector<diag_line> calc_line();
    size_property calc_size();
    static diag_line move_origin(const diag_line& line);
};


#endif
