#include "./iq.h"

void init(int argc, char **argv);

int main(int argc, char **argv)
{
	init(argc, argv);

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
}
