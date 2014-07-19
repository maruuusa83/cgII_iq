#include "./Player.h"

MAT mat_player =
	{
		{0.1, 0.1, 0.9, 1.0},
		{0.1, 0.1, 0.9, 1.0},
		{0.3, 0.3, 0.3, 1.0},
		100.0
	};
	
extern Event *event;
extern Stage *stage;

class MyEventCallbackListener : public EventCallbackListener {
public:
	void onKey(void *context, unsigned char key)
	{
		float z, x;
		Player *mPlayer = (Player *)context;
		
		mPlayer->get_pos(&z, &x);
		if (key == 'j'){
			stage->player_marker(z - 16.5, x + 4.0);
		}
		else if (key == 'k'){
			stage->exp_adv_marker();
		}
		
		switch (key){
		  case 'a':
			x -= PLAYER_WALK_SPEED;
			break;
		
		  case 'd':
			x += PLAYER_WALK_SPEED;
			break;
		
		  case 's':
			z += PLAYER_WALK_SPEED;
			break;
		
		  case 'w':
			z -= PLAYER_WALK_SPEED;
			break;
		}
		
		if (2.99 < x){
			x = 2.99;
		}
		else if (x < -2.99){
			x = -2.99;
		}
		if (15.499 < z){
			z = 15.499;
		}
		else if (z < -16.499){
			z = -16.499;
		}
		mPlayer->set_pos(z, x);
	}
};

Player::Player(void)
{
	MyEventCallbackListener *callback = new MyEventCallbackListener;
	event->add_key_listener((void *)this, callback);
}

void Player::calc(void)
{
	
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

