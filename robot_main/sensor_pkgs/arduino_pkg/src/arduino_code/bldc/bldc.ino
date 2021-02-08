#include <Servo.h>
#include <ros.h>
#include <life_msgs/Motor.h>
#include <life_msgs/Status.h>
int left_power = 1500;
int right_power = 1500;
Servo left_m,right_m;

ros::NodeHandle  nh;
life_msgs::Status state;
ros::Publisher state_pub("/life/Status/Motor", &state);

void messageCb( const life_msgs::Motor& msg){
    float angle = msg.angle;
    float linear = msg.linear;
    left_power = 1500 - angle/2*459 + linear/2;
    right_power = 1500 + angle/2*459 + linear/2;
    left_m.writeMicroseconds(left_power);
    right_m.writeMicroseconds(right_power);
}

ros::Subscriber<life_msgs::Motor> sub("/life/Motor", &messageCb );

void setup()
{ 
  left_m.attach(9);
  right_m.attach(11);
  left_m.writeMicroseconds(left_power);
  right_m.writeMicroseconds(right_power);
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(state_pub);
  state.good = true;
}

void loop()
{  
  state_pub.publish(&state);
  nh.spinOnce();
  delay(100);
}
