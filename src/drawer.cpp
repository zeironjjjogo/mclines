#include "../include/drawer.hpp"


line_drawer::line_drawer() : m_mat()
{
}

line_drawer::~line_drawer()
{
    m_mat.release();
}

void line_drawer::draw_poly(const cv::Size& size, const cv::Point * pts, const cv::Scalar& color, bool flip)
{
    m_mat = cv::Mat(size.height, size.width, CV_8UC4);
    m_mat = 0;

    cv::fillConvexPoly(m_mat, pts, 4, color);

    if (flip)
    {
        cv::flip(m_mat, m_mat, 0);
    }

    transparent();
    
    if (pts)
        delete[] pts;
    pts = nullptr;
}
                                                                                                                                                                                          
void line_drawer::save(const cv::String& filepath)
{
    cv::namedWindow(filepath);
    cv::imshow(filepath, m_mat);
    cv::waitKey();

    if (!cv::imwrite(filepath, m_mat))
    {
        CV_Error_(cv::Error::StsAssert, ("Failed to save the image (%s).", filepath.c_str()));
    }
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
                m_mat.at<cv::Vec4b>(x, y) = px;
            }
        }
    }
}
