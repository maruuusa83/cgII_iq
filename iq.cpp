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
}

void world(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	
	/* カメラ位置の設定 */
	float x, y, z;
	camera.get_pos(&x, &y, &z);
	GL_Utility::polarview(0, 0, 0, 0);
}