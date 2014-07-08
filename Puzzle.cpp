#include "./Puzzle.h"

Puzzle::Puzzle(void)
{
	state = STATE_GENERATE;
}

void Puzzle::calc(void)
{
	switch (state){
	  case STATE_GENERATE:
	  	generate();
		break;
		
	  case STATE_RUN:
	  	run();
		break;
	}
}

void Puzzle::draw(void)
{
	
}

void Puzzle::generate(void)
{
	
}

void Puzzle::run(void)
{
	
}
