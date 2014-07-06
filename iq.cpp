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
	GL_Utility::reshape(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	
	/* 各コールバックの設定 */
	glutDisplayFunc(world); //描画処理の関数を設定
	glutIdleFunc(idle); //アイドル中の処理を設定
	glutReshapeFunc(GL_Utility::reshape); //画面サイズが変更された時の処理
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
	GL_Utility::polarview(20, -10, -40, 20);
	
	/* ステージ位置の調整 */
	glTranslatef(0.0, 0.0, 0.0); //プレイヤーのx方向の位置に合わせる
	
	/* 光源の移動 */
	glPushMatrix();
	GLfloat light_position0[] = {0.0, 10.0, 0.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glPopMatrix();
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	
	
	/* プレイヤーの描画 */
	//Player::draw(0.0, 0.0); //z軸を正面とした方向ベクトルを渡す
	
	/* ステージの生成 */
	Stage::make_stage();
	
	/* 後片付け */
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	
	glPopMatrix();
	
	glutSwapBuffers();
}

void idle(void)
{
	/* TODO: 各オブジェクトの計算処理部分の呼び出し   */
	/* 先ずは全オブジェクトのcalc_posを呼び出してから */
	/* それぞれの位置を取得・設定していく             */
}
