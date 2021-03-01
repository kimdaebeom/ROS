#include "ros/ros.h"
#include <ackermann_msgs/AckermannDriveStamped.h>
#include <kuuve_practice/flag.h>

using namespace std;

double max_speed;
double max_steering_angle;
double min_steering_angle;
bool start_param;
double speed;
double steering_angle;
kuuve_practice::flag trigger_msg_;
int trigger=0;
int ex_trigger=0;

void AckermannCallback(const ackermann_msgs::AckermannDriveStamped::ConstPtr &ackermann_msg) {
	speed = ackermann_msg->drive.speed;
	steering_angle = ackermann_msg->drive.steering_angle;
}

int main(int argc, char **argv){
	ros::init(argc, argv, "trigger_node");
	ros::NodeHandle nh;
	ros::NodeHandle private_nh_;
	private_nh_.getParam("/ackermann_control/max_speed",max_speed);
	private_nh_.getParam("/ackermann_control/max_steering_angle",max_steering_angle);
	private_nh_.getParam("/ackermann_control/min_steering_angle",min_steering_angle);
	ros::Publisher trigger_pub_ = nh.advertise<kuuve_practice::flag>("trigger_flag",10);
	ros::Subscriber ackermann_sub_ = nh.subscribe("kuuve_ackermann",10,AckermannCallback);
	int i=0;
	ros::Rate loop_rate(10);
	while (ros::ok()){
		private_nh_.getParam("/ackermann_control/start_param",start_param);	
		if (start_param == true){
			if (i>=200){
				if (ex_trigger == 0){
					trigger = 1;
					if (steering_angle <= min_steering_angle){
						ex_trigger = 1;
					}
				}
				else if (ex_trigger == 1){
					trigger = 2;
					if (steering_angle >= max_steering_angle){
						ex_trigger = 2;
					}
				}
				else{
					trigger = 3;
				}
				trigger_msg_.kuuve_flag = trigger;
			}
			else{
				trigger = 0;
				trigger_msg_.kuuve_flag = trigger;
			}
			trigger_pub_.publish(trigger_msg_);
			++i;
		}
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}








