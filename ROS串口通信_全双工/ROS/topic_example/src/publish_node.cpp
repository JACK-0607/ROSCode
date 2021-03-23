
#include "ros/ros.h"
#include "std_msgs/String.h" //use data struct of std_msgs/String  
#include "mbot_linux_serial.h"
#include <sstream>
#include <geometry_msgs/Twist.h>

//test send value
double testSend1=5555.0;
double testSend2=2222.0;
unsigned char testSend3=0x07;

//test receive value
double testRece1=0.0;
double testRece2=0.0;
double testRece3=0.0;
unsigned char testRece4=0x00;

int main(int agrc,char **argv)
{
    ros::init(agrc,argv,"public_node");
    ros::NodeHandle nh;
    ros::Publisher turtle_vel_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    ros::Rate loop_rate(50);
    
    //串口初始化
    serialInit();

    while(ros::ok())
    {
        ros::spinOnce();
        //向STM32端发送数据，前两个为double类型，最后一个为unsigned char类型
       writeSpeed(testSend1,testSend2,testSend3);
       //从STM32接收数据，输入参数依次转化为小车的线速度、角速度、航向角（角度）、预留控制位
      readSpeed(testRece1,testRece2,testRece3,testRece4);
       // 初始化geometry_msgs::Twist类型的消息
      geometry_msgs::Twist vel_msg;
      vel_msg.linear.x = testRece1/15;
      vel_msg.angular.z = ((81-testRece2)-40)/80;

      turtle_vel_pub.publish(vel_msg);
        //打印数据
       ROS_INFO("%f,%f,%f,%d\n",testRece1,testRece2,testRece3,testRece4);

        loop_rate.sleep();
    }
    return 0;
}
 



