#include "../common.h"

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

    public:
        Processing();

        void on_pointcloud(sensor_msgs::PointCloud2 const &cloud) noexcept;

    private:
        cv::Mat extract_image(sensor_msgs::PointCloud2 const &cloud) const noexcept;


};