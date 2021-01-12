#define LORA   //test for LORA
#define GPS	   //test for GPS
#define RECODE     // GPS Recode

#include "serial_fun.cpp"
#include <iostream>
#include "ros/ros.h"
#include "life_msgs/Status.h"

#ifdef RECODE
#include "std_msgs/String.h"
#endif

using namespace std;


int main(int argc,char **argv){
	ros::init(argc,argv,"GPS_LORA");
	ros::NodeHandle nh;
	ros::Publisher state_pub = nh.advertise<life_msgs::Status>("/life/Status/GPS",1);
	life_msgs::Status state_msg; 
	#ifdef GPS
		Serial gps("/dev/ttyUSB1",9600);
		string gps_data;
		if(!gps.good){
			ROS_INFO("GPS ERROR");
			state_msg.good = false;
		}
	#endif
	#ifdef LORA
		Serial lora("/dev/ttyUSB0",9600);
		if(!lora.good){
			ROS_INFO("LORA ERROR");
			state_msg.good = false;
		}
	#endif
	#ifdef RECODE
		ros::Publisher pub = nh.advertise<std_msgs::String>("/GPS",1);
		std_msgs::String gps_msg;
	#endif
	ROS_INFO("START NODE");
    while(ros::ok()){
    	#ifdef GPS
				if(gps.good){
					gps_data = get_gps(gps);
					if(!gps_data.size()){
						cout<<endl<<"GPS ERROR"<<endl;
						state_msg.good = false;
					}
					else{
						cout<<"======= DATA ======="<<endl;
						cout<<gps_data<<endl<<endl;
						state_msg.good = true;
						#ifdef LORA
							if(lora.good){
								if(gps_data.substr(1,5) == "GNRMC"){
									if(lora.swrite(gps_data.c_str(),gps_data.size())<0)
										cout<<"LoRa write Error!!"<<endl;
									else{
										cout<<"Write to LoRa"<<endl;
										sleep(2);
									}
								#ifdef RECODE
									gps_msg.data = gps_data;
									pub.publish(gps_msg);
								#endif
								}
							}
						#endif
					}
				}
		#elif
			cout<<"NO MODULE TEST!!"<<enld;
		#endif
		state_pub.publish(state_msg);
	}
    return 0; // success
}
