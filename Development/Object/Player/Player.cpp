#include "Player.h"
#include "Bom.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"

Player::Player() :animation_count(0), flip_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;

}

Player::~Player()
{

}

//初期化
void Player::Initialize()
{
	Number = Player_Number;

	animation[0] = LoadGraph("Resource/Images/Tri-Pilot/1.png");
	animation[1] = LoadGraph("Resource/Images/Tri-Pilot/2.png");
	sound = LoadSoundMem("Resource/Sounds/pan.wav");



	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("トリパイロットの画像がありません\n");
	}

	radian = 0.0f;

	box_size = 64.0f;

	image = animation[0];
}

void Player::Update()
{
	//動きの処理
	Movement();

	//アニメーションの処理
	AnimationControl();

	//スペースで爆弾を作る
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		PlaySoundMem(sound, DX_PLAYTYPE_BACK);
		CreateObject<Bom>(location);
	}

}

void Player::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);
#if _DEBUG
	Vector2D ul = location - (box_size / 2.0f);
	Vector2D br = location + (box_size / 2.0f);

	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif
}

void Player::Finalize()
{
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}


void Player::OnHitCollision(GameObject* hit_object)
{
	//あたったときーー
	

}

Vector2D Player::GetLocation()
{
	return this->location;
}

void Player::Movement()
{
	Vector2D velocity = 0.0f;

	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		velocity.x += -1.0f;
		flip_flag = TRUE;
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x += 1.0f;
		flip_flag = FALSE;
	}
	else
	{
		velocity.x = 0.0f;
	}
	location += velocity;
}

void Player::AnimationControl()
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