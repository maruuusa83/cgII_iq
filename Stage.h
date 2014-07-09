#ifndef __STAGE_H__
#define __STAGE_H__


#include "./common.h"
#include "./Object.h"

#define NO_MARKER		(0)
#define MARKER_BLUE		(1)
#define MARKER_RED		(2)
#define MARKER_GREEN	(3)

#define STAGE_STATE_NORMAL	(0)
#define STAGE_STATE_SET		(1)
#define STAGE_STATE_EXP		(2)

extern MAT mat_normal_cube;

class StageCube {
private:
	char m_state;
	char m_kind_mark;
	int m_pos_z, m_pos_x;
	char m_bright;
	
public:
	StageCube(int pos_z, int pos_x);
	
	void calc(void);
	void draw(void);
	
	void set_marker(void);
	void exp_marker(void);
	char get_state(void);
};

class Stage : public Object {
private:
	StageCube* marker_map[6][32];
	
public:
	Stage(void);
	void calc(void);
	void draw(void);
};

#endif