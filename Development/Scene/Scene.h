#pragma once

#include<vector>
#include<string>
#include"../Object/GameObject.h"

class Scene
{
private:
	std::vector<GameObject*> objects;
	int BackGround;
	class Player* player;
	class Bom* bom;
	class Enemy* enemy;
	int Timer;
	int Score;

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw()const;
	void Finalize();



	//当たり判定のチェック処理
	void HitCheckObject(GameObject* a, GameObject* b);


	
	template <class T>
	T* CreateObject(const Vector2D& location)
	{
		T* new_instance = new T();
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);
		if (new_object == nullptr)
		{
			throw std::string("FUCK YOU!!");
		}

		new_object->SetScene(this);
		new_object->SetLocation(location);
		new_object->Initialize();

		objects.push_back(new_object);

		return new_instance;
	}

	//オブジェクトを削除するtemplate
	void DeleteObject(GameObject* deleteobject)
	{
		int i;
		GameObject* delete_object = dynamic_cast<GameObject*>(deleteobject);

		if (delete_object == nullptr)
		{
			delete delete_object;
			throw std::string("ゲームオブジェクトを特定できませんでした");
		}

		//①(オブジェクトの中身を見て一致する) or ②(オブジェクトの最後)までループ
		for (i = 0; i < objects.size(); i++)
		{
			if (delete_object == objects.at(i))
			{
				break;
			}
		}

		//上記のどちらの条件で終了したかの確認:(① and ②)
		if (delete_object != objects.at(i) && i == objects.size())
		{
			throw("オブジェクトの削除が不出来です。やり直し^^");
		}

		//Finalizeを通し、先頭からi番目(削除するオブジェクト)を消す
		delete_object->Finalize();
		objects.erase(objects.begin() + i);
	}
};