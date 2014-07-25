#include "./Puzzle.h"

extern Stage *stage;
extern Player *player;

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

int Puzzle::check_finish(void)
{
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 10; j++){
			if (m_state != STATE_RUN || (m_puzzle_map[i][j]->get_state() != STATE_DEL && m_puzzle_map[i][j]->get_kind() != CUBE_FORBIDDEN)){
				return (FALSE);
			}
		}
	}
	
	return (TRUE);
}

void Puzzle::set_state_fin(void)
{
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 10; j++){
			if (m_puzzle_map[i][j]->get_state() != STATE_DEL){
				m_puzzle_map[i][j]->start_down();
			}
		}
	}
}

int Puzzle::is_cube_pos(float pos_z, float pos_x)
{
	float cube_pos_z, cube_pos_x;
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 10; j++){
			if (m_puzzle_map[i][j]->get_state() != STATE_DEL){
				m_puzzle_map[i][j]->get_pos(&cube_pos_z, &cube_pos_x);
				if ((cube_pos_z - 16.5 < pos_z && pos_z < cube_pos_z - 15.5) && (cube_pos_x - 3.0 < pos_x && pos_x < cube_pos_x - 2.0)){
					printf("%f %f\n", cube_pos_x, pos_x);
					return (TRUE);
				}
			}
		}
	}
	
	return (FALSE);
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

void PuzzleCube::check_marker(void)
{
	//printf("%d %d\n", m_pos_z, m_pos_x);
	char marker = stage->get_marker(m_pos_z, m_pos_x);
	
	if (marker == MARKER_RED){
		m_state = STATE_DOWN;
		if (m_kind == CUBE_ADVANTAGE){ //アドバンテージキューブが爆破された場合、床にマーキング
				stage->set_adv_marker(m_pos_z, m_pos_x);
		}
	}
}

int PuzzleCube::calc(void)
{
	switch (m_state){
	  case STATE_GENERATE:
	  	if (m_pos_y < 1.0){
			m_pos_y += CUBE_GEN_SPD;
			return (1);
		}
		else {
			m_state = STATE_STOP;
		}
		return (0);
	  
	  case STATE_RUN:
	  	if (m_rot < 90.0){
			m_rot += CUBE_ROT_DEG;
	  	}
		else {
			float pos_z, pos_x;
			
			m_rot = 0.0;
			m_pos_z++;
			
			//プレイヤーがそのマスにいるか確認する
			player->get_pos(&pos_z, &pos_x);
			if (m_state != STATE_DOWN){
				m_wait = 0;
				m_state = STATE_WAIT_NEXT; //一時停止する
			}
		}
		break;
	
	  case STATE_WAIT_NEXT: //一時停止している状態
	  	if (m_wait > CUBE_WAIT_TIME){
			m_wait = 0;
			m_state = STATE_RUN;
	  	}
		else {
			//床が赤マーカかどうかチェックする
			check_marker(); 
			m_wait++;
		}
	  	break;
	
	  case STATE_DOWN:
	  	if (m_pos_y > -0.4){
			m_pos_y -= CUBE_DOWN_SPD;
	  	}
		else {
			m_pos_y = -1.0;
			m_state = STATE_DEL;
		}
		break;
	}
	
	return (0);
}

void PuzzleCube::draw(void)
{
	MAT mat;
	if (m_state == STATE_DEL){
		return;
	}
	
	/* キューブの質感の設定 */
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
	
	/* 描画処理 */
	glPushMatrix();
		/* 回転による変位を含む描画位置の決定 */
		float x = 1.0 * m_pos_x - 2.5;
		float y =	m_pos_y //現在のキューブのy方向の位置
					+ ((sqrt((0.98 * 0.98) / 2.0) * sin(D2R(m_rot) + (PI / 4.0))) //現在の中心高さ
					- (sqrt((0.98 * 0.98) / 2.0) * sin(PI / 4.0))); //面が床と接しているときの中心高さ
		float z =	1.0 * m_pos_z - 15.0 //現在のキューブのz方向の位置
					- ((sqrt((0.98 * 0.98) / 2.0) * cos(D2R(m_rot) + (PI / 4.0)))) - 0.5; //回転による-z方向へのズレ
		glTranslatef(x, y, z);
		
		/* キューブの回転 */
		GL_Utility::polarview(0, 0, -m_rot, 0);
		
		/* 少し小さ目のキューブを描画する */
		glutSolidCube(0.98);
	glPopMatrix();
}

/*** 以下ゲッタ・セッタ ***/
void PuzzleCube::start_generate(void)
{
	m_state = STATE_GENERATE;
}

void PuzzleCube::start_run(void)
{
	m_state = STATE_RUN;
}

void PuzzleCube::start_down(void)
{
	m_state = STATE_DOWN;
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

int PuzzleCube::get_kind(void)
{
	return (m_kind);
}

void PuzzleCube::get_pos(float *pos_z, float *pos_x)
{
	*pos_z = m_pos_z;
	*pos_x = m_pos_x;
}