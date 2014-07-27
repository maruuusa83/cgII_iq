#include "./Puzzle.h"

extern Stage *stage;
extern Player *player;
extern Puzzle *puzzle;

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
	//ファイルの読出し
	int n;
	int tmp;
	FILE *fp = fopen("./puzzle_map.txt", "r");
	fscanf(fp, "%d", &n);
	
	printf("%d\n", n);
	
	srand(time(NULL));
	n = rand() % n; //使うパズルの決定
	
	/*使わないパズルの読み捨て*/
	for (int i = 0; i < n; i++){
		int t1, t2, t3, t4, t5, t6;
		
		fscanf(fp, "%d", &tmp); //0の読み捨て
		printf("%d\n", tmp);
		for (int j = 0; j < 10; j++){
			fscanf(fp, "%d %d %d %d %d %d", &t1, &t2, &t3, &t4, &t5, &t6); //パズルの読み捨て
			printf("%d %d %d %d %d %d\n", t1, t2, t3, t4, t5, t6);
		}

	}
	
	/*パズル読み込み*/
	fscanf(fp, "%d", &tmp); //0の読み捨て
	for (int j = 0; j < 10; j++){
		int p1, p2, p3, p4, p5, p6;
		fscanf(fp, "%d %d %d %d %d %d", &p1, &p2, &p3, &p4, &p5, &p6);
		puts("hoge");
		
		m_puzzle_map[0][j] = new PuzzleCube(p1, j, 0);
		m_puzzle_map[1][j] = new PuzzleCube(p2, j, 1);
		m_puzzle_map[2][j] = new PuzzleCube(p3, j, 2);
		m_puzzle_map[3][j] = new PuzzleCube(p4, j, 3);
		m_puzzle_map[4][j] = new PuzzleCube(p5, j, 4);
		m_puzzle_map[5][j] = new PuzzleCube(p6, j, 5);
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
	
	m_size = 0.98;
	
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
			if ((m_pos_z - 16.5 < pos_z && pos_z < m_pos_z - 15.5) && (m_pos_x - 3.0 < pos_x && pos_x < m_pos_x - 2.0)){
				puzzle->set_state_fin();
			}
			
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
			printf("%d\n", m_pos_z);
			if (m_pos_z >= 32){
				m_state = STATE_DISAPPEAR;
				break;
			}
			
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
		
	  case STATE_DISAPPEAR:
	  	if (m_size > 0.0){
			m_size -= CUBE_DIS_SPD;
	  	}
		else {
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
		glutSolidCube(m_size);
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