#ifndef __CAMERA_H__
#define __CAMERA_H__


#include "./common.h"

class Camera
{
private:
	float m_distance, m_twist, m_elevation, m_azimuth;
	float mx, my, mz;
	
public:
	Camera(float x, float y, float z);
	
	void calc(void);
	void get_pos(float *distance, float *twist, float *elevation, float *azimuth);
	void get_pos2(float *x, float *y, float *z);
};


#endif