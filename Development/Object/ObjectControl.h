#pragma once
#include "../Scene/Scene.h"
#include"GameObject.h"

class ObjectControl : public GameObject
{
	protected:

		//オブジェクトを作成するtemplateを呼び出すヤツ
		template <class T>
		T* CreateObject(const Vector2D& location)
		{
			return scene->CreateObject<T>(location);
		}

	protected:

		//オブジェクトを削除するtemplateを呼び出すヤツ
		void DeleteClass(GameObject* deleteobject)
		{
			scene->DeleteObject(deleteobject);
		}

		/*	//なぜこのような形をとったかというと、
	//そもそもこのCreateClassはScene以外での呼び出しを対応してなく
	//今回はこのように、シーンの情報を確保して、
	//このクラスを介さないとCreateClassへ触れないようにして
	//保守性を高めた。*/
};