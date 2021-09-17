# pointcloud_processing
Processes pointcloud, dispatching to various other services

## The SSD
This package is supposed to be used with an object detection package. We are working on writing a package that offers a action server which does object recognition with an SSD network. The messages used for communication with this action server are described in the _action/ObjectRecognition.Action_ of this package. To import the action in python use 

```
`from pointcloud_processing.msg import ObjectRecognitionAction, ObjectRecognitionGoal, ObjectRecognitionResult`
```

A simple program allowing to manually pass bounding boxes is created in scripts/bboxtest.py

## Run instructions
To run the simulation can be started by using the following command:
```
roslaunch simulation sim.launch robot:=tiago
```

* Make a map stuff (Make sure its in the right folder)

Then to run the navigation parts with the created map run
```
roslaunch navigation tiago_nav.launch map:=my_map
```

## Action Message Structure
