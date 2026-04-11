#include "../include/drawer.hpp"

#include <opencv2/opencv.hpp>

void draw(float x0, float y0, float x1, float y1)
{
    cv::Point2f p0(x0, y0), p1(x1, y1);
}

line_drawer::line_drawer(const cv::String& filepath) : m_filepath(filepath), m_mat()
{
    // m_mat = cv::imread()
}

line_drawer::line_drawer(int width, int height, const cv::String& filepath) : m_filepath(filepath), m_w(width), m_h(height), m_mat()
{
}

void line_drawer::draw(const cv::Point2f& p0, const cv::Point2f& p1, const cv::Point2i& size)
{
    m_mat = cv::Mat(size.x, size.y, CV_8UC4);
    cv::line(m_mat, p0, p1, cv::Scalar(0xff, 0xff, 0xff), 16, cv::LINE_4);
}

void line_drawer::draw_poly(const cv::Size& size, const cv::Point * pts, std::size_t npts)
{
    m_mat = cv::Mat(size.height, size.width, CV_8UC4);
    m_mat = 0;
    // float padx = (size.width - 128) / 2; 
    // float pady = (size.height - 128) / 2;
    // cv::rectangle(m_mat, cv::Point(padx, pady), cv::Point(padx + 128, pady + 128), cv::Scalar(0xff, 0x00, 0x00));
    cv::fillConvexPoly(m_mat, pts, npts, cv::Scalar(0xff, 0xff, 0xff));
    transparent();
    
    delete[] pts;
}
                                                                                                                                                                                          
void line_drawer::save()
{
    cv::namedWindow(m_filepath);
    cv::imshow(m_filepath, m_mat);
    cv::waitKey();
    bool result = cv::imwrite(m_filepath + std::to_string(n_img_wrote) + ".png", m_mat);
    if (!result) std::cout << "Failed to write. n = " << n_img_wrote << std::endl;
    ++n_img_wrote;
}

void line_drawer::transparent()
{
    for (int x = 0; x < m_mat.rows; ++x)
    {
        for (int y = 0; y < m_mat.cols; ++y)
        {
            auto px = m_mat.at<cv::Vec4b>(x, y);
            if (px[0] + px[1] + px[2] == 0)
            {
                px[3] = 0;
            }
            else
            {
                px[3] = 0xff;
            }
            m_mat.at<cv::Vec4b>(x, y) = px;
        }
    }
}
