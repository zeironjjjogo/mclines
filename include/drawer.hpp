#ifndef MCLINES_DRAWER_HPP_
#define MCLINES_DRAWER_HPP_

#include <opencv2/opencv.hpp>

class line_drawer
{
    const cv::String& m_filepath;
    int m_w, m_h;
    cv::Mat m_mat;
    int n_img_wrote = 0;

public:
    line_drawer(const cv::String& filepath);
    line_drawer(int width, int height, const cv::String& filepath);
    ~line_drawer()
    {
        m_mat.release();
    }
    void draw(const cv::Point2f& p0, const cv::Point2f& p1, const cv::Point2i& size);
    void draw_poly(const cv::Size& size, const cv::Point * pts, std::size_t npts);
    void save();
    void transparent();
};

#endif
