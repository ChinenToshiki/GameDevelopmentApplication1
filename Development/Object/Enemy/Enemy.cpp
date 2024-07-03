#include"Enemy.h"
#include"DxLib.h"
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"../../Scene/Scene.h"
#include"Bullet.h"

Scene* Sc;
Bullet* bullet;

Enemy::Enemy() :animation_count(0), direction(1.0f), EnemyType(0), speed(0), isShot(false),isOut(false)
{
	for (int i = 0; i < 5; i++)
	{
		animation[i] = NULL;
	}


	Score = 0;

	player = nullptr;
	bullet = nullptr;

}

Enemy::~Enemy()
{

}

void Enemy::Initialize()
{

	if (GetLocation().x > 1.0f)
	{
		direction = -1.0f;
	}
	Number = Enemy_Number;
	EnemyType = GetRand(100);
	//EnemyType  0-15 = Gold; 16-40 = Box; 41-75 = Wing 76-100 = harpy;
	if(EnemyType<16) {
		animation[0] = LoadGraph("Resource/Images/GoldEnemy/1.png");
		animation[1] = LoadGraph("Resource/Images/GoldEnemy/2.png");
		animation[2] = LoadGraph("Resource/Images/GoldEnemy/3.png");
		animation[3] = LoadGraph("Resource/Images/GoldEnemy/4.png");
		animation[4] = LoadGraph("Resource/Images/GoldEnemy/5.png");
		Score = 1500;
		Sound = LoadSoundMem("Resource/Sounds/arrows_perfect03_short.wav");

	}
	else if(EnemyType<41)
	{
		animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
		animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");
		Score = 200;
		Sound = LoadSoundMem("Resource/Sounds/Boss_gahee.wav");
	}
	else if(EnemyType < 76)
	{
		animation[0] = LoadGraph("Resource/Images/WingEnemy/1.png");
		animation[1] = LoadGraph("Resource/Images/WingEnemy/2.png");
		Score = 30;
		Sound = LoadSoundMem("Resource/Sounds/teki_gahee.wav");
	}
	else
	{
		animation[0] = LoadGraph("Resource/Images/Harpy/1.png");
		animation[1] = LoadGraph("Resource/Images/Harpy/2.png");
		Score = -100;
		Sound = LoadSoundMem("Resource/Sounds/pokan.wav");
	}
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("なにかしらの敵の画像がありません");
	}

	switch (EnemyType) {
	case 1:
		speed = 1.5f;
		break;
	default:
		speed = 1;
		break;
	}

	radian = 0.0f;
	box_size = 64.0f;
	image = animation[0];
}


void Enemy::Update()
{


	Movement();

	AnimationControl();

	//エネミーが箱だった時に処理に入る
	switch (EnemyType)
	{
	case 0:
		//３以上でShotに移行(今だけ)
		if (3 > GetRand(10) && isShot == false)
		{
			Shot();
		}
	}

	//for (int i = 0; i < 4; i++)
	//{
	//	enemy_value[i][6] = 0;
	//	for (int j = 0; j < 7; j++)
	//	{
	//		if (enemy_value[i][j] == 1)
	//		{
	//			enemy_value[i][6] += 1;
	//		}
	//	}
	//}

	if (-1.0f > location.x || 930.0f < location.x)
	{
		isOut = true;
		DeleteClass(this);
	}
}

void Enemy::Draw() const
{

	int flip_flag = FALSE;

	if (direction > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

#if _DEBUG
	Vector2D ul = location - (box_size / 2.0f);
	Vector2D br = location + (box_size / 2.0f);

	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

	__super::Draw();
}

void Enemy::OnHitCollision(GameObject* hit_object)
{
	if (hit_object == player)
	{
	direction = 0.0f;
	}
}

void Enemy::SetPlayer(Player* player)
{
	this->player = player;
}

void Enemy::Finalize()
{
	for (int i = 0; i < 4; i++)
	{
	DeleteGraph(animation[i]);
	}

 	if (isOut == false)
	{
		scene->ScoreUpdate(Score);
	}

	PlaySoundMem(Sound, DX_PLAYTYPE_BACK);

	scene->DownEnemyCount();
}

void Enemy::SetBL(Vector2D location) 
{
	bullet = CreateObject<Bullet>(Vector2D(location.x,location.y));

	bullet->SetLocation(player->GetLocation(), Vector2D(this->location));

}

void Enemy::Movement()
{
	//進行方向に向かって位置座標を変更する
	location.x += direction * speed;
}

void Enemy::AnimationControl()
{
	animation_count++;

	if (animation_count >= 60)
	{
		animation_count = 0;

		switch (EnemyType){
		case 1:
		{
			animation_count = 30;
			int j = 0;
			while (j != 5)
			{
				if (image == animation[j])
				{
					break;
				}
				j++;
			}
			if (j == 4)
			{
				image = animation[0];
			}
			else
			{
				j++;
				image = animation[j];
			}
			break;
		}
		default:
		{
			if (image == animation[0])
			{
				image = animation[1];
			}
			else
			{
				image = animation[0];
			}
			break;
		}
		}
	}
}

void Enemy::Shot()
{	
	//Bulletにセットする処理
	SetBL(this->location);
	isShot = true;
}