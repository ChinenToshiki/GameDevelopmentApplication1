#pragma once

#include"../ObjectControl.h"

class Player : public ObjectControl
{
private:
	int animation[2];
	int animation_count;
	int flip_flag;

public:
	Player();
	~Player();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;
	
	virtual void OnHitCollision(GameObject* hit_object)override;
	
	virtual Vector2D GetLocation();

private:
	void Movement();
	void AnimationControl();

};