#include "./Stage.h"

MAT mat_red_cube =
	{
		{0.9, 0.4, 0.4, 1.0},
		{0.9, 0.3, 0.3, 1.0},
		{0.9, 0.4, 0.4, 1.0},
		128.0
	};
MAT mat_blue_cube =
	{
		{0.2, 0.4, 0.7, 1.0},
		{0.1, 0.3, 0.7, 1.0},
		{0.2, 0.4, 0.7, 1.0},
		128.0
	};
MAT mat_green_cube =
	{
		{0.4, 0.9, 0.4, 1.0},
		{0.3, 0.9, 0.3, 1.0},
		{0.4, 0.9, 0.4, 1.0},
		128.0
	};

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
	
	/*** 一段目以降の設定 ***/
	/* ステージの描画処理 */
	glPushMatrix();
	for (i = 0; i < 32; i++){
		for (j = 0; j < 6; j++){
			marker_map[j][i]->draw();
		}
	}
	glPopMatrix();
	
	
	/*** 二段目以降の設定 ***/
	/* シェーディングの設定 */
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat_normal_cube.diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_normal_cube.specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat_normal_cube.ambient);
	glMaterialf(GL_FRONT_AND_BACK,  GL_SHININESS, mat_normal_cube.shininess);
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
	MAT mat;
	
	switch (m_kind_mark){
	  case NO_MARKER:
	  	mat = mat_normal_cube;
	  	break;
	  
	  case MARKER_BLUE:
	  	mat = mat_blue_cube;
		break;
	  
	  case MARKER_RED:
	 	mat = mat_red_cube;
		break;
	  
	  case MARKER_GREEN:
	  	mat = mat_green_cube;
		break;
	}
	
	
	/* シェーディングの設定 */
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat.diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat.specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat.ambient);
	glMaterialf(GL_FRONT_AND_BACK,  GL_SHININESS, mat.shininess);
	
	/* 描画する処理 */
	glPushMatrix();
	glTranslatef(2.5 - m_pos_x, 0.0, -16.0 + m_pos_z); //右後ろに来るように移動
	glutSolidCube(0.98); //キューブの描画
	
	if (m_kind_mark != NO_MARKER){
		glTranslatef(0.0, 1.9, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glutSolidCone(0.08, 0.18, 12, 3);
	}
	glPopMatrix();
}
