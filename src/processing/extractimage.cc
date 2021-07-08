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


Mat Processing::extract_image(PointCloud2 const &cloud) const noexcept
{
    if (cloud.height == 1)
    {
        ROS_INFO("Can't extract image from unordered pointcloud, ignoring...\n");
        return Mat{};
    }

    size_t rgb_offset = find_rgb_offset(cloud.fields);
    if (rgb_offset == -1)
    {
        ROS_INFO("Can't find RGB layer in pointcloud, ignoring...\n");
        return Mat{};
    }

    Mat image = Mat(cloud.height, cloud.width, CV_8UC3, Scalar::all(0));

    for (size_t row = 0; row < cloud.height; ++row)
    {
        size_t row_offset = row * cloud.row_step;
        for (size_t col = 0; col < cloud.width; ++col)
        {
            uint8_t *pixel = &image.at<uint8_t>(static_cast<int>(row), static_cast<int>(col), 0);
            pixel[0] = cloud.data[row_offset + col * cloud.point_step + rgb_offset + 0];
            pixel[1] = cloud.data[row_offset + col * cloud.point_step + rgb_offset + 1];
            pixel[2] = cloud.data[row_offset + col * cloud.point_step + rgb_offset + 2];
        }
    }

    return image;
}