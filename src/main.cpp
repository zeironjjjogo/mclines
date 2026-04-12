#include "../include/diag.hpp"
#include "../include/drawer.hpp"

#include <random>
#include <ranges>
#include <strstream>

class ctrl
{
    diag_calcer m_dc;
    line_drawer m_ld;

    static constexpr int n_points = 4;
public:
    ctrl(int w, int h, const cv::String& fpath, int color[3]) : m_dc(w, h), m_ld()
    {
        size_property size_pro = m_dc.calc_size();
        const auto &lines = m_dc.calc_line();

        int n_img_written = 0;
        
        for (const auto& line : lines)
        {
            std::cout << line << std::endl;

            const auto moved_line = m_dc.move_origin(line);

            cv::Point2i pad(size_pro.padx, size_pro.pady);
            cv::Size mat_size(std::ceil(size_pro.x), std::ceil(size_pro.y));
            cv::Point2f p0(moved_line.p0.x, moved_line.p0.y), p1(moved_line.p1.x, moved_line.p1.y);

            cv::Point2f top(size_pro.abspadx + size_pro.padx, size_pro.abspady + size_pro.pady), bot(size_pro.abspadx - size_pro.padx, size_pro.abspady - size_pro.pady);

            cv::Scalar line_color(color[2], color[1], color[0], 0xff);

            // cv::String filename = fpath + std::to_string(n_img_written) + ".png";
            cv::String filename = generate_filename(fpath, n_img_written, m_dc.get_size(), mat_size);

            std::cout << filename << std::endl;
            std::cout << p0 << ", " << p1 << std::endl;
            std::cout << mat_size << ", " << pad << std::endl;

            std::cout << top + p0 << std::endl;
            std::cout << bot + p0 << std::endl;
            std::cout << bot + p1 << std::endl;
            std::cout << top + p1 << '\n' << std::endl;

            m_ld.draw_poly(mat_size, create_points(size_pro, p0, p1), n_points, line_color);
            m_ld.save(filename);
            n_img_written++;
        }
    }

        

    [[nodiscard]]
    cv::Point *create_points(const size_property& sp, const cv::Point2f& p0, const cv::Point2f& p1)
    {
        cv::Point* pts = new cv::Point[n_points];
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

    static cv::String generate_filename(const cv::String& name, int index, int srcsize, const cv::Size& dstsize)
    {
        float width_scale = dstsize.width / srcsize;
        float height_scale = dstsize.height / srcsize;

        std::random_device rd {};
        std::mt19937_64 mt { rd() };

        int random_n = mt();
        constexpr int Base = 36;

        const char Digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
        cv::String random_str;

        do
        {
            random_str.push_back(Digits[random_n % Base]);
            random_n /= Base;
        } while (random_n);
        std::ranges::reverse(random_str);

        std::ostringstream oss;

        oss << height_scale << '&' << width_scale << '&' << random_str << '&' << name << index << ".png";

        return oss.str();
    }

};

int main(int argc, char **argv)
{
    int line_color[3] = { 0xff, 0xff, 0xff };
    for (int i = 0; i < argc; i++)
    {
        std::cout << argv[i] << "\t";
    }
    std::cout << std::endl;

    std::cout << argv[4][0] << 'o' << (argv[4][0] == 'o') << std::endl;

    if (argc < 4)
        return -1;
    
    if (argc == 5 && argv[4][0] == 'o')
    {
        line_color[1] = 0x66;
        line_color[2] = 0x00;
        std::cout << "orange" << std::endl;
    }
    
    try
    {
        ctrl(atoi(argv[1]), atoi(argv[2]), argv[3], line_color);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
