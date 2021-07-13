#include "utility.ih"

Color next_color(float saturation, float value) noexcept
{
    static constexpr int step_size = 67;
    static float hue = 0.0f;

    // we assume a HSV color (so we can rotate the H-wheel)
    // then convert it to RGB and return
    float c = saturation * value;
    float x = c * (1 - fabs(fmod(hue / 60.0, 2.0) - 1));
    float m = value - c;
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;

    if (hue > 300.0f)
        r = c, g = 0, b = x;
    else if (hue > 240.0f)
        r = x, g = 0, b = c;
    else if (hue > 180.0f)
        r = 0, g = x, b = c;
    else if (hue > 120.0f)
        r = 0, g = c, b = x;
    else if (hue > 60)
        r = x, g = c, b = 0;
    else
        r = c, g = x, b = 0;

    hue = (int(hue) + step_size) % 360;
    return {
        static_cast<uint8_t>((r + m) * 255),
        static_cast<uint8_t>((g + m) * 255),
        static_cast<uint8_t>((b + m) * 255)
    };
}