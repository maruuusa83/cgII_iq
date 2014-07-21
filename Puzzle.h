#ifndef __PUZZLE_H__
#define __PUZZLE_H__


#include "./common.h"
#include "./Object.h"
#include "./GL_Utility.h"
#include "./Stage.h"

#include <stdio.h>

#define STATE_STOP			(0)
#define STATE_GET_PUZZLE	(1)
#define STATE_GENERATE		(2)
#define STATE_RUN			(3)
#define STATE_WAIT_NEXT		(4)
#define STATE_DOWN			(5)

#define CUBE_GEN_SPD	(0.01 * (SPEED))
#define CUBE_DOWN_SPD	(CUBE_GEN_SPD * (0.8))
#define CUBE_ROT_DEG	(0.7 * (SPEED))
#define CUBE_WAIT_TIME	((int)(45.0 * (1.0 / (SPEED))))

extern MAT mat_normal_cube;
extern MAT mat_forbidden_cube;
extern MAT mat_advantage_cube;

class PuzzleCube{
private:
	char m_kind;
	char m_state;
	int m_pos_z, m_pos_x;
	float m_pos_y;
	float m_rot;
	
	int m_wait;
	
public:
	PuzzleCube(char kind, int pos_z, int pos_x);
	
	void check_marker(void);
	
	int calc(void);
	void draw(void);
	
	void start_generate(void);
	void start_run(void);
	void start_down(void);
	
	void set_pos_y(float pos_y);
	float get_pos_y(void);
	int get_state(void);
	int get_kind(void);
};

class Puzzle : public Object {
private:
	int m_state;
	
	PuzzleCube* m_puzzle_map[6][10];
	
public:
	Puzzle(void);
	
	void calc(void);
	void draw(void);
	
	void get_puzzle(void);
	void generate(void);
	void run(void);
	
	int check_finish(void);
	
	void set_state_fin(void);
};

#endif