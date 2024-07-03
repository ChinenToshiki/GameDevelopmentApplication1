#include"Bullet.h"
#include"DxLib.h"
#include"../../Utility/InputControl.h"
#include"../DeleteAnim.h"

Bullet::Bullet() {
	speed = 2.0f;
	isShot = false;
	Number = Bullet_Number;
	box_size = 30;

	BulletAnim[0] = LoadGraph("Resource/Images/EnemyBullet/1.png");
	Sound = LoadSoundMem("Resource/Sounds/bishi.wav");
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
}

void Bullet::Finalize()
{
	PlaySoundMem(Sound, DX_PLAYTYPE_BACK);
	CreateObject<DeleteAnim>(location)->GetObjectType(this->Number);
}

void Bullet::Update()
{
	Movement();
	Shot();

	//画面外へ行ったら自身を削除
	if (location.x <= 0.0f || location.y <= -20.0f || location.x >= 920.0f || location.y >= 720.0f)
	{
		DeleteClass(this);
	}
}

void Bullet::Draw() const
{
	DrawExtendGraphF(location.x-15, location.y-15,location.x+15,location.y+15, BulletAnim[0], true);
#ifdef D_PIVOT_CENTER
	Vector2D tl = location - (box_size / 2.0f);
	Vector2D br = location + (box_size / 2.0f);

	DrawBoxAA(tl.x, tl.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#else
	Vector2D tl = location;
	Vector2D br = location + box_size;

	DrawBoxAA(tl.x, tl.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif // D_PIVOT_CENTER

}

void Bullet::Movement()
{
	Vector2D diff = NULL;
	//プレイヤーとエネミーの自身の差
	 diff = Vector2D((Player_location.x) - this->GetLocation().x, (Player_location.y-70.0f) - this->GetLocation().y);

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
		scene->DownTimer();
		DeleteClass(this);
	}
}


float Bullet::GetSpeed()
{
	return speed;
}

void Bullet::Shot(Vector2D location)
{
	isShot = true;
}