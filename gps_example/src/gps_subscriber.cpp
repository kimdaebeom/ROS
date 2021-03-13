#include "ros/ros.h"
#include "std_msgs/Bool.h"//똑같이 메세지파일 추가해준다.

void GpsflagCallback(const std_msgs::Bool::ConstPtr& msg)//Publisher에서도 설명했듯이 subscriber는 callback함수를 통해 정보를 받아온다.
{
ROS_INFO("gps_flag:%d",msg->data);//콜백에서 &로 묶어놓은 메세지에서 데이터에 접근하기 위해 pointer를 이용한다.
}

int main(int argc, char **argv)
{
ros::init(argc, argv, "gps_subscriber");//subscriber 이름 설정

ros::NodeHandle nh;//publisher 와 마찬가지로 노드핸들러를 선언

ros::Subscriber gps_sub = nh.subscribe("gps_flag1", 10, GpsflagCallback);//subscriber도 객체로 선언해주는데, 노드핸들의 subscribe모듈을 이용하며, 뒤에는 토픽명, 버퍼크기, callback함수가 들어간다.
ros::spin();//callback함수가 돌때마다 과정을 반복할 수 있도록, spin을 해준다.

return 0;
}
