#include "DeleteAnim.h"
#include"DxLib.h"

DeleteAnim::DeleteAnim()
{
	for (int  i = 0; i < 5; i++)
	{
		Animation[i] = NULL;
	}
	ObjectType = NULL;
	AnimControl = 0;
}

DeleteAnim::~DeleteAnim()
{
}

void DeleteAnim::Initialize()
{

}

void DeleteAnim::Update()
{
	AnimationControl();
}

void DeleteAnim::Draw() const
{
	DrawExtendGraphF(location.x, location.y, location.x + 50.0f, location.y + 50.0f, image, TRUE);
}

void DeleteAnim::Finalize()
{
}

void DeleteAnim::GetObjectType(int type)
{
	this->ObjectType = type;

	switch (type)
	{
	case Bullet_Number :
		Animation[0] = LoadGraph("Resource/Images/EnemyBullet/eff1.png");
		Animation[1] = LoadGraph("Resource/Images/EnemyBullet/eff2.png");
		Animation[2] = LoadGraph("Resource/Images/EnemyBullet/eff3.png");
		if (Animation[0] == -1 || Animation[1] == -1 || Animation[2] == -1)
		{
			throw("エネミーのeffectがロードできてません");
		}
		image = Animation[0];
		break;

		break;
	case Bom_Number :
		Animation[0] = LoadGraph("Resource/Images/Blast/1.png");
		Animation[1] = LoadGraph("Resource/Images/Blast/2.png");
		Animation[2] = LoadGraph("Resource/Images/Blast/3.png");
		if (Animation[0] == -1|| Animation[1] == -1|| Animation[2] == -1)
		{
			throw("爆風がロードできてません");
		}
		image = Animation[0];
		break;
		
	default:
		break;
	}
}

void DeleteAnim::AnimationControl()
{
	AnimControl++;
	if (AnimControl > 30)
	{
		AnimControl = 0;
		int j = 0;
		while (j != 5)
		{
			if (image == Animation[j])
			{
				break;
			}
			j++;
		}
		if (j == 3)
		{
			DeleteClass(this);
		}
		else
		{
			image = Animation[++j];
		}
	}
}