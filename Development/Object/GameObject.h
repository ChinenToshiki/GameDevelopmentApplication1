#pragma once

#include"../Utility/Vector2D.h"

#define D_PIVOT_CENTER
#define Player_Number 0
#define Enemy_Number 1
#define Bullet_Number 2
#define Bom_Number 3

class GameObject
{
protected:
	Vector2D location;
	Vector2D box_size;
	double radian;
	int image;
	int sound;
	class Scene* scene;
	int Number;
	bool Hit_now;

public:
	GameObject();
	virtual ~GameObject();
	virtual void Initialize();
	virtual void Update();
	virtual void Draw() const;
	virtual void Finalize();

	virtual void OnHitCollision(GameObject* hit_object);

	virtual int GetNuber() const;
	virtual bool GetHitNow() const;
	virtual void ChangeHitNow(bool IsHit);
	Vector2D GetLocation()const;
	void SetLocation(const Vector2D& location);
	void SetScene(class Scene* scene);

	Vector2D GetBoxSize() const;
};