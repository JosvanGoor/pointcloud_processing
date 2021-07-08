import rospy
import actionlib
import cv2
from cv_bridge import CvBridge
from sensor_msgs.msg import Image
from pointcloud_processing.msg import ObjectRecognitionAction, ObjectRecognitionGoal, ObjectRecognitionResult

client = None

def on_goal(goal):
    try:
        print("goal received!\n")
        
        bridge = CvBridge()
        image = bridge.imgmsg_to_cv2(goal.image, desired_encoding = "passthrough")
        
        cv2.imshow("Image", image)
        cv2.waitKey(1)

        result = ObjectRecognitionResult()
        client.set_succeeded(result)
    except Exception, e:
        print e
        result = ObjectRecognitionResult()
        client.set_succeeded(result)

if __name__ == "__main__":
    rospy.init_node("image_display_actionserver_test")
    client = actionlib.SimpleActionServer("bbox_server", ObjectRecognitionAction, on_goal, False)
    client.start()
    rospy.spin()
