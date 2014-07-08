#ifndef __PUZZLE_H__
#define __PUZZLE_H__


#include "./common.h"
#include "./Object.h"

#define STATE_GENERATE	(1)
#define STATE_RUN		(2)

class Puzzle : public Object {
private:
	int state;
	
public:
	Puzzle(void);
	
	void calc(void);
	void draw(void);
	
	void generate(void);
	void run(void);
};

#endif