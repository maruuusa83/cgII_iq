#include "./iq.h"

/* �C�x���g�Ǘ� */
Event *event = new Event;

/* �I�u�W�F�N�g */
Camera *camera = new Camera(0, 0, 0);
Stage *stage = new Stage;
Player *player = new Player;
Puzzle *puzzle = new Puzzle;

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
	
	glutMouseFunc(on_mouse);
	glutKeyboardFunc(on_key);
	glutSpecialFunc(on_skey);
}

void world(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	
	/* �J�����ʒu�̐ݒ� */
	/* TODO: GL_Utility��move_pos�֐��̒ǉ�           */
	/* polarview�ł��ƋC���������̂Ń��b�p����    */
	float x, y, z;
	float distance, twist, elevation, azimuth;
	camera->get_pos(&distance, &twist, &elevation, &azimuth);
	GL_Utility::polarview(distance, twist, elevation, azimuth); //�p�x�ƃv���C���[����̋����̐ݒ�
	
	player->get_pos(&z, &x);
	glTranslatef(-x, 0.0, -z); //�v���C���[�𒆐S�ɂ���ݒ�
	
	
	/* �X�e�[�W�ʒu�̒��� */
	glTranslatef(0.0, 0.0, 0.0); //�v���C���[��x�����̈ʒu�ɍ��킹��
	
	/* �����̈ړ� */
	glPushMatrix();
	GLfloat light_position0[] = {0.0, 10.0, 20.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glPopMatrix();
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	
	
	/*** �I�u�W�F�N�g�̕`��̊J�n               ***/
	/*** �`��֐��̑O��ōs���ۑ����Ă��܂��B ***/
	/*** �Ȃ��ōs��̕ۑ������Y��Ă����v�Ȃ� ***/
	/*** ���ɂ��邽�߂ł�                       ***/
	/* �v���C���[�̕`�� */
	glPushMatrix();
		glTranslatef(0.0, 0.75, 0.0);
		glPushMatrix();
	    	player->draw();
		glPopMatrix();
	glPopMatrix();
	
	/* �X�e�[�W�̐��� */
	glPushMatrix();
		stage->draw();
	glPopMatrix();
	
	/* �p�Y���̕`�� */
	glPushMatrix();
		puzzle->draw();
	glPopMatrix();
	/*** �I�u�W�F�N�g�̕`�悱���܂� ***/
	
	
	/* ���������A��Еt�� */
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
	
	
	player->calc();
	stage->calc();
	puzzle->calc();
	camera->calc();
	
	if (puzzle->check_finish() == TRUE){
		/* TODO: �Q�[���I���̏��� */
		exit(0);
	}
	
	glutPostRedisplay(); /* �ĕ`��̌Ăяo�� */
}

void on_mouse(int button, int state, int x, int y)
{
	event->call_mouse_listeners(button, state, x, y);
}

void on_key(unsigned char key, int x, int y)
{
	event->call_key_listeners(key);
}

void on_skey(int key, int x, int y)
{
	event->call_key_listeners(key);
}
