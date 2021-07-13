#include "processing.ih"

void Processing::publish_state_cloud() noexcept
{
    d_state_cloud->header.frame_id = d_output_tf_frame;
    pcl_conversions::toPCL(Time::now(), d_state_cloud->header.stamp);
    d_pointcloud_publisher.publish(d_state_cloud);
}