#include "../include/diag.hpp"
#include "../include/drawer.hpp"

#include <random>
#include <ranges>
#include <filesystem>
#include <format>

class ctrl
{
    static constexpr int n_points = 4;
    static constexpr char DST_DIR[] = "./dst/";

    diag_calc m_dc;
    line_drawer m_ld;

public:
    ctrl(int x, int y, const cv::String& fpath, int color[3], bool does_flip) : m_dc(x, y), m_ld()
    {
        auto [w, h] = m_dc.calc_size();
        cv::Point mat_size(std::ceil(w), std::ceil(h));

        cv::Scalar line_color(color[2], color[1], color[0], 0xff);

        auto points = m_dc.generate_points();

        for (int i = 0; i < points.size(); i++)
        {
            cv::String filename = generate_filename(fpath, i, m_dc.get_size(), mat_size, y / static_cast<float>(x));

            m_ld.draw_poly(mat_size, points[i], line_color, does_flip);
            m_ld.save(filename);
        }
    }

    static cv::String generate_random_text()
    {
        constexpr int BASE = 36;
        constexpr char DIGITS[] = "0123456789abcdefghijklmnopqrstuvwxyz";

        std::random_device rd;
        std::mt19937_64 mt(rd());
        auto random_num = mt();
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

    static cv::String generate_filename(const cv::String& name, int index, int srcsize, const cv::Size& dstsize, float slope)
    {
        namespace fs = std::filesystem;

        float width_scale = dstsize.width / static_cast<float>(srcsize);
        float height_scale = dstsize.height / static_cast<float>(srcsize);

        std::string str_slope = std::format("{:2f}", slope);
        str_slope.replace(str_slope.find('.'), 1, "o");

        std::string dststr = std::format(
            "{}&{}&{}{}&{}_{}.png",
            height_scale, width_scale,
            str_slope, generate_random_text(),
            name, index
        );

        fs::path dir = fs::weakly_canonical(fs::path(DST_DIR) / name);
        fs::create_directories(dir);

        return dir /= dststr;
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
    bool does_flip = false;

    if (argc == 5 && std::strcmp(argv[4], "orange") == 0)
    {
        line_color[1] = 0x66;
        line_color[2] = 0x00;
    }

    if (argc == 5)
    {
        if (std::strchr(argv[4], 'o'))
        {
            line_color[1] = 0x66;
            line_color[2] = 0x00;
        }

        if (std::strchr(argv[4], 'r'))
        {
            does_flip = true;
        }
    }

    try
    {
        ctrl(std::atoi(argv[1]), std::atoi(argv[2]), argv[3], line_color, does_flip);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}
