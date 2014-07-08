#include "./Player.h"

MAT mat_player =
	{
		{0.1, 0.1, 0.9, 1.0},
		{0.1, 0.1, 0.9, 1.0},
		{0.3, 0.3, 0.3, 1.0},
		100.0
	};
	
extern Event event;

class MyEventCallbackListener : public EventCallbackListener {
public:
	void onKey(unsigned char key)
	{
		printf("KEY HIT\n");
	}
};

Player::Player(void)
{
	MyEventCallbackListener callback;
	event.add_key_listener(callback);
}

void Player::calc(void)
{
	pos_z += 0.01;
}

/* 高さ0.5程度のプレイヤーのポリゴンをつくる */
/* ステージ表面の0.25の位置にいます。        */
/* 引数はプレイヤーの向きのベクトルです      */
void Player::draw(void)
{
	/* シェーディングの設定 */
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat_player.diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_player.specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat_player.ambient);
	glMaterialf(GL_FRONT_AND_BACK,  GL_SHININESS, mat_player.shininess);
	
	glPushMatrix();
	glTranslatef(pos_x, 0.0, pos_z);
	glScalef( 0.2, 0.8, 0.2 );
	glutSolidCube(1.0);
	glPopMatrix();
}


void Player::set_pos(float z, float x)
{
	pos_z = z;
	pos_x = x;
}
void Player::get_pos(float *z, float *x)
{
	*z = pos_z;
	*x = pos_x;
}

void Player::set_look(float z, float x)
{
	look_z = z;
	look_x = x;
}
void Player::get_look(float *z, float *x)
{
	*z = look_z;
	*x = look_x;
}

