#ifndef __COMMON_H__
#define __COMMON_H__


#include "./common.h"

class Camera
{
private:
	float x, y, z;
	
public:
	void move_pos(float x, float y, float z, float direction_x, float direction_y, float direction_z);
}


#endif