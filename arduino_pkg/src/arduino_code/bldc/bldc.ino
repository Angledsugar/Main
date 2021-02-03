#include <Servo.h>
#include <ros.h>
#include <life_msgs/Motor_set.h>

int left_power = 1500;
int right_power = 1500;
Servo left_m,right_m;

ros::NodeHandle  nh;
void messageCb( const life_msgs::Motor_set& msg){
    float l_data = msg.left.speed;
    float r_data = msg.right.speed;
    if(msg.left.dir && l_data > 0){
      left_power = 1541 + 459*l_data/100;  
    }
    else if(l_data > 0){
      left_power = 1460 - 460*l_data/100;  
    }
    else{
      left_power = 1500;
    }
    if(!msg.right.dir && r_data > 0){
      right_power = 1541 + 459*r_data/100;   
    }
    else if(r_data > 0){
      right_power = 1460 - 460*r_data/100;  
    }
    else{
      right_power = 1500;
    }
    left_m.writeMicroseconds(left_power);
    right_m.writeMicroseconds(right_power);
}

ros::Subscriber<life_msgs::Motor_set> sub("/life/Motor", &messageCb );


void setup()
{ 
  nh.initNode();
  nh.subscribe(sub);
  left_m.attach(9);
  right_m.attach(11);
  left_m.writeMicroseconds(1000);
  right_m.writeMicroseconds(right_power);
}

void loop()
{  
  nh.spinOnce();
  delay(1);
}
