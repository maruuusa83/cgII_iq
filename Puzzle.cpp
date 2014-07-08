#include "./Puzzle.h"

/*** Puzzleクラスの定義 ***/
Puzzle::Puzzle(void)
{
	m_state = STATE_GET_PUZZLE;
	
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 10; j++){
			m_puzzle_map[i][j] = NULL;
		}
	}
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
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 10; j++){
			if (m_puzzle_map[i][j] != NULL){
				m_puzzle_map[i][j]->draw();
			}
		}
	}
}

void Puzzle::get_puzzle(void)
{
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 10; j++){
			m_puzzle_map[i][j] = new PuzzleCube(CUBE_NORMAL, j, i);
		}
	}
	
	m_state = STATE_GENERATE;
}

void Puzzle::generate(void)
{
	int flag = 0;
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 10; j++){
			float pos_y = m_puzzle_map[i][j]->get_pos_y();
			if (pos_y < 1.0){
				m_puzzle_map[i][j]->set_pos_y(pos_y + 0.01);
				flag = 1;
			}
		}
	}
	
	if (flag == 0){
		m_state = STATE_RUN;
	}
}

void Puzzle::run(void)
{
	
}


/*** PuzzleCubeクラスの定義 ***/
PuzzleCube::PuzzleCube(char kind, int pos_z, int pos_x)
{
	m_kind = kind;
	m_pos_z = pos_z;
	m_pos_x = pos_x;
	
	m_pos_y = 0.0;
	
	printf("m_pos_x : %d\n", m_kind);
}

void PuzzleCube::calc(void)
{
	
}

void PuzzleCube::draw(void)
{
	glPushMatrix();
	glTranslatef(1.0 * m_pos_x - 2.5, m_pos_y, 1.0 * m_pos_z - 16.0); 
	glutSolidCube(0.98);
	glPopMatrix();
}

void PuzzleCube::set_pos_y(float pos_y)
{
	m_pos_y = pos_y;
}
float PuzzleCube::get_pos_y(void)
{
	return (m_pos_y);
}
