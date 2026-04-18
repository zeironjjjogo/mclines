#ifndef MCLINES_DIAG_HPP_
#define MCLINES_DIAG_HPP_

#include <opencv2/core/types.hpp>

#include <ostream>
#include <vector>
#include <tuple>

namespace mcls
{
    template <typename T>
    struct line_
    {
        using point_type = cv::Point_<T>;

        point_type p0, p1;

        line_(point_type p_0, point_type p_1) : p0(p_0), p1(p_1) {}
        line_(T p_0_x, T p_0_y, T p_1_x, T p_1_y) : p0(p_0_x, p_0_y), p1(p_1_x, p_1_y) {}

        friend bool operator ==(const line_<T>& lh, const line_<T>& rh)
        { return lh.p0 == rh.p0 && lh.p1 == rh.p1; }

        friend std::ostream& operator <<(std::ostream& os, const line_<T>& line)
        { return os << "[" << line.p0 << ", " << line.p1 << "]"; }
    };

    using line2f = line_<float>;
    using line2i = line_<int>;
}

class diag_calc
{
    static constexpr int N_SPLIT = 16;
    static constexpr int N_LINE = 2;
    static constexpr int PIXEL_SIZE = 8;

    cv::Point2i m_p0, m_p1;
    int m_n_w, m_n_h;
    float m_slope;

public: 
    diag_calc(int p0x, int p0y, int p1x, int p1y);
    diag_calc(int p1x, int p1y);

    mcls::line2f calc_block(float &p0x, float &p0y);
    std::vector<mcls::line2f> calc_line();
    cv::Point2f calc_padding();
    cv::Size2f calc_size();
    std::vector<cv::Point*> generate_points();
    
    static mcls::line2f move_origin(const mcls::line2f& line);
    static constexpr int get_size() { return N_SPLIT * PIXEL_SIZE; }
};

#endif
