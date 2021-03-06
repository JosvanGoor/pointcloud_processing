cmake_minimum_required(VERSION 3.0.2)
project(pointcloud_processing)

add_compile_options(-std=c++11 -march=native)

find_package(catkin REQUIRED COMPONENTS
    message_generation
    genmsg
    actionlib
    actionlib_msgs
    cv_bridge
    image_transport
    pcl_ros
    roscpp
    std_msgs
    sensor_msgs
    tf
)

find_package(PCL 1.9 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_action_files(
    FILES
    ObjectRecognition.action
)

generate_messages(
    DEPENDENCIES
    actionlib_msgs
    sensor_msgs
    std_msgs
)

catkin_package()

set(SOURCE_CODE
    src/main.cc
    src/processing/accumulate.cc
    src/processing/cloudfrombbox.cc
    src/processing/extractimage.cc
    src/processing/filteroverlap.cc
    src/processing/isolatesurface.cc
    src/processing/processing.cc
    src/processing/onpointcloud.cc
    src/processing/publishstatecloud.cc
    src/processing/removesurface.cc
    src/processing/voxelfilter.cc
    src/utility/nextcolor.cc
    src/utility/output.cc
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_node ${SOURCE_CODE})

target_link_libraries(${PROJECT_NAME}_node
   ${catkin_LIBRARIES}
)

add_dependencies(${PROJECT_NAME}_node pointcloud_processing_generate_messages_cpp)