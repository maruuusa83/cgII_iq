#include "./Stage.h"

void Stage::calc(void)
{
	
}

/* �v���C���[�̈ʒu�ɍ��킹�đO�コ���Ȃ��� */
/* �X�e�[�W��`�悷��                       */
void Stage::draw()
{
	int i, j, k;
	
	/* �V�F�[�f�B���O�̐ݒ� */
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat_normal_cube.diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_normal_cube.specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat_normal_cube.ambient);
	glMaterialf(GL_FRONT_AND_BACK,  GL_SHININESS, mat_normal_cube.shininess);
	
	
	/* �X�e�[�W�̕`�揈�� */
	glPushMatrix();
	glTranslatef(2.5, 0.0, -16.0); //�E���ɗ���悤�Ɉړ�

	for(k = 0; k < 6; k++){
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