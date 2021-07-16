#include "processing.ih"

void Processing::on_pointcloud(PointCloud2 const &cloud) noexcept
{
    static PointCloud2 transformed;
    vector<uint8_t> image = extract_image(cloud);
    
    if (image.empty()) // couldn't extract image
        return;

    int endian = 1;
    ObjectRecognitionGoal goal;
    goal.image.header = cloud.header;
    goal.image.height = cloud.height;
    goal.image.width = cloud.width;
    goal.image.encoding = "8UC3";
    goal.image.is_bigendian = *reinterpret_cast<char*>(&endian) != 1;
    goal.image.step = goal.image.width * 3;
    goal.image.data = move(image);

    if (!d_object_recognition.waitForServer(Duration(1.0)))
    {
        ROS_INFO("Action server lost, and not back yet...");
        return;
    }
        
    d_object_recognition.sendGoal(goal);
    d_object_recognition.waitForResult();

    if (d_object_recognition.getState() != SimpleClientGoalState::SUCCEEDED)
    {
        ROS_INFO("Failed to get bbox for image, ignoring...");
        return;
    }

    ObjectRecognitionResultConstPtr result = d_object_recognition.getResult();
    if (result->objects.size() * 4 != result->bbox.size())
    {
        ROS_INFO("Bounding boxes and labels dont line up, ignoring...");
        return;
    }

    // transform the received point cloud to the required frame.
    d_tflistener.waitForTransform(d_output_tf_frame, cloud.header.frame_id, Time(0), Duration(1.0));
    pcl_ros::transformPointCloud(d_output_tf_frame, cloud, transformed, d_tflistener);

    // highres extract the boundig box stuff, and color it
    for (size_t idx = 0; idx < result->objects.size(); ++idx)
    {
        // object we dont care, just get a color for now
        Color rgb = next_color(1.0, 1.0);
        int xpos = result->bbox[idx * 4 + 0];
        int ypos = result->bbox[idx * 4 + 1];
        int width = result->bbox[idx * 4 + 2];
        int height = result->bbox[idx * 4 + 3];

        cout << "bbox: RGB[" << int(rgb.red) << ", " << int(rgb.green) << ", " << int(rgb.blue) << "]";
        cout << " BBOX[x: " << xpos << ", y: " << ypos << ", w: " << width << ", h: " << height << "]\n";
        accumulate_highres(transformed, {xpos, ypos, width, height}, rgb);
    }

    // for lowres we convert to PCL so we can use voxelgrid
    PCLPointCloud2::Ptr pcl_cloud = boost::make_shared<PCLPointCloud2>();
    toPCL(transformed, *pcl_cloud);

    VoxelGrid<PCLPointCloud2> voxelgrid;
    voxelgrid.setInputCloud(pcl_cloud);
    voxelgrid.setLeafSize(d_lowres_distance, d_lowres_distance, d_lowres_distance);
    voxelgrid.filter(*pcl_cloud);

    accumulate_lowres(*pcl_cloud);
    publish_state_cloud();
}