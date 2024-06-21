#include"Enemy.h"
#include"DxLib.h"
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"../../Scene/Scene.h"
#include"Bullet.h"

Scene* Sc;
Bullet* bullet;

static std::vector<std::vector<int>> enemy_value =
{
	 {0,0,0,0,0,0},
	 {0,0,0,0,0,0},
	 {0,0,0,0,0,0},
	 {0,0,0,0,0,0} };


Enemy::Enemy() :animation_count(0), direction(0.0f), EnemyType(0), speed(0), isShot(false)
{




	animation[0] = NULL; 
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
	animation[4] = NULL;


	player = nullptr;
	bullet = nullptr;

}

Enemy::~Enemy()
{

}


void Enemy::Initialize()
{
	Number = Enemy_Number;
	EnemyType = GetRand(3);
	//EnemyType 0 = Box; 1 = Gold; 2 = Wing;
	switch (EnemyType) {
	case 0:
	{
		animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
		animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");
		animation[2] = NULL;
		animation[3] = NULL;
		animation[4] = NULL;
		break;
	}
	case 1:
	{
		animation[0] = LoadGraph("Resource/Images/GoldEnemy/1.png");
		animation[1] = LoadGraph("Resource/Images/GoldEnemy/2.png");
		animation[2] = LoadGraph("Resource/Images/GoldEnemy/3.png");
		animation[3] = LoadGraph("Resource/Images/GoldEnemy/4.png");
		animation[4] = LoadGraph("Resource/Images/GoldEnemy/5.png");
		break;
	}
	case 2:
	{
		animation[0] = LoadGraph("Resource/Images/WingEnemy/1.png");
		animation[1] = LoadGraph("Resource/Images/WingEnemy/2.png");
		animation[2] = NULL;
		animation[3] = NULL;
		animation[4] = NULL;
		break;
	}
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
	direction = Vector2D(1.0f, -0.5f);
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
		if (3 < rand() % 10 + 1 && isShot == false)
		{
			Shot();
		}
	}

	for (int i = 0; i < 4; i++)
	{
		enemy_value[i][6] = 0;
		for (int j = 0; j < 7; j++)
		{
			if (enemy_value[i][j] == 1)
			{
				enemy_value[i][6] += 1;
			}
		}
	}

}

void Enemy::Draw() const
{

	int flip_flag = FALSE;

	if (direction.x > 0.0f)
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
}

void Enemy::SetBL(Vector2D location) 
{
	bullet = CreateObject<Bullet>(Vector2D(location.x,location.y));


	Vector2D a = player->GetLocation();
	bullet->SetLocation(player->GetLocation(), Vector2D(this->location));

}

void Enemy::Movement()
{
	if (((location.x + direction.x) < box_size.x) || (930.0f - box_size.x) < (location.x + direction.x))
	{
		direction.x *= ( - 1.0f );
	}

	//進行方向に向かって位置座標を変更する
	location += direction * speed;
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