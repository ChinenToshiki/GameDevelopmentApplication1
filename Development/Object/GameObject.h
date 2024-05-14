#pragma once

#include"../Utility/Vector2D.h"

class GameObject
{
protected:
	Vector2D location;
	double scale;
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

};