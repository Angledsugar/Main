#include <TimerFive.h>
#include <ros.h>
#include <life_msgs/IR.h>
#include <life_msgs/Status.h>
#define IR_NUM 5
#define FILTER_SIZE 10
float IR_data[2][IR_NUM] {};
int IR[IR_NUM][FILTER_SIZE];
int IR_index = 0;
int IR_pre_index = 0;
int step = 0;
bool flag = false;
ros::NodeHandle  nh;
life_msgs::IR IR_msg;
life_msgs::Status state;
ros::Publisher IRpub("/life/IR", &IR_msg);
ros::Publisher state_pub("/life/Status/IR", &state);

void setup() {
  Timer5.initialize(25000);
  Timer5.attachInterrupt(timer_hander);
  Timer5.start();
  nh.initNode();
  nh.advertise(IRpub);
  nh.advertise(state_pub);
}

void loop() {
  if(flag){
    flag = false;
    switch(step){
        case 0 :
           ReadIR();
           step++;
           break;
        case 1:
           low_pass_filter();
           step++;
           break;
        case 2:
           state.good = true;
           state_pub.publish(&state);
           IRpub.publish(&IR_msg);
           step ++;
           break;
        case 3:
           nh.spinOnce();
           step = 0;
           break;
        default:
           step = 0;
           break;
      
     }
  }
  delay(10);
}
void ReadIR(){
    IR_pre_index = IR_index;
    IR_index = (IR_index+1)%FILTER_SIZE;
    IR[0][IR_index] = analogRead(A0);
    IR[1][IR_index] = analogRead(A1); 
    IR[2][IR_index] = analogRead(A2); 
    IR[3][IR_index] = analogRead(A3); 
    IR[4][IR_index] = analogRead(A4);
    //LOW PASS FILETER
    IR_data[0][0] = 0.7*IR_data[0][0] + 0.3*IR[0][IR_index];
    IR_data[0][1] = 0.7*IR_data[0][1] + 0.3*IR[1][IR_index];
    IR_data[0][2] = 0.7*IR_data[0][2] + 0.3*IR[2][IR_index];
    IR_data[0][3] = 0.7*IR_data[0][3] + 0.3*IR[3][IR_index];
    IR_data[0][4] = 0.7*IR_data[0][4] + 0.3*IR[4][IR_index];
    //HIGH PASS FILTER
    IR_data[1][0] = 0.1*(IR_data[1][0] + IR[0][IR_index] - IR[0][IR_pre_index]);
    IR_data[1][1] = 0.1*(IR_data[1][1] + IR[1][IR_index] - IR[1][IR_pre_index]);
    IR_data[1][2] = 0.1*(IR_data[1][2] + IR[2][IR_index] - IR[2][IR_pre_index]);
    IR_data[1][3] = 0.1*(IR_data[1][3] + IR[3][IR_index] - IR[3][IR_pre_index]);
    IR_data[1][4] = 0.1*(IR_data[1][4] + IR[4][IR_index] - IR[4][IR_pre_index]);
}


void timer_hander(){
  flag = true;
}

void low_pass_filter(){
  IR_msg.ir1 = (IR_data[0][0] - IR_data[1][0])*2;
  IR_msg.ir2 = (IR_data[0][1] - IR_data[1][1])*2;
  IR_msg.ir3 = (IR_data[0][2] - IR_data[1][2])*2;
  IR_msg.ir4 = (IR_data[0][3] - IR_data[1][3])*2;
  IR_msg.ir5 = (IR_data[0][4] - IR_data[1][4])*2;
}
