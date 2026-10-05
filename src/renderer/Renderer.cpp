#include "renderer/Renderer.h"

#include <algorithm>
#include <stdexcept>

namespace
{
std::size_t pixelCount(int width, int height)
{
    if (width <= 0 || height <= 0)
    {
        throw std::invalid_argument("Renderer dimensions must be positive");
    }

    return static_cast<std::size_t>(width) * static_cast<std::size_t>(height);
}
}

Renderer::Renderer(int width, int height)
    : width_(width),
      height_(height),
      pixels_(pixelCount(width, height))
{
}

void Renderer::clear(std::uint8_t red, std::uint8_t green, std::uint8_t blue)
{
    const std::uint32_t color =
        0xFF000000u |
        (static_cast<std::uint32_t>(red) << 16u) |
        (static_cast<std::uint32_t>(green) << 8u) |
        static_cast<std::uint32_t>(blue);

    std::fill(pixels_.begin(), pixels_.end(), color);
}

void Renderer::DrawPixel(int x, int y, std::uint32_t color) {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) {
        return;
    }
    pixels_[y * width_ + x] = color;
}


void Renderer::DrawLine(int x0, int y0, int x1, int y1, uint8_t red, uint8_t green, uint8_t blue) {
    // Bresenham Algorithm
    std::uint32_t color = 0xFF000000u | (static_cast<std::uint32_t>(red) << 16u) | (static_cast<std::uint32_t>(green) << 8u) | static_cast<std::uint32_t>(blue);

        int dx = abs(x1 - x0);
        int dy = abs(y1 - y0);

        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;

        int err = dx - dy;

        while (true)
        {
            setPixel(x0, y0, color);

            if (x0 == x1 && y0 == y1)
            {
                break;
            }

            int e2 = 2 * err;

            if (e2 > -dy)
            {
                err -= dy;
                x0 += sx;
            }

            if (e2 < dx)
            {
                err += dx;
                y0 += sy;
            }
        }
    }
}

int Renderer::width() const
{
    return width_;
}

int Renderer::height() const
{
    return height_;
}

const std::uint32_t* Renderer::pixels() const
{
    return pixels_.data();
}
