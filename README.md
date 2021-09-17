# Pointcloud Processing
Processes pointcloud, dispatching to various other services

## The SSD
This package is supposed to be used with an object detection package. We are working on writing a package that offers a action server which does object recognition with an SSD network. The messages used for communication with this action server are described in the _action/ObjectRecognition.Action_ of this package. To import the action in python use 

```
from pointcloud_processing.msg import ObjectRecognitionAction, ObjectRecognitionGoal, ObjectRecognitionResult
```

A simple program allowing to manually pass bounding boxes is created in scripts/bboxtest.py

## Run instructions
### Simulation
To run the simulation can be started by using the following command:
```
roslaunch simulation sim.launch robot:=tiago
```

* Make a map stuff (Make sure its in the right folder)

Then to run the navigation parts with the created map run
```
roslaunch navigation tiago_nav.launch map:=my_map
```

* Run rviz with config

For convenience there is also a sim_core.launch file which launches the simulation, and navigation stuff. Optionally also rviz when suplied with the rviz:=true parameter. i.e.:
```
roslaunch pointcloud_processing sim_core.launch rviz:=true
```

To manually control the robot you can use keyboard teleop:
```
roslaunch keyboard_teleop keyboard_tiago.launch
```

### Pointcloud processing
To run the pointcloud processing use the pointcloud_processing launch file.

```
roslaunch pointcloud_processing pointcloud_processing.launch
```
The program waits for an bounding box action server before it starts running, a dummy version can be run via python, the bboxtest.py script in the scripts folder.

The config used by the rviz launch file should show the default set topics.

The pointcloud processing program gathers a low resolution point cloud, of the environment. When a bounding box is passed it stores a colored high resolution cloud. This will change into a labelled cloud + graph representation later on (but of course the project isn't finished yet at the moment).