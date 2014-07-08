#ifndef __CAMERA_H__
#define __CAMERA_H__


#include "./common.h"

class Camera
{
private:
	float mx, my, mz;
	
public:
	Camera(float x, float y, float z);
	
	void get_pos(float *x, float *y, float *z);
};


#endif