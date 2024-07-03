#pragma once

#include<vector>
#include<string>
#include"../Object/GameObject.h"

class Scene
{
private:
	std::vector<GameObject*> objects;
	//各種処理に必要な変数
	int BackGround;
	int EnemyCount;
	class Player* player;
	bool isFinish;
	//タイマー関係
	int Timer;
	int TimerCount;
	int TimerImage;
	//スコア関係
	int Score;
	int ScoreImage;
	int ScoreText[4];
	int NumberImage[10];
	int HightScoreImage;
	int EndText;


public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw()const;
	void Finalize();
	void ScoreUpdate(int HitScore);
	void DrawUI() const;
	void TimeCount();
	float SpawnRand();
	void DownEnemyCount();
	void DownTimer();

	void Finish();


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