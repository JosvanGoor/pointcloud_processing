#include <iostream> // should prolly use ROS_INFO
#include <string>
#include <vector>

#include "utility/utility.h"

/***** OpenCV Includes *****/
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

/***** ROS INCLUDES *****/
#include "ros/ros.h"
#include "pcl_ros/point_cloud.h"
#include "pcl_ros/publisher.h"
#include "pcl_ros/transforms.h"
#include "pcl_conversions/pcl_conversions.h"

/***** ACTIONLIB INCLUDES *****/
#include <actionlib/client/simple_action_client.h>
#include "pointcloud_processing/ObjectRecognitionAction.h"
#include "pointcloud_processing/ObjectRecognitionGoal.h"
#include "pointcloud_processing/ObjectRecognitionResult.h"

/***** MSG INCLUDES *****/
#include "geometry_msgs/TransformStamped.h"
#include "sensor_msgs/PointCloud2.h"
#include "sensor_msgs/image_encodings.h"

/***** PCL INCLUDES *****/
#include "pcl-1.9/pcl/conversions.h"
#include "pcl-1.9/pcl/filters/voxel_grid.h"
#include "pcl-1.9/pcl/point_types.h"
#include "pcl-1.9/pcl/search/kdtree.h"

/***** REST *****/
#include "cv_bridge/cv_bridge.h"
#include "image_transport/image_transport.h"
#include "tf/transform_listener.h"
