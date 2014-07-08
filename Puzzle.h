#ifndef __PUZZLE_H__
#define __PUZZLE_H__


#include "./common.h"
#include "./Object.h"

#include <stdio.h>

#define STATE_GET_PUZZLE	(1)
#define STATE_GENERATE		(2)
#define STATE_RUN			(3)

class PuzzleCube : public Object {
private:
	char m_kind;
	int m_pos_z, m_pos_x;
	float m_pos_y;
	
public:
	PuzzleCube(char kind, int pos_z, int pos_x);

	void calc(void);
	void draw(void);
	
	void set_pos_y(float pos_y);
	float get_pos_y(void);
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
};

#endif