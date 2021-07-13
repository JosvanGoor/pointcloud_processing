import rospy
import actionlib
import cv2
from cv_bridge import CvBridge
from sensor_msgs.msg import Image
from pointcloud_processing.msg import ObjectRecognitionAction, ObjectRecognitionGoal, ObjectRecognitionResult

client = None
top_x = 0
top_y = 0
bot_x = 0
bot_y = 0
dragging = False
report = False

def on_mouse_event(event, x, y, flags, param):
    global dragging, top_x, top_y, bot_x, bot_y

    if event == cv2.EVENT_LBUTTONDOWN:
        top_x = x
        top_y = y
        dragging = True

    if dragging and event == cv2.EVENT_MOUSEMOVE:
        bot_x = x
        bot_y = y

    if event == cv2.EVENT_LBUTTONUP:
        bot_x = x
        bot_y = y
        dragging = False

def on_goal(goal):
    global report, client, top_x, top_y, bot_x, bot_y

    try:
        print("goal received!\n")
        
        bridge = CvBridge()
        image = bridge.imgmsg_to_cv2(goal.image, desired_encoding = "passthrough")
        
        if not bot_x == 0 and not bot_y == 0:
            cv2.rectangle(image, (top_x, top_y), (bot_x, bot_y), (0, 255, 0), 1)

        cv2.imshow("Image", image)
        key = cv2.waitKey(1)
        
        if key & 0xFF == ord(' '):
            report = True
        if key & 0xFF == ord('c'):
            print("Setting callback")
            cv2.setMouseCallback("Image", on_mouse_event)

        result = ObjectRecognitionResult()
        if report:
            result.bbox = [top_x, top_y, (bot_x - top_x), (bot_y - top_y)]
            result.probabilities = [1.0]
            result.objects = [1]
            report = False

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
