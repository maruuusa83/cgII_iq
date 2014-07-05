/*  c3-2.c   Copyright (c) 2003 by T. HAYASHI and K. KATO  */
/*                                    All rights reserved  */

/*  c3-1-101324.c   Copyright (c) 2014 by D.TERUYA  */
/*                             All rights reserved  */

#include "./common.h"
#include "./GL_Utility.h"

float theta = 0.0;
int xBegin, yBegin; /* �h���b�O�J�n���_�̃}�E�X�|�C���^�̍��W */
int depth = 0.0;

float distance, twist, elevation, azimuth;
float lightSpin;
float light0[] = { -3.0, 0.0, 0.0, 1.0 };/* �����O�̈ʒu�Ǝ�ށi�_�����j*/
unsigned char wireFlag = GL_TRUE;
unsigned char rotateFlag = GL_FALSE;
unsigned char shadeFlag = GL_FALSE;

int down_pos;

int mButton; /* �h���b�O���ɉ�����Ă���}�E�X�{�^���̔��� */


float diffuse[] = { 0.0, 0.5, 1.0, 1.0 };
float specular[] = { 0.8, 0.8, 0.8, 1.0 };
float ambient[] = { 0.1, 0.1, 0.1, 1.0 };
float shininess = 128.0;

void display( void );
void myKbd( unsigned char, int, int );
void myInit ( char* );
void myMouse( int button, int state, int x, int y );
void myMotion( int x, int y );
void resetview( void );
void idle(void);
void mySkey(int key, int x, int y);
void init(int argc, char** argv);

int main(int argc, char** argv)
{
	init(argc, argv);
	glutSpecialFunc(mySkey);
    glutDisplayFunc(display);
	glutReshapeFunc(GL_Utility::reshape);
	glutMainLoop(); 
	return( 0 );
}

