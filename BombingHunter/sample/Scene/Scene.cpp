#include"Scene.h"
#include"../Utility/InputControl.h"
#include"../Object/Player/Player.h"
#include "../Object/Enemy/Enemy.h"
#include <DxLib.h>

Scene::Scene() :objects()
{

}

Scene::~Scene()
{
	Finalize();
}

void Scene::Initialize()
{
	CreateObject<Player>(Vector2D(320.0f, 50.0f));
}

void Scene::Update()
{
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			HitCheckObject(objects[i], objects[j]);
		}
	}		if (InputControl::GetKeyDown(KEY_INPUT_Z))
		{
			CreateObject<Enemy>(Vector2D(100.0f, 400.0f));
		}
}

void Scene::Draw() const
{
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

void Scene::Finalize()
{
	if (objects.empty())
	{
		return;
	}

	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	objects.clear();
}

#ifdef D_PIVOT_CENTER
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	Vector2D diff = a->GetLocation() - b->GetLocation();

	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#else
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	if((a->GetLocation().x<b_lower_right.x)&&
		(a->GetLocation().y<b_lower_right.y)&&
		(a_lower_right.x>b->GetLocation().x)&&
		(a_lower_right.y>b->GetLocation().y))
	{
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#endif //D_PIVOT_CENTER