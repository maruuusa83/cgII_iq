#include "./Stage.h"

/* プレイヤーの位置に合わせて前後させながら */
/* ステージを描画する                       */
void Stage::make_stage()
{
	int i, j;
	
	/* シェーディングの設定 */
	glEnable(GL_DEPTH_TEST);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat_normal_cube.diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_normal_cube.specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat_normal_cube.ambient);
	glMaterialf(GL_FRONT_AND_BACK,  GL_SHININESS, mat_normal_cube.shininess);
	glEnable(GL_LIGHTING);
	
	/* ステージの描画処理 */
	glPushMatrix();
	glTranslatef(2.0, 0.0, -2.0); //右後ろに来るように移動
	for (i = 0; i < 5; i++){ //右後ろから順番に１つずつ描画
		glPushMatrix();
		for (j = 0; j < 5; j++){
			glutSolidCube(0.98); //キューブにほんの少し隙間を開ける
			glTranslatef(-1.0, 0.0, 0.0); //左に１つずれる
		}
		glPopMatrix();
		glTranslatef(0.0, 0.0, 1.0); //前に１つずれる
	}
	glPopMatrix();
}