void init(int argc, char** argv)
{
	float aspect = (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT;
	
	glutInit(&argc, argv);
	
	
	lightSpin = 0.0;
	
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow(argv[0]);
    glClearColor (0.0, 0.0, 0.0, 1.0);
	glEnable( GL_LIGHT0 );
	resetview();
	
    glutKeyboardFunc( myKbd );
	glutMouseFunc(myMouse); /* �}�E�X�N���b�N�ɑ΂���R�[���o�b�N */
	glutMotionFunc(myMotion); /* �}�E�X�h���b�O�ɑ΂���R�[���o�b�N */
	glutIdleFunc(idle);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, aspect, 1.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

void display( void )
{
	int i;
	
	glClear( GL_COLOR_BUFFER_BIT );
	glPushMatrix();/* ���W�n�̕ۑ� */

    //glTranslatef( 0.0, 0.0, -20.0 );
	GL_Utility::polarview(distance, twist, elevation, azimuth);
	
	/* �����̈ړ� */
	glPushMatrix();
	glRotatef(lightSpin, 0.0, 1.0, 0.0);
	glLightfv( GL_LIGHT0, GL_POSITION, light0);
	glPopMatrix();

	if (wireFlag == GL_TRUE){
	    glPushMatrix();/* ���W�n�̕ۑ� */
	    glTranslatef( 0.0, 1.0, 0.0 );
		myWireCylinder( 1.0, 2.0, 12 );
		glTranslatef( 0.0, 1.0, 0.0);
		glRotatef( -90.0, 1.0, 0.0, 0.0 );
		glutWireCone( 1.0, 2.0, 12, 3 );
		glPopMatrix();/* ���W�n�̕����@33�s�̍��W�n�ɖ߂� */
		glTranslatef( 0.0, -1.0 + down_pos, 0.0 );
		
		myWireCylinder( 1.0, 2.0, 12 );/* 1�i�ڂ̕`�� */
		
		/* ���ˌ��̕`�� D.TERUYA 2014.4.8 */
		glPushMatrix();
		glTranslatef( 0.0, -1.5, 0.0 );    //1�i�ڂ̒�ɕ��ˌ������悤�ɍ��W�n�����Ɉړ�
		glRotatef( -90.0, 1.0, 0.0, 0.0 ); //�~����z�����ɕ`�悳���̂ŏ�����ɉ�]
		glutWireCone( 0.5, 1.0, 12, 3 );
		glPopMatrix();
		
		/* �H�̕`�� D.TERUYA 2014.4.8 */
		for (i = 0; i < 4; i++){
			glPushMatrix();
			glRotatef( 90.0 * i, 0.0, 1.0, 0.0 ); //�H�����Ƃ̌����̐ݒ�
			glScalef( 0.8, 1.5, 0.1 );            //�����`���H���̌`�ɂ��邽�߂ɃX�P�[���ύX
			glTranslatef( 1.7, 0.0, 0.0 );        //1�i�ڂ̕ǂɂ������悤��xy���ʂňړ�
			glutWireCube(1);
			glPopMatrix();
		}
	}
	else {
		if ( shadeFlag == GL_TRUE ){
			glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
			glEnable( GL_DEPTH_TEST );
			glMaterialfv( GL_FRONT, GL_DIFFUSE, diffuse );
			glMaterialfv( GL_FRONT, GL_SPECULAR, specular );
			glMaterialfv( GL_FRONT, GL_AMBIENT, ambient );
			glMaterialf( GL_FRONT, GL_SHININESS, shininess );
			glEnable( GL_LIGHTING );
		}
		
	    glPushMatrix();/* ���W�n�̕ۑ� */
	    glTranslatef( 0.0, 1.0, 0.0 );
		mySolidCylinder( 1.0, 2.0, 12 );
		glTranslatef( 0.0, 1.0, 0.0);
		glRotatef( -90.0, 1.0, 0.0, 0.0 );
		glutSolidCone( 1.0, 2.0, 12, 3 );
		glPopMatrix();/* ���W�n�̕����@33�s�̍��W�n�ɖ߂� */
		glTranslatef( 0.0, -1.0 + down_pos, 0.0 );
		
		mySolidCylinder( 1.0, 2.0, 12 );/* 1�i�ڂ̕`�� */
		
		/* ���ˌ��̕`�� D.TERUYA 2014.4.8 */
		glPushMatrix();
		glTranslatef( 0.0, -1.5, 0.0 );    //1�i�ڂ̒�ɕ��ˌ������悤�ɍ��W�n�����Ɉړ�
		glRotatef( -90.0, 1.0, 0.0, 0.0 ); //�~����z�����ɕ`�悳���̂ŏ�����ɉ�]
		glutSolidCone( 0.5, 1.0, 12, 3 );
		glPopMatrix();
		
		/* �H�̕`�� D.TERUYA 2014.4.8 */
		for (i = 0; i < 4; i++){
			glPushMatrix();
			glRotatef( 90.0 * i, 0.0, 1.0, 0.0 ); //�H�����Ƃ̌����̐ݒ�
			glScalef( 0.8, 1.5, 0.1 );            //�����`���H���̌`�ɂ��邽�߂ɃX�P�[���ύX
			glTranslatef( 1.7, 0.0, 0.0 );        //1�i�ڂ̕ǂɂ������悤��xy���ʂňړ�
			glutSolidCube(1);
			glPopMatrix();
		}
		
		if ( shadeFlag == GL_TRUE ){
			glDisable( GL_LIGHTING );
			glDisable( GL_DEPTH_TEST );
		}
	}

	glPopMatrix();/* ���W�n�̕����@50�s�ڂ̍��W�n�ɖ߂� */
	
	glutSwapBuffers(); 
}

void idle(void)
{
	if ( rotateFlag == GL_TRUE ){
		azimuth = fmod( azimuth + 0.05, 360.0 );
	}
	lightSpin = fmod( lightSpin - 1.0, 360.0 );
	glutPostRedisplay();
}

void myKbd( unsigned char key, int x, int y )
{
    switch( key ) {
	case 'r':
		rotateFlag = !rotateFlag;
		break;
    case 'w':
        wireFlag = !wireFlag;
        break;
	case 's':
		shadeFlag = !shadeFlag;
		break;
    case 'R':
        resetview();
        break;
    case KEY_ESC:
        exit( 0 );
    }
	glutPostRedisplay();
} 

void mySkey(int key, int x, int y)
{
	switch (key){
	case GLUT_KEY_F1:
		down_pos = -1;
		break;
	}
	glutPostRedisplay();
}

void myMouse( int button, int state, int x, int y )
{
	int xDisp, yDisp;
	
	xDisp = x - xBegin;
	yDisp = y - yBegin;
	
	if (state == GLUT_DOWN) {
		switch(button) {
		case GLUT_LEFT_BUTTON:
			mButton = button;
			break;
		case GLUT_MIDDLE_BUTTON:
			mButton = button;
			break;
		case GLUT_RIGHT_BUTTON:
			mButton = button;
			break;
		}
		xBegin = x; /* �h���b�O�񎋓_��x,y���W�l���擾 */
		yBegin = y;
	}
}

void myMotion( int x, int y )
{
	int xDisp, yDisp;
	
	xDisp = x - xBegin; /* �}�E�X�̈ړ������̌v�Z */
	yDisp = y - yBegin;

	switch (mButton) {
	case GLUT_LEFT_BUTTON: /* ���{�^���̃h���b�O�ŕ��̂̎p����ς��� */
		azimuth += (float) xDisp/2.0;
		elevation -= (float) yDisp/2.0;
		break;
	case GLUT_MIDDLE_BUTTON:
		twist += (float) xDisp/2.0;
		break;
	case GLUT_RIGHT_BUTTON: /* �E�{�^���̃h���b�O�ŃY�[�� */
		distance += (float) yDisp/40.0;
		break;
	}
	xBegin = x; /* ���̃X�e�b�v�̃}�E�X�̏o���_ */
	yBegin = y;
	/*printf("myMotion:xBegin=%d, yBegin=%d \n",xBegin,yBegin);*/

	glutPostRedisplay(); /* 1�X�e�b�v���̃h���b�O�̌��ʂ�`��ɔ��f */
}

void resetview( void )
{
    distance = 20.0;
    twist = 0.0;
    elevation = 0.0;
    azimuth = 0.0;
	
	down_pos = 0;
}
