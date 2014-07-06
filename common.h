#ifndef __COMMON_H__
#define __COMMON_H__


#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "myShape.h"

#define DISPLAY_WIDTH  (1280)
#define DISPLAY_HEIGHT (960)

#define KEY_ESC 27


/* 各キューブの質感の設定 */
typedef struct _mat
{
	float diffuse[4];
	float specular[4];
	float ambient[4];
	float shininess;
} MAT;

#endif