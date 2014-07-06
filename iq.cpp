#include "./iq.h"

/* オブジェクト */
Camera camera(0, 0, 0);

int main(int argc, char **argv)
{
	/* 初期化 */
	init(argc, argv);
	
	/* 処理の開始 */
	glutMainLoop();

	return (0);
}

void init(int argc, char **argv)
{
	glutInit(&argc, argv);

	/* ウィンドウの設定など */
	glutInitWindowSize(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	/* 画面の初期化 */ 
	glutCreateWindow(argv[0]);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	
	glEnable(GL_LIGHT0);
	
	/* カメラに関する設定 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (float)DISPLAY_WIDTH / (float)DISPLAY_HEIGHT, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
	
	/* 各コールバックの設定 */
	glutDisplayFunc(world); //描画処理の関数を設定
	glutIdleFunc(idle); //アイドル中の処理を設定
}

void world(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	
	/* カメラ位置の設定 */
	/* TODO: GL_Utilityにmove_pos関数の追加           */
	/* polarviewでやると気持ち悪いのでラッパつくる    */
	float x, y, z;
	camera.get_pos(&x, &y, &z);
	GL_Utility::polarview(10, 30, 50, 30);
	
	
	/* 光源の移動 */
	glPushMatrix();
	GLfloat light_position0[] = {0.0, 0.0, 3.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glPopMatrix();
	
	
	/* シェーディングの設定 */
	glEnable(GL_DEPTH_TEST);
	float diffuse[] = { 0.9, 0.9, 0.9, 1.0 };
	float specular[] = { 0.9, 0.9, 0.9, 1.0 };
	float ambient[] = {0.7, 0.7, 0.7, 1.0};
	float shininess = 128.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glEnable(GL_LIGHTING);
	
	
	/*** テストオブジェクト ***/
	glPushMatrix();
	glutSolidCube(1.0);
	glPopMatrix();
	/*** テストオブジェクトここまで ***/
	
	glPopMatrix();
	
	glutSwapBuffers();
}

void idle(void)
{
	/* TODO: 各オブジェクトの計算処理部分の呼び出し   */
	/* 先ずは全オブジェクトのcalc_posを呼び出してから */
	/* それぞれの位置を取得・設定していく             */
}
