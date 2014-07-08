#ifndef __STAGE_H__
#define __STAGE_H__


#include "./common.h"
#include "./Object.h"

extern MAT mat_normal_cube;

class Stage : public Object {
public:
	void calc(void);
	void draw(void);
};

#endif