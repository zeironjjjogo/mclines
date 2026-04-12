#ifndef MCLINES_DRAWER_HPP_
#define MCLINES_DRAWER_HPP_

#include <opencv2/opencv.hpp>

class line_drawer
{
    int m_w, m_h;
    cv::Mat m_mat;

public:
    line_drawer();
    line_drawer(int width, int height);
    ~line_drawer()
    {
        m_mat.release();
    }
    void draw(const cv::Point2f& p0, const cv::Point2f& p1, const cv::Point2i& size);
    void draw_poly(const cv::Size& size, const cv::Point * pts, std::size_t npts, const cv::Scalar& color);
    void save(const cv::String& filepath);
    void transparent();
};

#endif
