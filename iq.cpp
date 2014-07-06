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
	GL_Utility::polarview(10, 0, 0, 0);
	
	
	/*** テストオブジェクト ***/
	glPushMatrix();
	glutSolidCone(1.0, 2.0, 12, 3);
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
