#include "./iq.h"

/* �I�u�W�F�N�g */
Camera camera(0, 0, 0);

int main(int argc, char **argv)
{
	/* ������ */
	init(argc, argv);
	
	/* �����̊J�n */
	glutMainLoop();

	return (0);
}

void init(int argc, char **argv)
{
	glutInit(&argc, argv);

	/* �E�B���h�E�̐ݒ�Ȃ� */
	glutInitWindowSize(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	/* ��ʂ̏����� */ 
	glutCreateWindow(argv[0]);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	/* �J�����Ɋւ���ݒ� */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
	
	/* �e�R�[���o�b�N�̐ݒ� */
	glutDisplayFunc(world); //�`�揈���̊֐���ݒ�
	glutIdleFunc(idle); //�A�C�h�����̏�����ݒ�
}

void world(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	
	/* �J�����ʒu�̐ݒ� */
	/* TODO: GL_Utility��move_pos�֐��̒ǉ�           */
	/* polarview�ł��ƋC���������̂Ń��b�p����    */
	float x, y, z;
	camera.get_pos(&x, &y, &z);
	GL_Utility::polarview(10, 0, 0, 0);
	
	
	/*** �e�X�g�I�u�W�F�N�g ***/
	glPushMatrix();
	glutSolidCone(1.0, 2.0, 12, 3);
	glPopMatrix();
	/*** �e�X�g�I�u�W�F�N�g�����܂� ***/
	
	glPopMatrix();
	
	glutSwapBuffers();
}

void idle(void)
{
	/* TODO: �e�I�u�W�F�N�g�̌v�Z���������̌Ăяo��   */
	/* �悸�͑S�I�u�W�F�N�g��calc_pos���Ăяo���Ă��� */
	/* ���ꂼ��̈ʒu���擾�E�ݒ肵�Ă���             */
}
