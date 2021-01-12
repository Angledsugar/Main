#include <Servo.h>
#include <ros.h>
#include <life_msgs/Motor_set.h>

int left_power = 1500;
int right_power = 1500;
Servo left_m,right_m;

ros::NodeHandle  nh;
void messageCb( const life_msgs::Motor_set& msg){
    float l_data = msg.left.speed.data;
    float r_data = msg.right.speed.data;
    if(msg.left.dir.data){
      left_power = 1500 + 500*l_data/100;  
    }
    else{
      left_power = 1500 - 500*l_data/100;  
    }
    if(msg.right.dir.data){
      right_power = 1500 + 500*r_data/100;   
    }
    else{
      right_power = 1500 - 500*r_data/100;  
    }
    left_m.writeMicroseconds(left_power);
    right_m.writeMicroseconds(right_power);
}

ros::Subscriber<life_msgs::Motor_set> sub("/life/motor", &messageCb );


void setup()
{ 
  nh.initNode();
  nh.subscribe(sub);
  left_m.attach(9);
  right_m.attach(11);
  left_m.writeMicroseconds(left_power);
  right_m.writeMicroseconds(right_power);
}

void loop()
{  
  nh.spinOnce();
  delay(1);
}
