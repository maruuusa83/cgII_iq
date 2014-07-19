#ifndef __COMMON_H__
#define __COMMON_H__


#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "myShape.h"

/* スピードの調整用 */
#define SPEED (0.8)

#define DISPLAY_WIDTH  (1280)
#define DISPLAY_HEIGHT (960)

#define KEY_ESC 27

#define CUBE_NORMAL		(1)
#define CUBE_FORBIDDEN	(2)
#define CUBE_ADVANTAGE	(3)

#define PI (3.141592653)
#define D2R(deg) (((2.0 * (PI)) / 360.0) * (deg))

#define FALSE (0)
#define TRUE  (1)

/* 各キューブの質感の設定 */
typedef struct _mat
{
	float diffuse[4];
	float specular[4];
	float ambient[4];
	float shininess;
} MAT;

#endif