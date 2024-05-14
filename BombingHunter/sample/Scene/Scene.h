#pragma once

#include<vector>
#include<string>
#include"../Object/GameObject.h"

class Scene
{
private:
	std::vector<GameObject*>objects;

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw()const;
	void Finalize();

private:

	//�����蔻��̃`�F�b�N����
	void HitCheckObject(GameObject* a, GameObject* b);

	template <class T>
	T* CreateObject(const Vector2D& location)
	{
		T* new_instance = new T();
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("�Q�[���I�u�W�F�N�g�𐶐��ł��܂���ł���");
		}
		new_object->Initialize();
		new_object->SetLocation(location);
		objects.push_back(new_object);
		return new_instance;
	}
};