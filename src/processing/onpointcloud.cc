#include "processing.ih"

void Processing::on_pointcloud(PointCloud2 const &cloud) noexcept
{
    ROS_INFO("Pointcloud received.\n");
    Mat image = extract_image(cloud);
    
    if (image.empty()) // couldn't extract image
        return;
    
    if (!image.isContinuous())
    {
        ROS_INFO("Image not continuous, which is unexpected.\n");
        return;
    }

    int endian = 1;
    ObjectRecognitionGoal goal;
    goal.image.header = cloud.header;
    goal.image.height = image.size().height;
    goal.image.width = image.size().width;
    goal.image.encoding = "8UC3";
    goal.image.is_bigendian = *reinterpret_cast<char*>(&endian) != 1;
    goal.image.step = goal.image.width * 3;
    goal.image.data.reserve(image.total() * image.channels());
    goal.image.data.insert(goal.image.data.end(), image.data, image.data + (image.total() * image.channels()));
    
    ROS_INFO("Sending goal.\n");
    d_object_recognition.sendGoal(goal);
    ROS_INFO("Waiting for Result.\n");
    d_object_recognition.waitForResult();
    if (d_object_recognition.getState() == SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("Yay it works'd!\n");
    else
        ROS_INFO("FAIL KEKW.\n");
}