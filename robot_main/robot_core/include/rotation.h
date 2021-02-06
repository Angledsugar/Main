#ifndef _LIFE_ROTATION
#define _LIFE_ROTATION
#include <cmath>
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/Vector3.h"
namespace LIFE{
	typedef geometry_msgs::Quaternion Rotate;
	typedef geometry_msgs::Vector3 L_VECTOR;
	L_VECTOR transform(Rotate angle,L_VECTOR vec){
		L_VECTOR result;
		result.x = cos(angle.z)*cos(angle.y)*vec.x + (cos(angle.z)*sin(angle.y)*sin(angle.x) - sin(angle.z)*cos(angle.x))*vec.y + (cos(angle.z)*sin(angle.y)*cos(angle.x) + sin(angle.z)*sin(angle.x))*vec.z;
		
		result.y = sin(angle.z)*cos(angle.y)*vec.x + (sin(angle.z)*sin(angle.y)*sin(angle.x) + cos(angle.z)*cos(angle.x))*vec.y + (sin(angle.z)*sin(angle.y)*cos(angle.x) - cos(angle.z)*sin(angle.x))*vec.z;
		
		result.z = -sin(angle.y)*vec.x + cos(angle.y)*sin(angle.x)*vec.y + cos(angle.y)*cos(angle.x)*vec.z;
		return result;
	}

	L_VECTOR inv_transform(Rotate angle,L_VECTOR vec){
		angle.x = - angle.x;
		angle.y = - angle.y;
		angle.z = - angle.z;
		return transform(angle,vec);
	}
};
#endif
