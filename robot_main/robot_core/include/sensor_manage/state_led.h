#ifndef _LIFE_STATE_LED
#define _LIFE_STATE_LED
#include "ros/ros.h"
#include "life_msgs/LED_SET.h"
namespace LIFE{
	class StateLed{
		public:
			const static int RED = 0 ;
			const static int GREEN = 1 ;
			const static int BLUE = 2 ;
			
			StateLed(ros::NodeHandle& nh);
			~StateLed(){};
			void led_set(int color1,int color2);
		private:
			ros::NodeHandle _nh;
			ros::Publisher _state_pub;
			life_msgs::LED_SET _led_msg;
	};
}
#endif
