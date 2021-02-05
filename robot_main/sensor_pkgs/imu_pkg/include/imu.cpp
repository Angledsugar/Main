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
    e.roll  *= DEGREE_TO_RADIAN;
    e.pitch *= DEGREE_TO_RADIAN;
    e.yaw   *= DEGREE_TO_RADIAN;
    rotated.r_ax = cos(e.pitch)*imu.ax + sin(e.pitch)*sin(e.roll)*imu.ay + sin(e.pitch)*cos(e.roll)*imu.az;
    rotated.r_ay = cos(e.roll)*imu.ay - sin(e.roll)*imu.az;
    rotated.r_az = -sin(e.pitch)*imu.ax + cos(e.pitch)*sin(e.roll)*imu.ay + cos(e.pitch)*cos(e.roll)*imu.az+1;
    /*printf("Rotated=%.4f,%.4f,%.4f, Angle(rpy)=%.1f, %.1f, %.1f, Accel(xyz)=%.4f,%.4f,%.4f, Gyro(xyz)=%.4f,%.4f,%.4f, Magnet(xyz)=%.2f,%.2f,%.2f\n",
            rotated.r_ax,rotated.r_ay, rotated.r_az,
            e.roll, e.pitch, e.yaw,
            imu.ax, imu.ay, imu.az,
            imu.gx, imu.gy, imu.gz,
            imu.mx, imu.my, imu.mz);*/
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