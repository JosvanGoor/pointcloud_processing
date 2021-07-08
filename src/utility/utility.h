#ifndef POINTCLOUD_POC_UTILITY_H
#define POINTCLOUD_POC_UTILITY_H

#include <iomanip>
#include <ostream>

#include "ros/ros.h"
#include "sensor_msgs/PointCloud2.h"

template <typename Type>
Type get_param(std::string const &key);

std::ostream &operator<<(std::ostream &out, sensor_msgs::PointCloud2 const &pc) noexcept;

#include "getparam.f"

#endif