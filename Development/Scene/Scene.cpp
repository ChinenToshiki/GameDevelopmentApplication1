#include"Scene.h"

#include"../Object/Player/Player.h"
#include "../Object/Enemy/Enemy.h"

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
	CreateObject<Enemy>(Vector2D(0.0f, 400.0f));
}

void Scene::Update()
{
	for (GameObject* obj : objects)
	{
		obj->Update();
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