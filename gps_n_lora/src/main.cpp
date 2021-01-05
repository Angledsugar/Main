#include "serial_fun.cpp"
#include <iostream>
#include "ros/ros.h"

using namespace std;

int main(int argc,char **argv){
	ros::init(argc,argv,"GPS_LORA");
	ros::NodeHandle nh;
	Serial gps("/dev/ttyUSB0",9600);
	Serial lora("/dev/ttyUSB1",9600);
	string gps_data;
    while(ros::ok()){
    	gps_data = get_gps(gps);
    	if(!gps_data.size()){
    		cout<<endl<<"GPS ERROR"<<endl;
    	}
    	else{
			cout<<"======= DATA ======="<<endl;
			cout<<gps_data<<endl<<endl;
			if(lora.swrite(gps_data.c_str(),gps_data.size())<0)
				cout<<"LoRa write Error!!"<<endl;
			else{
				cout<<"Write to LoRa"<<endl;
				sleep(2);
			}
    	}
	}
    return 0; // success
}
