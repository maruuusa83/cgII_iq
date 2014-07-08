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

/* パズルを取得して設定する関数 */
void Puzzle::get_puzzle(void)
{
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 10; j++){
			m_puzzle_map[i][j] = new PuzzleCube((i + j) % 3 + 1, j, i);
		}
	}
	
	m_state = STATE_GENERATE;
}

void Puzzle::generate(void)
{
	int flag = 0;
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 10; j++){
			/* 奥から順番に呼ばれるように調整 */
			if (j == 0){
				m_puzzle_map[i][j]->start_generate();
			}
			else {
				if (m_puzzle_map[i][j - 1]->get_pos_y() > 0.3){
					m_puzzle_map[i][j]->start_generate();
				}
			}
			
			/* すべてが浮上し終えるまで繰り返すためのフラグ */
			if ((m_puzzle_map[i][j]->get_state() == STATE_GENERATE) && (m_puzzle_map[i][j]->calc() == 1)){
				flag = 1;
			}
		}
	}
	
	if (flag == 0){
		for (int i = 0; i < 6; i++){
			for (int j = 0; j < 10; j++){
				m_puzzle_map[i][j]->start_run();
			}
		}
		m_state = STATE_RUN;
	}
}

void Puzzle::run(void)
{
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 10; j++){
			m_puzzle_map[i][j]->calc();
		}
	}
}


/*** PuzzleCubeクラスの定義 ***/
PuzzleCube::PuzzleCube(char kind, int pos_z, int pos_x)
{
	m_state = STATE_STOP;
	
	m_kind = kind;
	m_pos_z = pos_z;
	m_pos_x = pos_x;
	
	m_pos_y = -0.01; //0.0にしていると微妙に見えるので少し下げる
	m_rot = 0.0;
}

int PuzzleCube::calc(void)
{
	switch (m_state){
	  case STATE_GENERATE:
	  	if (m_pos_y < 1.0){
			m_pos_y += 0.01;
			return (1);
		}
		else {
			m_state = STATE_STOP;
		}
		return (0);
	  
	  case STATE_RUN:
	  	if (m_rot < 90.0){
			m_rot += 1;
	  	}
		else {
			m_rot = 0.0;
			m_pos_z++;
		}
		break;
	}
	
	return (0);
}

void PuzzleCube::draw(void)
{
	MAT mat;
	
	switch (m_kind){
	  case CUBE_NORMAL:
	  	mat = mat_normal_cube;
	  	break;
	
	  case CUBE_FORBIDDEN:
	  	mat = mat_forbidden_cube;
	  	break;
	
	  case CUBE_ADVANTAGE:
	  	mat = mat_advantage_cube;
	  	break;
	
	  default:
	  	mat = mat_normal_cube;
	}
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat.diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat.specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat.ambient);
	glMaterialf(GL_FRONT_AND_BACK,  GL_SHININESS, mat.shininess);
	
	glPushMatrix();
	
	float x = 1.0 * m_pos_x - 2.5;
	float y = m_pos_y + ((sqrt((0.98 * 0.98) / 2.0) * sin(D2R(m_rot) + (PI / 4.0))) - (sqrt((0.98 * 0.98) / 2.0) * sin(PI / 4.0)));
	float z = 1.0 * m_pos_z - 16.0 - ((sqrt((0.98 * 0.98) / 2.0) * cos(D2R(m_rot) + (PI / 4.0)))) - 0.5;
	glTranslatef(x, y, z);
	GL_Utility::polarview(0, 0, -m_rot, 0);
	glutSolidCube(0.98);
	glPopMatrix();
}

void PuzzleCube::start_generate(void)
{
	m_state = STATE_GENERATE;
}

void PuzzleCube::start_run(void)
{
	m_state = STATE_RUN;
}

void PuzzleCube::set_pos_y(float pos_y)
{
	m_pos_y = pos_y;
}
float PuzzleCube::get_pos_y(void)
{
	return (m_pos_y);
}
int PuzzleCube::get_state(void)
{
	return (m_state);
}