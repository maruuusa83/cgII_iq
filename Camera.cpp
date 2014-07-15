#include "./Camera.h"

Camera::Camera(float x, float y, float z)
{
	mx = x;
	my = y;
	mz = z;
}

void Camera::calc(void)
{
	
}

void Camera::get_pos(float *x, float *y, float *z)
{
	*x = mx;
	*y = my;
	*z = mz;
}