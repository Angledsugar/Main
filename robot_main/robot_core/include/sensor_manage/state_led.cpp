#include "state_led.h"
using namespace LIFE;
StateLed::StateLed(ros::NodeHandle& nh){
	_nh = nh;
	_state_pub = _nh.advertise<life_msgs::LED_SET>("/life/LED",1);
}

void StateLed::led_set(int color1,int color2){
	if(color1 == RED){
		_led_msg.Status.red = false;
		_led_msg.Status.green = true;
		_led_msg.Status.blue = true;
	}
	else if(color1 == GREEN){
		_led_msg.Status.red = true;
		_led_msg.Status.green = false;
		_led_msg.Status.blue = true;
	}
	else if(color1 == BLUE){
		_led_msg.Status.red = true;
		_led_msg.Status.green = true;
		_led_msg.Status.blue = false;
	}
	if(color2 == RED){
		_led_msg.Step.red = false;
		_led_msg.Step.green = true;
		_led_msg.Step.blue = true;
	}
	else if(color2 == GREEN){
		_led_msg.Step.red = true;
		_led_msg.Step.green = false;
		_led_msg.Step.blue = true;
	}
	else if(color2 == BLUE){
		_led_msg.Step.red = true;
		_led_msg.Step.green = true;
		_led_msg.Step.blue = false;
	}
	_state_pub.publish(_led_msg);
}
