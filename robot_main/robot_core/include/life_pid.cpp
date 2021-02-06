#include "life_pid.h"
using namespace LIFE;

PID::PID(float P, float I, float D) : _Kp(P) , _Ki(I) , _Kd(D){
	_target = 0;
};
PID::~PID(){};
float PID::calculate(float now){
	float _err = _target - now;
	float	_P_gain = _err*_Kp;
	_I_gain = (_err + _err_pre)*_Ki;
	float _D_gain = (_err - _err_pre)*_Kd;
	if(_I_gain > _I_gain_max)
		_I_gain = _I_gain_max;
	else if(_I_gain < -_I_gain_max)
		_I_gain = -_I_gain_max;
	_err_pre = _err;
	return _P_gain+_I_gain+_D_gain;
};

void PID::set_target(float target){
	_target = target;
	_I_gain_max = (_max - _min)*0.1 + target*_Kp;
}

void PID::init(float max, float min){
	_min = min;
	_max = max;
}
