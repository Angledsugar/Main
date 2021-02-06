#ifndef _LIFE_PID
#define _LIFE_PID
namespace LIFE{
	class PID{
		public:
			PID(float P = 0,float I = 0,float D = 0);
			~PID();
			float calculate(float now);
			void set_target(float target);
			float init(float max, float min);
		private:
			float _Kp,_Ki,_Kd;
			float _I_gain;
			float _err_pre;
			float _I_gain_max;
			float _target;
			float _min,_max;
	};
};
#endif
