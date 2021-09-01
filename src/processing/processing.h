#include "../common.h"

#include <vector>

class Processing
{
    // relevant topics
    std::string d_pointcloud_in;
    std::string d_bbox_service;
    std::string d_pointcloud_out;
    std::string d_output_tf_frame;

    // i/o
    tf::TransformListener d_tflistener;
    ros::Subscriber d_pointcloud_subscriber;
    ros::Publisher d_pointcloud_publisher;
    actionlib::SimpleActionClient<pointcloud_processing::ObjectRecognitionAction> d_object_recognition;

    // parameters
    float d_lowres_distance;

    // Storage
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr d_state_cloud;

    public:
        Processing();

        void on_pointcloud(sensor_msgs::PointCloud2 const &cloud) noexcept;

    private:
        void publish_state_cloud() noexcept;
        std::vector<uint8_t> extract_image(sensor_msgs::PointCloud2 const &cloud) const noexcept;

        pcl::PointCloud<pcl::PointXYZRGB>::Ptr isolate_surface(pcl::PointCloud<pcl::PointXYZRGB>::Ptr const &cloud) noexcept;
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_from_bbox(pcl::PointCloud<pcl::PointXYZRGB> const &in, int xpos, int ypos, int width, int height) noexcept;
        void filter_overlap(pcl::PointCloud<pcl::PointXYZRGB>::Ptr const &cloud, pcl::PointCloud<pcl::PointXYZRGB>::Ptr const &filter) noexcept;
        void remove_surface(pcl::PointCloud<pcl::PointXYZRGB>::Ptr const &cloud) noexcept;
        void voxel_filter(pcl::PointCloud<pcl::PointXYZRGB>::Ptr const &in, pcl::PointCloud<pcl::PointXYZRGB> &out, float min_distance) noexcept;
        void accumulate(pcl::PointCloud<pcl::PointXYZRGB> const &cloud, Color const &color, float min_distance) noexcept;
};