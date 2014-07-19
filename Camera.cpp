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
	m_distance = 15;
	m_elevation = -25;
	
	float z, x;
	player->get_pos(&z, &x);
	m_elevation = -(16.0 - z) * 1.2 - 5;
	m_azimuth = x * 10.0;
	m_twist = x * 1.5;
}

void Camera::get_pos(float *distance, float *twist, float *elevation, float *azimuth)
{
	*distance = m_distance;
	*twist = m_twist;
	*elevation = m_elevation;
	*azimuth = m_azimuth;
}
