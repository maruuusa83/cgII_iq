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
}

void world(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	
	/* �J�����ʒu�̐ݒ� */
	float x, y, z;
	camera.get_pos(&x, &y, &z);
	GL_Utility::polarview(0, 0, 0, 0);
}