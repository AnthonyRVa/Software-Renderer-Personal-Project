#pragma once

#include <cstdint>
#include <vector>

class Renderer
{
public:
    Renderer(int width, int height);

    void clear(std::uint8_t red, std::uint8_t green, std::uint8_t blue);

    [[nodiscard]] int width() const;
    [[nodiscard]] int height() const;
    [[nodiscard]] const std::uint32_t* pixels() const;

    void DrawPixel(int x, int y, std::uint32_t color);

    void DrawLine(int x0, int y0, int x1, int y1, uint8_t red, uint8_t green, uint8_t blue);

private:
    int width_;
    int height_;
    std::vector<std::uint32_t> pixels_;
};
