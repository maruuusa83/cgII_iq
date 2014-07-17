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

void Camera::get_pos(float *distance, float *twist, float *elevation, float *azimuth)
{
	*distance = m_distance;
	*twist = m_twist;
	*elevation = m_elevation;
	*azimuth = m_azimuth;
}
