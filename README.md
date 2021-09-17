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

To manually control the robot you can use keyboard teleop:
```
roslaunch keyboard_teleop keyboard_tiago.launch
```

### Making a map
To make a map run the gmapping slam tool with
```
rosrun gmapping slam_gmapping scan:=scan_raw
```
Then rotate tiago with the keyboard teleop tool untill it creates a complete map of its surroundings (you can verify this by looking at the /map topic in rviz).

Then to store the map use the following command in a new terminal.  
note: this map gets stored in the current terminals location, the launch files we use assume the map is found in the navigation package under maps (i.e. `$(find navigation)/maps/my_map`).
```
rosrun map_server map_saver -f my_map
```

Then to run the navigation parts with the created map run
```
roslaunch navigation tiago_nav.launch map:=my_map
```

You can change my_map to a name of your choice when creating the map, then use that other name in places where my_map is used here.

### sim_core.launch
For convenience there is also a sim_core.launch file which launches the simulation, and navigation stuff.
```
roslaunch pointcloud_processing sim_core.launch
```
* A custom map name can be used by adding the `map:=my_map` argument.
* The launch file can instead be used for mapping by using the `mapping:=true` argument.
* Rviz can be ran using a basic default topic setup by adding the `rviz:=true` argument.

### Pointcloud processing
To run the pointcloud processing use the pointcloud_processing launch file.

```
roslaunch pointcloud_processing pointcloud_processing.launch
```
The program waits for an bounding box action server before it starts running, a dummy version can be run via python, the bboxtest.py script in the scripts folder.

The pointcloud processing program gathers a low resolution point cloud, of the environment. When a bounding box is passed it stores a colored high resolution cloud. This will change into a labelled cloud + graph representation later on (but of course the project isn't finished yet at the moment).

## Plans for the final program
Tiago can drive around (either manually or autonomously) and map objects within a room. These objects will be registered in a scene graph like structure. 

The object detection will be done in realtime by a SSD running on an action server.

Currently we are looking into a way to remove surfaces under detected objects, but this would be an extention.

In the final product we are planning to include some simple behaviours which can be asked to grasp known items (this would most likely be an adapted version of the behaviours written for Robotics for AI).
