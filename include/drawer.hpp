#ifndef MCLINES_DRAWER_HPP_
#define MCLINES_DRAWER_HPP_

#include <opencv2/opencv.hpp>

class line_drawer
{
    cv::Mat m_mat;

public:
    line_drawer();
    ~line_drawer();
    
    void draw_poly(const cv::Size& size, const cv::Point * pts, const cv::Scalar& color, bool flip);
    void save(const cv::String& filepath);
    void transparent();
};

#endif
