#ifndef _LIFE_FILTER
#define _LIFE_FILTER
namespace LIFE{
	class Filter{
		public:
			Filter(float w = 0);
			~Filter() {};
			void set_cutting_frequency(float w);
			float low_pass(float new_data);
			float high_pass(float new_data);
			void reset();
		private:
			float pre_data;
			float high_pre;
			float low_pre;
			float alpha;
	};
};
#endif
