#include "processing.ih"

void Processing::filter_overlap(PointCloud<PointXYZRGB>::Ptr const &cloud, PointCloud<PointXYZRGB>::Ptr const &filter) noexcept
{
    vector<int> indices;
    vector<float> distances;
    search::KdTree<PointXYZRGB> kdtree;
    kdtree.setInputCloud(filter);

    PointIndices::Ptr outliers = boost::make_shared<PointIndices>();
    
    for (int idx = 0; idx < cloud->size(); ++idx)
    {
        if (kdtree.radiusSearch(cloud->at(idx), 0.025f, indices, distances, 1) != 0)
            outliers->indices.push_back(idx);
    }

    ExtractIndices<PointXYZRGB> extraction;
    extraction.setInputCloud(cloud);
    extraction.setIndices(outliers);
    extraction.setNegative(true);
    extraction.filter(*cloud);
}