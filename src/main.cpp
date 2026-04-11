#include "../include/diag.hpp"
#include "../include/drawer.hpp"

class ctrl
{
    diag_calcer m_dc;
    line_drawer m_ld;
public:
    ctrl(int w, int h, const cv::String& fpath) : m_dc(w, h), m_ld(fpath)
    {
        size_property size_pro = m_dc.calc_size();
        const auto &lines = m_dc.calc_line();
        for (const auto& line : lines)
        {
            std::cout << line << std::endl;

            const auto moved_line = m_dc.move_origin(line);

            cv::Point2i pad(size_pro.padx, size_pro.pady);
            cv::Point2i size(std::ceil(size_pro.x), std::ceil(size_pro.y));
            cv::Point2f p0(moved_line.p0.x, moved_line.p0.y), p1(moved_line.p1.x, moved_line.p1.y);

            std::cout << p0 << ", " << p1 << std::endl;
            std::cout << size << ", " << pad << std::endl;

            std::cout << "[" << size_pro.abspadx + size_pro.padx + p0.x << ", " << size_pro.abspady + size_pro.pady + p0.y << "]" << std::endl;
            std::cout << "[" << size_pro.abspadx - size_pro.padx + p0.x << ", " << size_pro.abspady - size_pro.pady + p0.y << "]" << std::endl;
            std::cout << "[" << size_pro.abspadx - size_pro.padx + p1.x << ", " << size_pro.abspady - size_pro.pady + p1.y << "]" << std::endl;
            std::cout << "[" << size_pro.abspadx + size_pro.padx + p1.x << ", " << size_pro.abspady + size_pro.pady + p1.y << "]\n" << std::endl;

            m_ld.draw_poly(cv::Size(size), create_points(size_pro, p0, p1), 4);
            m_ld.save();
        }
    }

        

    [[nodiscard]]
    cv::Point *create_points(const size_property& sp, const cv::Point2f& p0, const cv::Point2f& p1)
    {
        cv::Point* pts = new cv::Point[4];
        // 0 = 0, pady
        // 1 = padx, 0
        // 2 = size, size - pady
        // 3 = size - padx, size
        pts[0] = cv::Point(sp.abspadx + sp.padx + p0.x, sp.abspady + sp.pady + p0.y);
        pts[1] = cv::Point(sp.abspadx - sp.padx + p0.x, sp.abspady - sp.pady + p0.y);
        pts[2] = cv::Point(sp.abspadx - sp.padx + p1.x, sp.abspady - sp.pady + p1.y);
        pts[3] = cv::Point(sp.abspadx + sp.padx + p1.x, sp.abspady + sp.pady + p1.y);

        return pts;
    }

};

int main(int argc, char **argv)
{
    if (argc < 4)
        return -1;
    
    ctrl(atoi(argv[1]), atoi(argv[2]), argv[3]);
    return 0;
}
