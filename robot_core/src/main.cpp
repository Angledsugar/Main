#include "main_fun.cpp"
#include <iostream>

int main(int argc,char** argv){
	ros::init(argc,argv,"Core");
	ros::NodeHandle nh;
	ros::Subscriber sub1 = nh.subscribe("/life/IR", 1 ,IR_CB);
    ros::Subscriber sub2 = nh.subscribe("/life/Cam", 1 ,Cam_CB);
    ros::Subscriber sub3 = nh.subscribe("/life/Robot_state", 1 ,Imu_CB);
    ros::Publisher motor = nh.advertise<life_msgs::Motor_set>("/life/Motor",1);
    ros::Publisher st_pub = nh.advertise<life_msgs::Motor_set>("/life/Status/Robot",1);
	
    life_msgs::Motor_set Motor_msg;
    life_msgs::Status state;
    
    std::cout<<"ROBOT MAIN IS READY\n";
	while(ros::ok()){
		switch(step){
			case 0:         // robot state is after boot , preparing sensors and do something
				ready_sensor();
				break;
			case 1:  		// robot state is after dropping, robot is on the sea
				find_person();
				break;
		}
		ros::spinOnce();
	}
	return 0;
}


