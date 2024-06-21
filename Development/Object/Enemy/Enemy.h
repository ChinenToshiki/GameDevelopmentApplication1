#pragma once

#include"../GameObject.h"
#include"../../Utility/Vector2D.h"
#include"../Player/Player.h"
#include"Bullet.h"
#include"../../Scene/Scene.h"
#include"../ObjectControl.h"

class Enemy : public ObjectControl
{
private:

	int animation[5];
	int animation_count;
	Vector2D direction;
	Player* player;
	int EnemyType;
	float speed;
	bool isShot;

public:
	Enemy();
	~Enemy();

	static float GetLocation();
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;
	void SetBL(Vector2D location);



	virtual void OnHitCollision(GameObject* hit_object)override;

	void SetPlayer(class Player* player);
private:
	void Movement();
	void AnimationControl();
	void Shot();


};