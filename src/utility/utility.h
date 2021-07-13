#ifndef POINTCLOUD_POC_UTILITY_H
#define POINTCLOUD_POC_UTILITY_H

#include <iomanip>
#include "ros/ros.h"
#include <ostream>
#include <tuple>

#include "sensor_msgs/PointCloud2.h"

struct Rectangle
{
    int x;
    int y;
    int width;
    int height;
};

struct Color
{
    uint8_t red;
    uint8_t blue;
    uint8_t green;
};

struct Offsets
{
    size_t offset_x;
    size_t offset_y;
    size_t offset_z;
};

template <typename Type>
Type get_param(std::string const &key);

std::ostream &operator<<(std::ostream &out, sensor_msgs::PointCloud2 const &pc) noexcept;

Color next_color(float saturation, float value) noexcept;

#include "getparam.f"

#endif