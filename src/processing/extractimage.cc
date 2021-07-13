#include "processing.ih"

static size_t find_rgb_offset(PointCloud2::_fields_type const &fields) noexcept
{
    for (auto const &field : fields)
    {
        if (field.name == "rgb")
            return field.offset;
    }

    return -1;
}


vector<uint8_t> Processing::extract_image(PointCloud2 const &cloud) const noexcept
{
    if (cloud.height == 1)
    {
        ROS_INFO("Can't extract image from unordered pointcloud, ignoring...\n");
        return {};
    }

    size_t rgb_offset = find_rgb_offset(cloud.fields);
    if (rgb_offset == -1)
    {
        ROS_INFO("Can't find RGB layer in pointcloud, ignoring...\n");
        return {};
    }

    vector<uint8_t> data;
    data.reserve(cloud.height * cloud.width * 3);
    
    for (size_t row = 0; row < cloud.height; ++row)
    {
        size_t row_offset = row * cloud.row_step;
        for (size_t col = 0; col < cloud.width; ++col)
        {
            data.push_back(cloud.data[row_offset + col * cloud.point_step + rgb_offset + 0]);
            data.push_back(cloud.data[row_offset + col * cloud.point_step + rgb_offset + 1]);
            data.push_back(cloud.data[row_offset + col * cloud.point_step + rgb_offset + 2]);
        }
    }

    return data;
}