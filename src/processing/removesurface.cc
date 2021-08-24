#include "processing.ih"

void Processing::remove_surface(pcl::PointCloud<pcl::PointXYZRGB>::Ptr const &cloud) noexcept
{
    ModelCoefficients coefficients;
    PointIndices::Ptr inliers = boost::make_shared<PointIndices>();
    SACSegmentation<PointXYZRGB> segmentation;

    segmentation.setInputCloud(cloud);
    segmentation.setDistanceThreshold(0.1f); // parameterize?
    segmentation.setMethodType(SAC_RANSAC);
    segmentation.setModelType(SACMODEL_PLANE);
    segmentation.segment(*inliers, coefficients);

    ExtractIndices<PointXYZRGB> extraction;
    extraction.setInputCloud(cloud);
    extraction.setIndices(inliers);
    extraction.setNegative(true);
    extraction.filter(*cloud);
}