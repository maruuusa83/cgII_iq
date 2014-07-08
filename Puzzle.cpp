#include "./Puzzle.h"

/*** Puzzle�N���X�̒�` ***/
Puzzle::Puzzle(void)
{
	m_state = STATE_GET_PUZZLE;
}

void Puzzle::calc(void)
{
	switch (m_state){
	  case STATE_GET_PUZZLE:
	  	get_puzzle();
	  	break;
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

void Puzzle::get_puzzle(void)
{
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 10; j++){
			m_puzzle_map[i][j] = new PuzzleCube(CUBE_NORMAL);
		}
	}
}

void Puzzle::generate(void)
{
	
}

void Puzzle::run(void)
{
	
}


/*** PuzzleCube�N���X�̒�` ***/
PuzzleCube::PuzzleCube(char kind)
{
	m_kind = kind;
}