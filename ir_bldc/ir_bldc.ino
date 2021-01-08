#include <Servo.h>
#include <ros.h>
#include <life_msgs/IR.h>
#include <life_msgs/Motor_set.h>
#define IR_NUM 3
#define FILTER_SIZE 10
int left_power = 1500;
int right_power = 1500;
float IR_data[IR_NUM];
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
life_msgs::IR IR_msg;
ros::Subscriber<life_msgs::Motor_set> sub("/life/motor", &messageCb );
ros::Publisher IRpub("/life/IR", &IR_msg);

void setup()
{ 
  nh.initNode();
  nh.advertise(IRpub);
  nh.subscribe(sub);
  left_m.attach(9);
  right_m.attach(11);
  left_m.writeMicroseconds(left_power);
  right_m.writeMicroseconds(right_power);
}

void loop()
{  
  ReadIR();
  IRpub.publish(&IR_msg);
  nh.spinOnce();
  delay(10);
}


void ReadIR(){
    static int IR[IR_NUM][FILTER_SIZE];
    static int IR_index = 0;
    float mean[IR_NUM] {};
    IR[0][IR_index] = analogRead(A0);
    IR[1][IR_index] = analogRead(A1);  
    IR_index = (IR_index+1)%FILTER_SIZE;
    for(int i=0;i<IR_NUM;i++){
      for(int j=0;j<FILTER_SIZE;j++){
        mean[i] += IR[i][j];  
      }
      mean[i] /= FILTER_SIZE;
      IR_data[i] = IR_data[i]*0.95 + mean[i]*0.05;
    }
    IR_msg.ir1.data = IR_data[0];
    IR_msg.ir2.data = IR_data[1];
    IR_msg.ir3.data = IR_data[2];
}
