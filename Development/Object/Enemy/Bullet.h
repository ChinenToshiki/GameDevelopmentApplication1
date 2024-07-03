#pragma once

#include"../../Utility/Vector2D.h"
#include"Enemy.h"
#include"../ObjectControl.h"
class Bullet : public ObjectControl
{
private:
	float speed;
	int BulletAnim[4];
	Vector2D Player_location;
	bool isShot;
	int Sound;

public:
	Bullet();
	~Bullet();

	void Shot(Vector2D location);
	virtual void SetLocation(Vector2D location,Vector2D loc);
	virtual void OnHitCollision(GameObject* hit_object) override;
	virtual void Initialize()override;
	virtual void Finalize()override;
	virtual void Update()override;
	virtual void Draw()const override;
	virtual void Movement();
	virtual void Shot();

	float GetSpeed();

};

