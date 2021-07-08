#include "common.h"

#include "processing/processing.h"

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "pointcloud_processing");
    ros::NodeHandle node;

    Processing processing;

    ros::spin();
}