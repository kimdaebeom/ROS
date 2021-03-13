#include "ros/ros.h"
#include "std_msgs/Bool.h"//사용할 메세지를 추가해줘야한다.

  int main(int argc, char **argv)
  {

    ros::init(argc, argv, "gps_publisher");//노드명을 적어준다.

    ros::NodeHandle nh;//노드핸들은 마스터를 통해 통신을 담당하는 역할을 하며, publisher혹은 subscriber는 nh를 통해 통신을 한다.(class로 구현되어있어 객체 선언)

    ros::Publisher gps_pub = nh.advertise<std_msgs::Bool>("gps_flag1", 10);//퍼블리셔의 경우, 노드핸들 내부 모듈 advertise를 이용하며, 뒤에는 메세지형식을 <>에 넣어주고, 토픽의 이름과 버퍼의 크기를 설정한다.
  
    ros::Rate loop_rate(10);// loop_rate도 마찬가지로, ros내부에 구현된 Rate의 객체로 생성하며, 생성자에서 10을 넣어주면, Hz를 10으로 맞춰준다.
  
    int count = 0;
    while (ros::ok())
    {
	std_msgs::Bool msg;//우리가 토픽에 담아주기위한 메세지를 정의한다. 메세지는 위의 11번째 줄에서 정의한 메세지 형식을 따라야 한다.

	msg.data=false;		//std_msgs의 각각을 보면, 대부분 .data로 접근할 수 있다. 우리가사용하는 ackerman_msgs를 확인해보자.
	
	if (count>=200){
		msg.data=true;
	}

      	gps_pub.publish(msg);//11째 줄에서 선언해좋은 퍼블리셔 gps_pub은 ros의 Publisher클래스의 내부함수 publish를 통해 토픽을 전송한다.
  
      	ros::spinOnce();//와일문을 다시 반복하라는 의미 이며, publisher에서는 while과 함께 사용해서 spinOnce()를 이용하지만, subscriber에서는 callback()함수가 돌때마다 과정을 반복하도록 spin()함수를 이용한다.
  
      	loop_rate.sleep();//13째 줄에서 정해놓은 것처럼 0.1초동안 슬립하게한다.(이는 전체프로그램의 정지를 의미하며,프로그램실행속도는 매우 빠르기 때문에 loop_late를 이용해 토픽의 주기를 결정해줄 수 있음을 알 수 있다.
      	++count;
    }
  
  
    return 0;
  }
