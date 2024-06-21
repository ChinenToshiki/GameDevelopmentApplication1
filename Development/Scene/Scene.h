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



	//�����蔻��̃`�F�b�N����
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

	//�I�u�W�F�N�g���폜����template
	void DeleteObject(GameObject* deleteobject)
	{
		int i;
		GameObject* delete_object = dynamic_cast<GameObject*>(deleteobject);

		if (delete_object == nullptr)
		{
			delete delete_object;
			throw std::string("�Q�[���I�u�W�F�N�g�����ł��܂���ł���");
		}

		//�@(�I�u�W�F�N�g�̒��g�����Ĉ�v����) or �A(�I�u�W�F�N�g�̍Ō�)�܂Ń��[�v
		for (i = 0; i < objects.size(); i++)
		{
			if (delete_object == objects.at(i))
			{
				break;
			}
		}

		//��L�̂ǂ���̏����ŏI���������̊m�F:(�@ and �A)
		if (delete_object != objects.at(i) && i == objects.size())
		{
			throw("�I�u�W�F�N�g�̍폜���s�o���ł��B��蒼��^^");
		}

		//Finalize��ʂ��A�擪����i�Ԗ�(�폜����I�u�W�F�N�g)������
		delete_object->Finalize();
		objects.erase(objects.begin() + i);
	}
};