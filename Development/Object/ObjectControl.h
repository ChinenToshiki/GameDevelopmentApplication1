#pragma once
#include "../Scene/Scene.h"
#include"GameObject.h"

class ObjectControl : public GameObject
{
	protected:

		//�I�u�W�F�N�g���쐬����template���Ăяo�����c
		template <class T>
		T* CreateObject(const Vector2D& location)
		{
			return scene->CreateObject<T>(location);
		}

	protected:

		//�I�u�W�F�N�g���폜����template���Ăяo�����c
		void DeleteClass(GameObject* deleteobject)
		{
			scene->DeleteObject(deleteobject);
		}

		/*	//�Ȃ����̂悤�Ȍ`���Ƃ������Ƃ����ƁA
	//������������CreateClass��Scene�ȊO�ł̌Ăяo����Ή����ĂȂ�
	//����͂��̂悤�ɁA�V�[���̏����m�ۂ��āA
	//���̃N���X����Ȃ���CreateClass�֐G��Ȃ��悤�ɂ���
	//�ێ琫�����߂��B*/
};