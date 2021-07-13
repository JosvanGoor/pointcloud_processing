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
        std::vector<uint8_t> extract_image(sensor_msgs::PointCloud2 const &cloud) const noexcept;
        void accumulate_highres(sensor_msgs::PointCloud2 const &fullcloud, Rectangle const &rect, Color const &color) noexcept;
        void accumulate_lowres(sensor_msgs::PointCloud2 const &fullcloud) noexcept;
        void publish_state_cloud() noexcept;
};