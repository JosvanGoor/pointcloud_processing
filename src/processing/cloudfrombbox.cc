#include "processing.ih"

PointCloud<PointXYZRGB>::Ptr Processing::cloud_from_bbox(PointCloud<PointXYZRGB> const &in, int xpos, int ypos, int width, int height) noexcept
{
    PointCloud<PointXYZRGB>::Ptr out = boost::make_shared<PointCloud<PointXYZRGB>>();

    for (size_t col = xpos; col < (xpos + width); ++col)
    {
        for (size_t row = ypos; row < (ypos + height); ++row)
            out->push_back(in.at(col, row));
    }

    return out;
}