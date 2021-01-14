#ifndef CORE_
#define CORE_
#include "robot_core.h"
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
			void step_set(int n);
	}
	;
}
#endif
