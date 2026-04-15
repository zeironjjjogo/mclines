#include "../include/diag.hpp"
#include "../include/drawer.hpp"

#include <random>
#include <ranges>
#include <strstream>
#include <fstream>
#include <filesystem>

class ctrl
{
    static constexpr int n_points = 4;
    static constexpr char DST_DIR[] = "./dst/";

    diag_calcer m_dc;
    line_drawer m_ld;

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

            cv::Size mat_size(std::ceil(size_pro.width), std::ceil(size_pro.height));
            cv::Point2f p0(moved_line.p0.x, moved_line.p0.y), p1(moved_line.p1.x, moved_line.p1.y);

            cv::Scalar line_color(color[2], color[1], color[0], 0xff);

            cv::String filename = generate_filename(fpath, n_img_written, m_dc.get_size(), mat_size);

            m_ld.draw_poly(mat_size, create_points(size_pro, p0, p1), n_points, line_color);
            m_ld.save(filename);
            ++n_img_written;
        }
    }

    [[nodiscard]]
    cv::Point *create_points(const size_property& sp, const cv::Point2f& p0, const cv::Point2f& p1)
    {
        cv::Point* pts = new cv::Point[n_points];
        cv::Point2f top(sp.abspadx + sp.padx, sp.abspady + sp.pady), bot(sp.abspadx - sp.padx, sp.abspady - sp.pady);
        // 0 = 0, pady
        // 1 = padx, 0
        // 2 = size, size - pady
        // 3 = size - padx, size
        pts[0] = top + p0;
        pts[1] = bot + p0;
        pts[2] = bot + p1;
        pts[3] = top + p1;

        return pts;
    }

    static cv::String generate_random_text()
    {
        constexpr int BASE = 36;
        constexpr char DIGITS[] = "0123456789abcdefghijklmnopqrstuvwxyz";

        std::random_device rd;
        std::mt19937_64 mt(rd());
        u_int64_t random_num = mt();
        cv::String random_str;

        do
        {
            random_str.push_back(DIGITS[random_num % BASE]);
            random_num /= BASE;
        }
        while (random_num);

        std::ranges::reverse(random_str);

        return random_str;
    }

    static cv::String generate_filename(const cv::String& name, int index, int srcsize, const cv::Size& dstsize)
    {
        float width_scale = dstsize.width / static_cast<float>(srcsize);
        float height_scale = dstsize.height / static_cast<float>(srcsize);

        std::ostringstream oss;

        oss << DST_DIR << name << "/";
        std::filesystem::path dir = oss.str();
        dir.lexically_normal();

        std::error_code ec;
        std::filesystem::create_directories(dir, ec);
        if (ec)
        {
            std::cerr << "Failed to create or check directories; " << dir << std::endl;
        }

        oss << height_scale << '&' << width_scale << '&' << generate_random_text() << '&' << name << index << ".png";

        return oss.str();
    }
};

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        std::cerr << "Arguments are lacking.\n\tusage: ./MCLs <width> <height> <outputfile> [color]" << std::endl;
        return -1;
    }

    int line_color[3] = { 0xff, 0xff, 0xff };

    if (argc == 5 && std::strcmp(argv[4], "orange") == 0)
    {
        line_color[1] = 0x66;
        line_color[2] = 0x00;
    }

    try
    {
        ctrl(std::atoi(argv[1]), std::atoi(argv[2]), argv[3], line_color);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}
