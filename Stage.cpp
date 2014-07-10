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

/*** Stage�N���X�̒�` ***/
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

/* �v���C���[�̈ʒu�ɍ��킹�đO�コ���Ȃ��� */
/* �X�e�[�W��`�悷��                       */
void Stage::draw()
{
	int i, j, k;
	
	/*** ��i�ڈȍ~�̐ݒ� ***/
	/* �X�e�[�W�̕`�揈�� */
	glPushMatrix();
	for (i = 0; i < 32; i++){
		for (j = 0; j < 6; j++){
			marker_map[j][i]->draw();
		}
	}
	glPopMatrix();
	
	
	/*** ��i�ڈȍ~�̐ݒ� ***/
	/* �V�F�[�f�B���O�̐ݒ� */
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat_normal_cube.diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_normal_cube.specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat_normal_cube.ambient);
	glMaterialf(GL_FRONT_AND_BACK,  GL_SHININESS, mat_normal_cube.shininess);
	glPushMatrix();
	glTranslatef(2.5, 0.0, -16.0); //�E���ɗ���悤�Ɉړ�
	glTranslatef(0.0, -1.0, 0.0);
	for(k = 0; k < 5; k++){
		glPushMatrix();
		for (i = 0; i < 32; i++){ //�E��납�珇�ԂɂP���`��
			glPushMatrix();
			for (j = 0; j < 6; j++){
				glutSolidCube(0.98); //�L���[�u�ɂق�̏������Ԃ��J����
				glTranslatef(-1.0, 0.0, 0.0); //���ɂP�����
			}
			glPopMatrix();
			glTranslatef(0.0, 0.0, 1.0); //�O�ɂP�����
		}
		
		glPopMatrix();
		glTranslatef(0.0, -1.0, 0.0);
	}
	
	glPopMatrix();
}



/*** StageCube�N���X�̒�` ***/
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
	
	
	/* �V�F�[�f�B���O�̐ݒ� */
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat.diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat.specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat.ambient);
	glMaterialf(GL_FRONT_AND_BACK,  GL_SHININESS, mat.shininess);
	
	/* �`�悷�鏈�� */
	glPushMatrix();
	glTranslatef(2.5 - m_pos_x, 0.0, -16.0 + m_pos_z); //�E���ɗ���悤�Ɉړ�
	glutSolidCube(0.98); //�L���[�u�̕`��
	
	if (m_kind_mark != NO_MARKER){
		glTranslatef(0.0, 1.9, 0.0);
		glRotatef(90.0, 1.0, 0.0, 0.0);
		glutSolidCone(0.08, 0.18, 12, 3);
	}
	glPopMatrix();
}
