#ifndef __PUZZLE_H__
#define __PUZZLE_H__


#include "./common.h"
#include "./Object.h"

#define STATE_GET_PUZZLE	(1)
#define STATE_GENERATE		(2)
#define STATE_RUN			(3)

class Puzzle : public Object {
private:
	int state;
	
	float puzzle_map[5][5];
	
public:
	Puzzle(void);
	
	void calc(void);
	void draw(void);
	
	void get_puzzle(void);
	void generate(void);
	void run(void);
};

#endif