#ifndef CORE_
#define CORE_
#include "robot_core.h"

#include <wiringPi.h>
#define BLUE 22
#define GREEN 27
#define RED 17


#define TURN_ON 0 
#define DROPPED 1
#define MOVE_PERSON 2
#define WAIT_FOR_PERSON_GRAPPING 3
#define WAIT_LIFE_GUARD 4

#ifndef IMU_STATE
	#define IMU_DROPPED 1
	#define IMU_GRAPPED 2
#endif

namespace Life{
	class Core : private Robot{
		public:
			Core();
			~Core();
			void prepare();
			void find_person();
			void go_to_person();
			void person_grap();
			void maintain();
			void clear_step();
			const int get_step();
		private :
			int step_;
			void step_set_(int n);
	}
	;
}
#endif
