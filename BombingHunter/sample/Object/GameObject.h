#pragma once

#include"../Utility/Vector2D.h"

#define D_PIVOT_CENTER

class GameObject
{
protected:
	Vector2D location;
	Vector2D box_size;
	double radian;
	int image;
	int sound;

public:
	GameObject();
	virtual ~GameObject();
	virtual void Initialize();
	virtual void Update();
	virtual void Draw() const;
	virtual void Finalize();

	virtual void OnHitCollision(GameObject* hit_object);

	Vector2D GetLocation()const;
	void SetLocation(const Vector2D& location);

	Vector2D GetBoxSize() const;
};