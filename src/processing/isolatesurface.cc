#include "processing.ih"

PointCloud<PointXYZRGB>::Ptr Processing::isolate_surface(pcl::PointCloud<pcl::PointXYZRGB>::Ptr const &cloud) noexcept
{
    PointCloud<PointXYZRGB>::Ptr rval = boost::make_shared<PointCloud<PointXYZRGB>>();
    ModelCoefficients coefficients;
    PointIndices::Ptr inliers = boost::make_shared<PointIndices>();
    SACSegmentation<PointXYZRGB> segmentation;

    segmentation.setInputCloud(cloud);
    segmentation.setDistanceThreshold(0.01f); // parameterize?
    segmentation.setMethodType(SAC_RANSAC);
    segmentation.setModelType(SACMODEL_PLANE);
    segmentation.segment(*inliers, coefficients);

    ExtractIndices<PointXYZRGB> extraction;
    extraction.setInputCloud(cloud);
    extraction.setIndices(inliers);
    extraction.filter(*rval);

    return rval;
}