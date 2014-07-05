/*  c3-2.c   Copyright (c) 2003 by T. HAYASHI and K. KATO  */
/*                                    All rights reserved  */

/*  c3-1-101324.c   Copyright (c) 2014 by D.TERUYA  */
/*                             All rights reserved  */

#include "./common.h"
#include "./GL_Utility.h"

float theta = 0.0;
int xBegin, yBegin; /* ドラッグ開始時点のマウスポインタの座標 */
int depth = 0.0;

float distance, twist, elevation, azimuth;
float lightSpin;
float light0[] = { -3.0, 0.0, 0.0, 1.0 };/* 光源０の位置と種類（点光源）*/
unsigned char wireFlag = GL_TRUE;
unsigned char rotateFlag = GL_FALSE;
unsigned char shadeFlag = GL_FALSE;

int down_pos;

int mButton; /* ドラッグ時に押されているマウスボタンの判別 */


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
	glutMouseFunc(myMouse); /* マウスクリックに対するコールバック */
	glutMotionFunc(myMotion); /* マウスドラッグに対するコールバック */
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
	glPushMatrix();/* 座標系の保存 */

    //glTranslatef( 0.0, 0.0, -20.0 );
	GL_Utility::polarview(distance, twist, elevation, azimuth);
	
	/* 光源の移動 */
	glPushMatrix();
	glRotatef(lightSpin, 0.0, 1.0, 0.0);
	glLightfv( GL_LIGHT0, GL_POSITION, light0);
	glPopMatrix();

	if (wireFlag == GL_TRUE){
	    glPushMatrix();/* 座標系の保存 */
	    glTranslatef( 0.0, 1.0, 0.0 );
		myWireCylinder( 1.0, 2.0, 12 );
		glTranslatef( 0.0, 1.0, 0.0);
		glRotatef( -90.0, 1.0, 0.0, 0.0 );
		glutWireCone( 1.0, 2.0, 12, 3 );
		glPopMatrix();/* 座標系の復元　33行の座標系に戻る */
		glTranslatef( 0.0, -1.0 + down_pos, 0.0 );
		
		myWireCylinder( 1.0, 2.0, 12 );/* 1段目の描画 */
		
		/* 噴射口の描画 D.TERUYA 2014.4.8 */
		glPushMatrix();
		glTranslatef( 0.0, -1.5, 0.0 );    //1段目の底に噴射口がつくように座標系を下に移動
		glRotatef( -90.0, 1.0, 0.0, 0.0 ); //円錐はz方向に描画されるので上向きに回転
		glutWireCone( 0.5, 1.0, 12, 3 );
		glPopMatrix();
		
		/* 羽の描画 D.TERUYA 2014.4.8 */
		for (i = 0; i < 4; i++){
			glPushMatrix();
			glRotatef( 90.0 * i, 0.0, 1.0, 0.0 ); //羽根ごとの向きの設定
			glScalef( 0.8, 1.5, 0.1 );            //正方形を羽根の形にするためにスケール変更
			glTranslatef( 1.7, 0.0, 0.0 );        //1段目の壁にくっつくようにxy平面で移動
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
		
	    glPushMatrix();/* 座標系の保存 */
	    glTranslatef( 0.0, 1.0, 0.0 );
		mySolidCylinder( 1.0, 2.0, 12 );
		glTranslatef( 0.0, 1.0, 0.0);
		glRotatef( -90.0, 1.0, 0.0, 0.0 );
		glutSolidCone( 1.0, 2.0, 12, 3 );
		glPopMatrix();/* 座標系の復元　33行の座標系に戻る */
		glTranslatef( 0.0, -1.0 + down_pos, 0.0 );
		
		mySolidCylinder( 1.0, 2.0, 12 );/* 1段目の描画 */
		
		/* 噴射口の描画 D.TERUYA 2014.4.8 */
		glPushMatrix();
		glTranslatef( 0.0, -1.5, 0.0 );    //1段目の底に噴射口がつくように座標系を下に移動
		glRotatef( -90.0, 1.0, 0.0, 0.0 ); //円錐はz方向に描画されるので上向きに回転
		glutSolidCone( 0.5, 1.0, 12, 3 );
		glPopMatrix();
		
		/* 羽の描画 D.TERUYA 2014.4.8 */
		for (i = 0; i < 4; i++){
			glPushMatrix();
			glRotatef( 90.0 * i, 0.0, 1.0, 0.0 ); //羽根ごとの向きの設定
			glScalef( 0.8, 1.5, 0.1 );            //正方形を羽根の形にするためにスケール変更
			glTranslatef( 1.7, 0.0, 0.0 );        //1段目の壁にくっつくようにxy平面で移動
			glutSolidCube(1);
			glPopMatrix();
		}
		
		if ( shadeFlag == GL_TRUE ){
			glDisable( GL_LIGHTING );
			glDisable( GL_DEPTH_TEST );
		}
	}

	glPopMatrix();/* 座標系の復元　50行目の座標系に戻る */
	
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
		xBegin = x; /* ドラッグ回視点のx,y座標値を取得 */
		yBegin = y;
	}
}

void myMotion( int x, int y )
{
	int xDisp, yDisp;
	
	xDisp = x - xBegin; /* マウスの移動距離の計算 */
	yDisp = y - yBegin;

	switch (mButton) {
	case GLUT_LEFT_BUTTON: /* 左ボタンのドラッグで物体の姿勢を変える */
		azimuth += (float) xDisp/2.0;
		elevation -= (float) yDisp/2.0;
		break;
	case GLUT_MIDDLE_BUTTON:
		twist += (float) xDisp/2.0;
		break;
	case GLUT_RIGHT_BUTTON: /* 右ボタンのドラッグでズーム */
		distance += (float) yDisp/40.0;
		break;
	}
	xBegin = x; /* 次のステップのマウスの出発点 */
	yBegin = y;
	/*printf("myMotion:xBegin=%d, yBegin=%d \n",xBegin,yBegin);*/

	glutPostRedisplay(); /* 1ステップ分のドラッグの結果を描画に反映 */
}

void resetview( void )
{
    distance = 20.0;
    twist = 0.0;
    elevation = 0.0;
    azimuth = 0.0;
	
	down_pos = 0;
}
