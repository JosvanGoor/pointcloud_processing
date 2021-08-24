#include "processing.ih"

void Processing::voxel_filter(PointCloud<PointXYZRGB>::Ptr const &in, PointCloud<PointXYZRGB> &out, float min_distance) noexcept
{
    VoxelGrid<PointXYZRGB> voxelgrid;
    voxelgrid.setInputCloud(in);
    voxelgrid.setLeafSize(min_distance, min_distance, min_distance);
    voxelgrid.filter(out);
}