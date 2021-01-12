#include <ros/ros.h>
#include <wiringPi.h>

#include "life_msgs/Status.h"
#define RED 17
#define GREEN 27
#define BLUE 22

void IR(const life_msgs::Status& msg);
void Cam(const life_msgs::Status& msg);
void Imu(const life_msgs::Status& msg);
void Motor(const life_msgs::Status& msg);
void GPS(const life_msgs::Status& msg);


bool IR_ok = false;
bool Cam_ok = false;
bool Imu_ok = false;
bool Motor_ok = false;
bool GPS_ok = false;

int main (int argc, char **argv)
{
    ros::init(argc, argv, "SENSOR_CHECK");
    ros::NodeHandle nh;
    ros::Subscriber sub1 = nh.subscribe("/life/Status/IR", 1 ,IR);
    ros::Subscriber sub2 = nh.subscribe("/life/Status/Cam", 1 ,Cam);
    ros::Subscriber sub3 = nh.subscribe("/life/Status/Imu", 1 ,Imu);
    ros::Subscriber sub4 = nh.subscribe("/life/Status/Motor", 1 ,Motor);
    ros::Subscriber sub5 = nh.subscribe("/life/Status/GPS", 1 ,GPS);
    
    wiringPiSetupGpio();
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);
    
    digitalWrite(RED,LOW);
    digitalWrite(GREEN,HIGH);
    digitalWrite(BLUE,LOW);
    ROS_INFO("STATUS SET UP OK");
    
    while (ros::ok())
    {
    	if(IR_ok & Cam_ok & Imu_ok & Motor_ok & GPS_ok){
    		digitalWrite(RED,LOW);
    		digitalWrite(GREEN,LOW);
    		digitalWrite(BLUE,HIGH);
    		ROS_INFO("ALL SENSOR IS GOOD");	
    	}
    	else{
    		digitalWrite(RED,LOW);
    		digitalWrite(GREEN,HIGH);
    		digitalWrite(BLUE,LOW);
    	}
        ros::Duration(1).sleep();
        ros::spinOnce();
        
    }
    return 0;
}


void IR(const life_msgs::Status& msg){
	IR_ok = msg.good;
	if(!IR_ok){
		ROS_INFO("IR Status ERROR");
	}
	else{
		ROS_INFO("IR Status GOOD");
	}
}

void Cam(const life_msgs::Status& msg){
	Cam_ok = msg.good;
	if(!Cam_ok){
		ROS_INFO("Cam Status ERROR");
	}
	else{
		ROS_INFO("Cam Status GOOD");
	}
}

void Imu(const life_msgs::Status& msg){
	Imu_ok = msg.good;
	if(!Imu_ok){
		ROS_INFO("Imu Status ERROR");
	}
	else{
		ROS_INFO("Imu Status GOOD");
	}
}

void Motor(const life_msgs::Status& msg){
	Motor_ok = msg.good;
	if(!Motor_ok){
		ROS_INFO("Motor Status ERROR");
	}
	else{
		ROS_INFO("Motor Status GOOD");
	}
}

void GPS(const life_msgs::Status& msg){
	GPS_ok = msg.good;
	if(!GPS_ok){
		ROS_INFO("GPS Status ERROR");
	}
	else{
		ROS_INFO("GPS Status GOOD");
	}
}

