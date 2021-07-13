#include "processing.ih"

void Processing::accumulate_highres(PointCloud2 const &cloud, Rectangle const &rect, Color const &color) noexcept
{
    Offsets offsets = get_offsets(cloud.fields);

    for (size_t row = rect.y; row < (rect.y + rect.height); ++row)
    {
        size_t row_offset = row * cloud.row_step;
        for (size_t col = rect.x; col < (rect.x + rect.width); ++col)
        {
            PointXYZRGB point;
            point.x = *reinterpret_cast<float const *>(cloud.data.data() + (row_offset + col * cloud.point_step + offsets.offset_x));
            point.y = *reinterpret_cast<float const *>(cloud.data.data() + (row_offset + col * cloud.point_step + offsets.offset_y));
            point.z = *reinterpret_cast<float const *>(cloud.data.data() + (row_offset + col * cloud.point_step + offsets.offset_z));
            point.r = color.red;
            point.g = color.green;
            point.b = color.blue;

            d_state_cloud->push_back(point);
        }
    }
}