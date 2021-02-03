#ifndef _MY_IMU
#define _MY_IMU

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <map>

#include "myahrs_plus.hpp"
#define DEGREE_TO_RADIAN  M_PI /180;
using namespace WithRobot;

static const int BAUDRATE = 115200;

static const char* DIVIDER = "1";  // 100 Hz


void handle_error(const char* error_msg)
{
    fprintf(stderr, "ERROR: %s\n", error_msg);
    exit(1);
}

void wait_for_user_input()
{
    printf("\npress enter key to quit.\n");
    char c = getchar();
    exit(1);
}

class IMU : public iMyAhrsPlus
{
	Platform::Mutex lock;
    SensorData sensor_data;
	struct Rotated_accel
	{
		float r_ax;
		float r_ay;
		float r_az;
	};

	public:
		IMU(std::string port="", unsigned int baudrate=115200);
    	~IMU();
    	Quaternion q;
    	EulerAngle e;
    	ImuData<float> imu;
    	Rotated_accel rotated;
	    bool initialize();
	    inline void get_data(SensorData& data);
	    inline SensorData get_data();
	    void operate_data(int sensor_id);
    protected:
    	void OnSensorData(int sensor_id, SensorData data);
    	void OnAttributeChange(int sensor_id, std::string attribute_name, std::string value);

};
#endif