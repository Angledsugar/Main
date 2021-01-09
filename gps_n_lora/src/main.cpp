#define LORA   //test for LORA
#define GPS	   //test for GPS
#define RECODE     // GPS Recode

#include "serial_fun.cpp"
#include <iostream>
#include "ros/ros.h"

#ifdef RECODE
#include "std_msgs/String.h"
#endif

using namespace std;


int main(int argc,char **argv){
	ros::init(argc,argv,"GPS_LORA");
	ros::NodeHandle nh;
	#ifdef GPS
		Serial gps("/dev/ttyUSB1",9600);
		string gps_data;
	#endif
	#ifdef LORA
		Serial lora("/dev/ttyUSB0",9600);
	#endif
	#ifdef RECODE
		ros::Publisher pub = nh.advertise<std_msgs::String>("/GPS",1);
		std_msgs::String gps_msg;
	#endif 
    while(ros::ok()){
    	#ifdef GPS
    		gps_data = get_gps(gps);
			if(!gps_data.size()){
				cout<<endl<<"GPS ERROR"<<endl;
			}
			else{
				cout<<"======= DATA ======="<<endl;
				cout<<gps_data<<endl<<endl;
				#ifdef LORA
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
				#endif
			}
		#elif
			cout<<"NO MODULE TEST!!"<<enld;
		#endif
	}
    return 0; // success
}
