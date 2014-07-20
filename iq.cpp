#include "./iq.h"

/* イベント管理 */
Event *event = new Event;

/* オブジェクト */
Camera *camera = new Camera(0, 0, 0);
Stage *stage = new Stage;
Player *player = new Player;
Puzzle *puzzle = new Puzzle;

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
	
	glutMouseFunc(on_mouse);
	glutKeyboardFunc(on_key);
	glutSpecialFunc(on_skey);
}

void world(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	
	/* カメラ位置の設定 */
	/* TODO: GL_Utilityにmove_pos関数の追加           */
	/* polarviewでやると気持ち悪いのでラッパつくる    */
	float x, y, z;
	float distance, twist, elevation, azimuth;
	camera->get_pos(&distance, &twist, &elevation, &azimuth);
	GL_Utility::polarview(distance, twist, elevation, azimuth); //角度とプレイヤーからの距離の設定
	
	player->get_pos(&z, &x);
	glTranslatef(-x, 0.0, -z); //プレイヤーを中心にする設定
	
	
	/* ステージ位置の調整 */
	glTranslatef(0.0, 0.0, 0.0); //プレイヤーのx方向の位置に合わせる
	
	/* 光源の移動 */
	glPushMatrix();
	GLfloat light_position0[] = {0.0, 10.0, 20.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glPopMatrix();
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	
	
	/*** オブジェクトの描画の開始               ***/
	/*** 描画関数の前後で行列を保存しています。 ***/
	/*** なかで行列の保存をし忘れても大丈夫なよ ***/
	/*** うにするためです                       ***/
	/* プレイヤーの描画 */
	glPushMatrix();
		glTranslatef(0.0, 0.75, 0.0);
		glPushMatrix();
	    	player->draw();
		glPopMatrix();
	glPopMatrix();
	
	/* ステージの生成 */
	glPushMatrix();
		stage->draw();
	glPopMatrix();
	
	/* パズルの描画 */
	glPushMatrix();
		puzzle->draw();
	glPopMatrix();
	/*** オブジェクトの描画ここまで ***/
	
	
	/* ここから先、後片付け */
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
	
	
	player->calc();
	stage->calc();
	puzzle->calc();
	camera->calc();
	
	if (puzzle->check_finish() == TRUE){
		/* TODO: ゲーム終了の処理 */
		exit(0);
	}
	
	glutPostRedisplay(); /* 再描画の呼び出し */
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
