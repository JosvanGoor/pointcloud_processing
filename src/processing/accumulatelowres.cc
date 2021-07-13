#include "processing.ih"

void Processing::accumulate_lowres(PointCloud2 const &cloud) noexcept
{
    // PointCloud2 filtered;
    // pcl::VoxelGrid filter;
    // filter.setInputCloud(cloud);

    Offsets offsets = get_offsets(cloud.fields);
    if (d_state_cloud->size() == 0)
    {
        PointXYZRGB point;
        point.x = *reinterpret_cast<float const *>(cloud.data.data() + offsets.offset_x);
        point.y = *reinterpret_cast<float const *>(cloud.data.data() + offsets.offset_y);
        point.z = *reinterpret_cast<float const *>(cloud.data.data() + offsets.offset_z);
        point.r = 255;
        point.g = 255;
        point.b = 255;
        d_state_cloud->push_back(point);
    }

    std::vector<int> indices;
    std::vector<float> distances;
    search::KdTree<PointXYZRGB> kdtree;
    kdtree.setInputCloud(d_state_cloud);

    for (size_t row = 0; row < cloud.height; row += 5)
    {
        size_t row_offset = row * cloud.row_step;
        for (size_t col = 0; col < cloud.width; col += 5)
        {
            PointXYZRGB point;
            point.x = *reinterpret_cast<float const *>(cloud.data.data() + (row_offset + col * cloud.point_step + offsets.offset_x));
            point.y = *reinterpret_cast<float const *>(cloud.data.data() + (row_offset + col * cloud.point_step + offsets.offset_y));
            point.z = *reinterpret_cast<float const *>(cloud.data.data() + (row_offset + col * cloud.point_step + offsets.offset_z));
            point.r = 255;
            point.g = 255;
            point.b = 255;

            if (kdtree.radiusSearch(point, d_lowres_distance, indices, distances, 1) == 0)
                d_state_cloud->push_back(point);
        }
    }
}