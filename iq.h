#ifndef __IQ_H__
#define __IQ_H__

#include "./common.h"

#include "./Camera.h"
#include "./GL_Utility.h"
#include "./Stage.h"
#include "./Player.h"
#include "./Event.h"
#include "./Puzzle.h"

void init(int argc, char **argv);
void world(void);
void idle(void);

void on_mouse(int button, int state, int x, int y);
void on_key(unsigned char key, int x, int y);
void on_skey(int key, int x, int y);

MAT mat_normal_cube =
	{
		{0.9, 0.9, 0.9, 1.0},
		{0.9, 0.9, 0.9, 1.0},
		{0.8, 0.8, 0.8, 1.0},
		128.0
	};
MAT mat_forbidden_cube =
	{
		{0.1, 0.1, 0.1, 1.0},
		{0.0, 0.0, 0.0, 1.0},
		{0.8, 0.8, 0.8, 1.0},
		128.0
	};
MAT mat_advantage_cube =
	{
		{0.42969, 1.0, 0.21094, 1.0},
		{0.41969, 0.86, 0.20094, 1.0},
		{0.8, 0.8, 0.8, 1.0},
		128.0
	};

#endif