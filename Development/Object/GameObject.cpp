#include"GameObject.h"
#include "../Scene/Scene.h"
#include"DxLib.h"

GameObject::GameObject() 
	:location(0.0f), 
	box_size(0.0), 
	radian(0.0), 
	image(NULL), 
	sound(NULL),
	scene(nullptr),
	Hit_now(false),
	Number(-1)
{
}

GameObject::~GameObject()
{

}

void GameObject::Initialize()
{

}

void GameObject::Update()
{

}

void GameObject::Draw()const
{
#ifdef D_PIVOT_CENTER
	Vector2D tl = location - (box_size / 2.0f);
	Vector2D br = location + (box_size / 2.0f);

	DrawBoxAA(tl.x, tl.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#else
	Vector2D tl = location;
	Vector2D br = location + box_size;

	DrawBoxAA(tl.x, tl.y, br.x, br.y, GetColor(255, 0, 0), FALSE);
#endif // D_PIVOT_CENTER

}

void GameObject::Finalize()
{
}
void GameObject::OnHitCollision(GameObject* hit_object)
{
	//“–‚½‚Á‚½‚ç
}

int GameObject::GetNuber() const
{
	return Number;
}

bool GameObject::GetHitNow() const
{
	return Hit_now;
}

void GameObject::ChangeHitNow(bool IsHit)
{
	Hit_now = IsHit;

}

Vector2D GameObject::GetLocation() const
{
	return this->location;
}

void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}

void GameObject::SetScene(Scene* scene)
{
	this->scene = scene;
}

Vector2D GameObject::GetBoxSize() const
{
	return box_size;
}