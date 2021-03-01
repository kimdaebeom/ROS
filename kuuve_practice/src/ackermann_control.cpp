#include "ros/ros.h"
#include <ackermann_msgs/AckermannDriveStamped.h>
#include <kuuve_practice/flag.h>

using namespace std;

double max_speed;
double max_steering_angle;
double min_steering_angle;
bool start_param;
double speed=0;
double steering_angle=0;
int cur_trigger_ = 0;
ackermann_msgs::AckermannDriveStamped ackermann_msg_;

void Trigger_Callback(const kuuve_practice::flag::ConstPtr &trigger_msg) {
	cur_trigger_ = trigger_msg->kuuve_flag;
}

int main(int argc, char **argv){
	ros::init(argc, argv, "ackermann_control");
	ros::NodeHandle nh;
	ros::NodeHandle private_nh_;
	private_nh_.getParam("/ackermann_control/max_speed",max_speed);
	private_nh_.getParam("/ackermann_control/max_steering_angle",max_steering_angle);
	private_nh_.getParam("/ackermann_control/min_steering_angle",min_steering_angle);
	ros::Publisher ackermann_pub_= nh.advertise<ackermann_msgs::AckermannDriveStamped>("kuuve_ackermann", 10);
	ros::Rate loop_rate(10);
	ros::Subscriber trigger_sub_ = nh.subscribe("trigger_flag",10,Trigger_Callback);
	while (ros::ok()){
		private_nh_.getParam("/ackermann_control/start_param",start_param);
		if (start_param == true){
			if (cur_trigger_ == 0){
				speed = 30;
				steering_angle = 0;	
			}
			else if(cur_trigger_ ==1){
				speed += 0.1;
				steering_angle -= 0.2;
			}
			else if(cur_trigger_==2){
				speed += 0.3;
				steering_angle += 0.4;
			}
			else{
				speed -= 3;
				steering_angle = 0;
			}
			if (speed >= max_speed){
				speed = max_speed;
			}
			if (steering_angle >= max_steering_angle){
				steering_angle = max_steering_angle;
			}
			else if(steering_angle <= min_steering_angle){
				steering_angle = min_steering_angle;
			}
			ackermann_msg_.drive.speed = speed;
			ackermann_msg_.drive.steering_angle = steering_angle;
			ackermann_pub_.publish(ackermann_msg_);
		}
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}












