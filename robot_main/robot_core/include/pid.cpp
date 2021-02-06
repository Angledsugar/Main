#include "pid.h"
using namespace LIFE;

PID::PID(float K, float I, float D) : Kp(K) , Ki(I) , Kd (d){};

float PID::calculate(float now){
	float err = target - now;
	float	P_gain = err*Kp;
	_I_gain = (err + err_pre)*Ki;
	float D_gain = (err - err_pre)*Kd;
	if(_I_gain > _I_gain_max)
		_I_gain = _I_gain_max;
	else if(_I_gain > _I_gain_max)
};
