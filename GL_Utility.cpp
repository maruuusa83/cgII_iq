#include "./GL_Utility.h"

void GL_Utility::polarview(float distance, float twist, float elevation, float azimuth)
{
    glTranslatef( 0.0, 0.0, -distance);
    glRotatef( -twist, 0.0, 0.0, 1.0);
    glRotatef( -elevation, 1.0, 0.0, 0.0);
    glRotatef( -azimuth, 0.0, 1.0, 0.0);
}

void GL_Utility::reshape(int width, int height)
{
	float aspect = (float)width / (float)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, aspect, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
}
