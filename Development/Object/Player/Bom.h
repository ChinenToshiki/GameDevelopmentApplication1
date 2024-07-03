#pragma once

#include"../../Utility/Vector2D.h"
#include"Player.h"
#include"../ObjectControl.h"
class Bom : public ObjectControl
{
private:
	float speed;
	int Anim;
	bool isShot;
	bool dele;
	int sound;

public:
	Bom();
	~Bom();

	virtual void Initialize()override;
	virtual void Finalize()override;
	virtual void Update()override;
	virtual void Draw()const override;
	virtual void Movement();
	virtual void Shot();

	virtual void OnHitCollision(GameObject* hit_object)override;


	float GetSpeed();
	Vector2D GetLocation();

};

