#include"Enemy.h"
#include"DxLib.h"
#include<stdlib.h>
#include<math.h>

Enemy::Enemy():animation_count(0),direction(0.0f)
{
	animation[0] = NULL; 
	animation[1] = NULL;
}

Enemy::~Enemy()
{

}
void Enemy::OnHitCollision(GameObject* hit_object)
{
	direction = 0.0f;
}


void Enemy::Update()
{
	Movement();

	AnimationControl();
}

void Enemy::Initialize()
{
	animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");

	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ハコ敵の画像がありません");
	}

	radian = 0.0f;
	box_size = 64.0f;
	image = animation[0];
	direction = Vector2D(1.0f, -0.5f);
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

	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE);
#if _DEBUG
	Vector2D ul = location - (box_size / 2.0f);
	Vector2D br = location + (box_size / 2.0f);

	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);
	
	__super::Draw();
}

void Enemy::Finalize()
{
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

void Enemy::Movement()
{
	if (((location.x + direction.x) < box_size.x) || (640.0f - box_size.x) < (location.x + direction.x))
	{
		direction.x *= -1.0f;
	}
	if (((location.y + direction.y) < box_size.y) || (480.0f - box_size.y) < (location.y + direction.y))
	{
		direction.y *= -1.0f;
	}
	//進行方向に向かって位置座標を変更する
	location += direction;
}

void Enemy::AnimationControl()
{
	animation_count++;

	if (animation_count >= 60)
	{
		animation_count = 0;

		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}