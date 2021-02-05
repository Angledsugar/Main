#include "imu.h"

IMU::IMU(std::string port, unsigned int baudrate) : iMyAhrsPlus(port, baudrate) {

};

IMU::~IMU(){};

bool IMU::initialize() {
        bool ok = false;
        do {
            if(start() == false) break;
            if(cmd_binary_data_format("QUATERNION, IMU") == false) break;
            if(cmd_divider(DIVIDER) == false) break;
            if(cmd_mode("BC") == false) break;
            ok = true;
        } while(0);

        return ok;
}

inline void IMU::get_data(SensorData& data) {
    LockGuard _l(lock);
    data = sensor_data;
}

inline SensorData IMU::get_data() {
    LockGuard _l(lock);
    return sensor_data;
}

void IMU::operate_data(int sensor_id) {
    q = sensor_data.quaternion;
    e = sensor_data.euler_angle;
    imu = sensor_data.imu;
    e.roll  *= -DEGREE_TO_RADIAN;
    e.pitch *= -DEGREE_TO_RADIAN;
    e.yaw   *= -DEGREE_TO_RADIAN;
}

void IMU::OnSensorData(int sensor_id, SensorData data) {
    {
        LockGuard _l(lock);
        sensor_data = data;
        sensor_data.euler_angle = sensor_data.quaternion.to_euler_angle();
    }
    operate_data(sensor_id);
}

void IMU::OnAttributeChange(int sensor_id, std::string attribute_name, std::string value) {
    printf("OnAttributeChange(id %d, %s, %s)\n", sensor_id, attribute_name.c_str(), value.c_str());
}
