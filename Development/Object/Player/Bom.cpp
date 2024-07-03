#include"Bom.h"
#include"DxLib.h"
#include"../../Utility/InputControl.h"
#include"Player.h"
#include"../DeleteAnim.h"
#include"../Enemy/Enemy.h"

#define PI 3.141592654

Bom::Bom() {
	speed = 1.0f;
	isShot = false;
	Anim = NULL;
	dele = FALSE;
	radian = 15.0;
	Number = Bom_Number;
	box_size = Vector2D(50.0f, 80.0f);
}

Bom::~Bom()
{
	DeleteGraph(Anim);
}

//������
void Bom::Initialize()
{
	location.y += 100.0f;
	Anim = LoadGraph("Resource/Images/Bomb/Bomb.png");
	sound = LoadSoundMem("Resource/Sounds/explosion.wav");
	if (Anim == NULL)
	{
		throw("�ڂނ��[��[");
	}


}
 
void Bom::Update()
{

	//��ʊO(x���O�ȉ��X�Q�O�ȏ�)(y�͉��ɂ����s���Ȃ��̂�700�ȏ�)�֍s�����玩�g���폜
	if (location.x <= -50.0f || 920.0f <= location.x || location.y >= 600.0f)
	{
		//DeleteClass��DeleteObject���Ăяo���Ă�
 		DeleteClass(this);
	}

	Movement();
	
}

void Bom::Draw() const
{
	DrawRotaGraphF(location.x,location.y,1.0,PI/2, Anim,TRUE,FALSE);
	//DrawGraph(location.x, location.y, Anim, true);


#if _DEBUG
	Vector2D ul = location - (box_size / 2.0f);
	Vector2D br = location + (box_size / 2.0f);

	DrawBoxAA(ul.x, ul.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif

}

void Bom::Movement()
{
	location.y += 5.0f;
}

void Bom::Shot()
{
}

//����������
void Bom::Finalize()
{
	//�T�E���h���Đ����A���g�̎��ʔԍ���DeleteAnim�ɑ���
	PlaySoundMem(sound, DX_PLAYTYPE_BACK);
	CreateObject<DeleteAnim>(location)->GetObjectType(this->Number);
}

float Bom::GetSpeed()
{
	return speed;
}

Vector2D Bom::GetLocation()
{
	return location;
}

//����������
void Bom::OnHitCollision(GameObject* hit_object)
{
	//���ʔԍ����擾
	int hit_num;
 	hit_num = hit_object->GetNuber();

	//Enemy* hitObject = dynamic_cast<Enemy*>(hit_object);

	//if (hitObject == nullptr)
	//{
	//	return;
	//}
	//hit_num = Enemy_Number;

	//���ʔԍ��œ��������I�u�W�F�N�g��F������
	if (hit_num == Enemy_Number)
	{
		DeleteClass(hit_object);
		DeleteClass(this);
	}


}
