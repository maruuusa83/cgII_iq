#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "./common.h"
#include "./Object.h"
#include "./Event.h"
#include "./Stage.h"
#include "./Puzzle.h"

#define PLAYER_WALK_SPEED (0.12)

class Player : public Object {
private:
	float pos_z, pos_x;
	float look_z, look_x;
	
public:
	Player(void);
	
	void calc(void);
	void draw(void);
	
	void set_pos(float z, float x);
	void get_pos(float *z, float *x);
	void set_look(float z, float x);
	void get_look(float *z, float *x);
};

#endif