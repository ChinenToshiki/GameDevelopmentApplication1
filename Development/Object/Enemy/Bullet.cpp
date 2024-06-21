#include"Bullet.h"
#include"DxLib.h"
#include"../../Utility/InputControl.h"
#include"../DeleteAnim.h"

Bullet::Bullet() {
	speed = 2.0f;
	location = (0.0f, 0.0f);
	isShot = false;
	Number = Bullet_Number;

	BulletAnim[0] = LoadGraph("Resource/Images/EnemyBullet/1.png");
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
}

void Bullet::Finalize()
{
	CreateObject<DeleteAnim>(location)->GetObjectType(this->Number);
}

void Bullet::Update()
{
	Movement();
	Shot();

	//画面外へ行ったら自身を削除
	if (location.x <= 0.0f || location.y <= 0.0f || location.x >= 920.0f || location.y >= 720.0f)
	{
		DeleteClass(this);
	}

}

void Bullet::Draw() const
{
	DrawGraphF(location.x, location.y, BulletAnim[0], true);
}

void Bullet::Movement()
{
	Vector2D diff = NULL;
	//プレイヤーとエネミーの自身の差
	 diff = Vector2D((Player_location.x - 25.0f) - this->GetLocation().x, (Player_location.y - 100.0f) - this->GetLocation().y);

	 float radian = NULL;
	//ベクトルから角度を知る
	radian = (float)atan2(diff.y, diff.x);

	if (diff.x > 0)
	{
		//そのベクトルに応じて移動する(0or180に近いと大きく90or270に近いほど小さくする※総量は１)
		location += Vector2D(cosf(radian), sinf(radian))*2.0f;
	}
	else if (diff.x < -0)
	{
		//そのベクトルに応じて移動する(0or180に近いと大きく90or270に近いほど小さくする※総量は１)
		location += Vector2D(cosf(radian), sinf(radian))*2.0f;
	}


	//float PtoE;
	//PtoE = Player_location.x - Bullet_location.x;
	//if (PtoE > 0)
	//{
	//	Bullet_location.x += 1.0f;
	//}
	//else
	//{
	//	Bullet_location.x -= 1.0f;
	//}
	//Bullet_location.y -= 1.0f;
}

void Bullet::Shot()
{
	isShot = true;
}

void Bullet::SetLocation(Vector2D location,Vector2D loc)
{
	if (isShot == false)
	{
	this->location = loc;
	//自身のローカル変数に直接代入
	Player_location = location;
}}

void Bullet::OnHitCollision(GameObject* hit_object)
{
	int hit_Nuber;
	hit_Nuber = hit_object->GetNuber();

	if (hit_Nuber == Player_Number)
	{
		DeleteClass(this);
	}
}


float Bullet::GetSpeed()
{
	return speed;
}

Vector2D Bullet::GetLocation()
{
	return location;
}

void Bullet::Shot(Vector2D location)
{
	isShot = true;
}