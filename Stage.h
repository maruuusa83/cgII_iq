#ifndef __STAGE_H__
#define __STAGE_H__


#include "./common.h"
#include "./Object.h"

#define NO_MARKER		(0)
#define MARKER_BLUE		(1)
#define MARKER_RED		(2)
#define MARKER_GREEN	(3)

extern MAT mat_normal_cube;

class Stage : public Object {
private:
	char marker_map[6][32];
	
public:
	Stage(void);
	void calc(void);
	void draw(void);
};

#endif