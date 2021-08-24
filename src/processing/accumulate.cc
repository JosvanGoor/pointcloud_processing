#include "processing.ih"

void Processing::accumulate(PointCloud<PointXYZRGB> const &cloud, Color const &color, float min_distance) noexcept
{
    // If the state cloud is empty we just adopt the entire cloud
    // under the assumption that is has been appropriately voxelized.
    if (d_state_cloud->empty())
    {
        d_state_cloud->reserve(cloud.size());
        for (PointXYZRGB const &point : cloud)
        {
            PointXYZRGB recolored;
            recolored.x = point.x;
            recolored.y = point.y;
            recolored.z = point.z;
            recolored.r = color.red;
            recolored.g = color.green;
            recolored.b = color.blue;
            d_state_cloud->push_back(recolored);
        }
    }

    vector<int> indices;
    vector<float> distances;
    search::KdTree<PointXYZRGB> kdtree;
    kdtree.setInputCloud(d_state_cloud);

    for (PointXYZRGB const &point : cloud)
    {
        if (kdtree.radiusSearch(point, min_distance, indices, distances, 1) == 0)
        {
            PointXYZRGB recolored;
            recolored.x = point.x;
            recolored.y = point.y;
            recolored.z = point.z;
            recolored.r = color.red;
            recolored.g = color.green;
            recolored.b = color.blue;
            d_state_cloud->push_back(recolored);
        }
    }
}