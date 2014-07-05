#ifndef __GL_UTILITY_H__
#define __GL_UTILITY_H__

#include "./common.h"

class GL_Utility
{
public:
	static void polarview(float distance, float twist, float elevation, float azimuth);
	static void reshape(int width, int height);
};

#endif