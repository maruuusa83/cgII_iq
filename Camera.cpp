#include "./Camera.h"

extern Player *player;

Camera::Camera(float x, float y, float z)
{
	mx = x;
	my = y;
	mz = z;
}

void Camera::calc(void)
{
	m_distance = 20;
	m_twist = -5;
	m_elevation = -25;
	m_azimuth = 45;
}

void Camera::get_pos(float *distance, float *twist, float *elevation, float *azimuth)
{
	*distance = m_distance;
	*twist = m_twist;
	*elevation = m_elevation;
	*azimuth = m_azimuth;
}
