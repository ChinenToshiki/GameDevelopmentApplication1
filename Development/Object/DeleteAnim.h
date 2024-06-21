#pragma once
#include"GameObject.h"
#include"ObjectControl.h"

class DeleteAnim :public ObjectControl
{
public:
	int Animation[5];
	int ObjectType;
	int AnimControl;

	DeleteAnim();
	~DeleteAnim();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual void GetObjectType(int type);

private:
	virtual void AnimationControl();
};