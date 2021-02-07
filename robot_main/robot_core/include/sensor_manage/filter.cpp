#include "filter.h"

using namespace LIFE;
Filter::Filter(float w) : high_pre(0),low_pre(0),pre_data(0),alpha(w){
};

void Filter::set_cutting_frequency(float w){
	alpha = w;
}

float Filter::low_pass(float new_data){
	float result = alpha*low_pre + (1-alpha)*new_data;
	low_pre = result;
	return result;
};

float Filter::high_pass(float new_data){
	float result = alpha*(high_pre + new_data - pre_data);
	pre_data = new_data;
	high_pre = result;
	return result;
};

void Filter::reset(){
	pre_data = 0;
	high_pre = 0;
	low_pre = 0;
	alpha = 0;
};
