#ifndef __OBJECT_H__
#define __OBJECT_H__


#include "./common.h"

class Object
{
public:
	virtual void calc(void);
	virtual void draw(void);
};

#endif