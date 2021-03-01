#include <ros/ros.h>
#include <ackermann_msgs/AckermannDriveStamped.h>
using namespace std;
float kuuve_speed = 0;
float kuuve_steering_angle = 0;
bool start_trigger;
void ackermann_Callback(const ackermann_msgs::AckermannDriveStamped::ConstPtr &ackermann_msg){
	kuuve_speed = ackermann_msg->drive.speed;
	kuuve_steering_angle = ackermann_msg->drive.steering_angle;
	if (start_trigger == 1){
		ROS_INFO("current speed is %f", kuuve_speed);
		ROS_INFO("current steering angle is %f", kuuve_steering_angle);
	}
}
int main(int argc, char **argv){
	ros::init(argc, argv, "kuuve_example");
	ros::NodeHandle nh;
	ros::NodeHandle private_nh_;
	private_nh_.getParam("/kuuve_example/start_param",start_trigger);
	ros::Subscriber kuuve_sub = nh.subscribe("kuuve_ackermann",10, ackermann_Callback);
	ros::spin();
	return 0;
}
