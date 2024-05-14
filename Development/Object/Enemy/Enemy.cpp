#include"Enemy.h"
#include"DxLib.h"
#include<stdlib.h>
#include<math.h>

Enemy::Enemy():animation_count(0),flip_flag(FALSE)
{

}

Enemy::~Enemy()
{

}
void Enemy::OnHitCollision(GameObject* hit_object)
{

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
		throw("ƒnƒR“G‚Ì‰æ‘œ‚ª‚ ‚è‚Ü‚¹‚ñ");
	}

	radian = 0.0f;
	scale = 64.0f;
	image = animation[0];
}

void Enemy::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);
}

void Enemy::Finalize()
{

}

void Enemy::Movement()
{

	float value;

	if (location.x == 700.0f)
	{
		
		value = -1.0f;
		flip_flag = true;
	}
	else if (location.x == -65.0f)
	{
		value = 1.0f;
		flip_flag = false;
	}
	else
	{
		if (flip_flag == false)
		{
			value = 1.0f;
		}
		else if (flip_flag == true)
		{
			value = -1.0f;
		}
	}
	
	location.x += 1.0f * value;
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