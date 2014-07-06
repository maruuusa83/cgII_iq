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

	
	glEnable(GL_LIGHT0);
	
	/* �J�����Ɋւ���ݒ� */
	GL_Utility::reshape(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	
	/* �e�R�[���o�b�N�̐ݒ� */
	glutDisplayFunc(world); //�`�揈���̊֐���ݒ�
	glutIdleFunc(idle); //�A�C�h�����̏�����ݒ�
	glutReshapeFunc(GL_Utility::reshape); //��ʃT�C�Y���ύX���ꂽ���̏���
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
	GL_Utility::polarview(20, -10, -40, 20);
	
	/* �X�e�[�W�ʒu�̒��� */
	glTranslatef(0.0, 0.0, 0.0); //�v���C���[��x�����̈ʒu�ɍ��킹��
	
	/* �����̈ړ� */
	glPushMatrix();
	GLfloat light_position0[] = {0.0, 10.0, 0.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glPopMatrix();
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	
	
	/* �v���C���[�̕`�� */
	//Player::draw(0.0, 0.0); //z���𐳖ʂƂ��������x�N�g����n��
	
	/* �X�e�[�W�̐��� */
	Stage::make_stage();
	
	/* ��Еt�� */
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	
	glPopMatrix();
	
	glutSwapBuffers();
}

void idle(void)
{
	/* TODO: �e�I�u�W�F�N�g�̌v�Z���������̌Ăяo��   */
	/* �悸�͑S�I�u�W�F�N�g��calc_pos���Ăяo���Ă��� */
	/* ���ꂼ��̈ʒu���擾�E�ݒ肵�Ă���             */
}
