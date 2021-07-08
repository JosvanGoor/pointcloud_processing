#include "processing.ih"

Processing::Processing()
:   d_pointcloud_in(get_param<string>("pointcloud_in")),
    d_bbox_service(get_param<string>("bbox_service")),
    d_pointcloud_out(get_param<string>("pointcloud_out")),
    d_output_tf_frame(get_param<string>("output_tf_frame")),
    d_object_recognition(d_bbox_service, true),
    d_lowres_distance(get_param<float>("lowres_distance"))
{
    NodeHandle node;
    d_pointcloud_subscriber = node.subscribe(d_pointcloud_in, 1, &Processing::on_pointcloud, this);
    d_pointcloud_publisher = node.advertise<PointCloud<PointXYZ>>(d_pointcloud_out, 1);

    ROS_INFO("Waiting for object recognition server on topic %s.\n", d_bbox_service.c_str());
    cout << "bbox service: " << d_bbox_service << "\n";
    d_object_recognition.waitForServer();
    // while (!d_object_recognition.waitForServer(Duration(0.1)))
    //     ros::spinOnce();
    ROS_INFO("All Fully setup, running\n");
}