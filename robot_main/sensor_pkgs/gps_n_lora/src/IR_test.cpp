#include <iostream>
#include "ros/ros.h"
#include "serial.cpp"

using namespace std;

int main(int argc,char** argv){
	ros::init(argc,argv,"TEST_NODE");
	ros::NodeHandle nh;
	Serial lidar("/dev/ttyUSB0",115200);
	char buf[9] {};
	int index = 0;
	unsigned int dist = 0;
	bool header = false;
	memset(buf,100,0);
	while(ros::ok()){
		if(lidar.sread(buf + index,sizeof(char))){
			if(!header){
				if(buf[index] == 0x59){
					index++;
				}
				if(index==2)
					header=true;
			}
			else{
				index++;
				if(index==9){
					header=false;
					char check_sum = 0;
					for(int i=0;i<8;i++)
						check_sum+= buf[i];
					if(check_sum == buf[8]){
						dist = (unsigned int)0|buf[2] + (unsigned int)0|(buf[3]<<8);
					}
					if(dist<700){
						for(int i=0;i<9;i++)
							cout<<(int)buf[i]<<" ";
						cout<<endl;
						cout<<"CHECK SUM : "<<(int)check_sum<<endl;
						
						cout<<"DIST : "<<dist<<endl;
					}
					memset(buf,100,0);
					index = 0;
				}
			}
		}
		else{
			cerr<<"SERIAL READ ERROR!!"<<endl;
			return -1;
		}
	}
	return 0;
}