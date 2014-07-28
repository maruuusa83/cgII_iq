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
	m_distance = 23;
	m_elevation = -25;
	
	float z, x;
	player->get_pos(&z, &x);
	m_distance = (16.0 - z) * 0.6 + 10;
	m_elevation = -(16.0 - z) * 1.7 - 10;
	m_azimuth = x * 10.0;
	m_twist = x * 1.6;
}

void Camera::get_pos(float *distance, float *twist, float *elevation, float *azimuth)
{
	*distance = m_distance;
	*twist = m_twist;
	*elevation = m_elevation;
	*azimuth = m_azimuth;
}
