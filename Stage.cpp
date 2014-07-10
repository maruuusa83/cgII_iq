#include "./Stage.h"


/*** Stageクラスの定義 ***/
Stage::Stage(void)
{
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 32; j++){
			marker_map[i][j] = new StageCube(j, i);
		}
	}
}

void Stage::calc(void)
{
	
}

/* プレイヤーの位置に合わせて前後させながら */
/* ステージを描画する                       */
void Stage::draw()
{
	int i, j, k;
	
	/* シェーディングの設定 */
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat_normal_cube.diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_normal_cube.specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat_normal_cube.ambient);
	glMaterialf(GL_FRONT_AND_BACK,  GL_SHININESS, mat_normal_cube.shininess);
	
	
	/* ステージの描画処理 */
	glPushMatrix();
	for (i = 0; i < 32; i++){
		for (j = 0; j < 6; j++){
			marker_map[j][i]->draw();
		}
	}
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(2.5, 0.0, -16.0); //右後ろに来るように移動
	glTranslatef(0.0, -1.0, 0.0);
	for(k = 0; k < 5; k++){
		glPushMatrix();
		for (i = 0; i < 32; i++){ //右後ろから順番に１つずつ描画
			glPushMatrix();
			for (j = 0; j < 6; j++){
				glutSolidCube(0.98); //キューブにほんの少し隙間を開ける
				glTranslatef(-1.0, 0.0, 0.0); //左に１つずれる
			}
			glPopMatrix();
			glTranslatef(0.0, 0.0, 1.0); //前に１つずれる
		}
		
		glPopMatrix();
		glTranslatef(0.0, -1.0, 0.0);
	}	
	
	glPopMatrix();
}



/*** StageCubeクラスの定義 ***/
StageCube::StageCube(int pos_z, int pos_x)
{
	m_state = STAGE_STATE_NORMAL;
	
	m_kind_mark = NO_MARKER;
	m_pos_z = pos_z;
	m_pos_x = pos_x;
	
	m_bright = 0;
}

void StageCube::draw(void)
{
	/* シェーディングの設定 */
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat_normal_cube.diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_normal_cube.specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat_normal_cube.ambient);
	glMaterialf(GL_FRONT_AND_BACK,  GL_SHININESS, mat_normal_cube.shininess);
	
	glPushMatrix();
	glTranslatef(2.5 - m_pos_x, 0.0, -16.0 + m_pos_z); //右後ろに来るように移動
	glutSolidCube(0.98);
	glPopMatrix();
}
