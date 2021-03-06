#ifndef __STAGE_H__
#define __STAGE_H__


#include "./common.h"
#include "./Object.h"

#include <stdio.h>

#define NO_MARKER		(0)
#define MARKER_BLUE		(1)
#define MARKER_RED		(2)
#define MARKER_GREEN	(3)

#define STAGE_STATE_NORMAL	(0)
#define STAGE_STATE_SET		(1)
#define STAGE_STATE_EXP		(2)

#define FIN_TIME_EXP (50)

#define STAGE_CUBE_TIME_INFTY ((unsigned char)(255))

extern MAT mat_normal_cube;

class StageCube {
private:
	char m_state;
	char m_kind_mark;
	int m_pos_z, m_pos_x;
	unsigned char m_time;
	
public:
	StageCube(int pos_z, int pos_x);
	
	void calc(void);
	void draw(void);
	
	void set_marker(int type);
	void exp_nml_marker(void);
	void exp_marker(void);
	char get_state(void);
	char get_marker(void);
	char get_kind_mark(void);
};

class Stage : public Object {
private:
	StageCube* marker_map[6][32];
	int m_player_marker_flag;
	
	void set_marker(int type, float pos_z, float pos_x);
	void exp_nml_marker(void);
	
public:
	Stage(void);
	void calc(void);
	void draw(void);
	
	void player_marker(float pos_z, float pos_x);
	void set_adv_marker(float pos_z, float pos_x);
	void exp_adv_marker(void);
	char get_marker(float pos_z, float pox_x);
};

#endif