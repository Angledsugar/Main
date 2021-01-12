#include <ros.h>
#include <life_msgs/IR.h>
#include <life_msgs/Status.h>
#define IR_NUM 5
#define FILTER_SIZE 10
float IR_data[IR_NUM];
int IR[IR_NUM][FILTER_SIZE];
int IR_index = 0;

ros::NodeHandle  nh;
life_msgs::IR IR_msg;
life_msgs::Status state;
ros::Publisher IRpub("/life/IR", &IR_msg);
ros::Publisher state_pub("/life/Status/IR", &state);

void setup() {
  nh.initNode();
  nh.advertise(IRpub);
  nh.advertise(state_pub);
}

void loop() {
  ReadIR();
  state.good = true;
  state_pub.publish(&state);
  IRpub.publish(&IR_msg);
  nh.spinOnce();
  delay(10);
}
void ReadIR(){
    float mean[IR_NUM] {};
    IR[0][IR_index] = analogRead(A0);
    IR[1][IR_index] = analogRead(A1); 
    IR[2][IR_index] = analogRead(A2); 
    IR[3][IR_index] = analogRead(A3); 
    IR[4][IR_index] = analogRead(A4);  
    IR_index = (IR_index+1)%FILTER_SIZE;
    for(int i=0;i<IR_NUM;i++){
      for(int j=0;j<FILTER_SIZE;j++){
        mean[i] += IR[i][j];  
      }
      mean[i] /= FILTER_SIZE;
      IR_data[i] = IR_data[i]*0.95 + mean[i]*0.05;
    }
    IR_msg.ir1 = IR_data[0];
    IR_msg.ir2 = IR_data[1];
    IR_msg.ir3 = IR_data[2];
    IR_msg.ir4 = IR_data[3];
    IR_msg.ir5 = IR_data[4];
}
