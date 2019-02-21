#include "stdafx.h"
#include "GameObject.h"

using namespace Figure;

//¸â¹ö ÀÌ´Ï¼È¶óÀÌÁî 
GameObject::GameObject()
	:pivot(Pivot::LEFT_TOP),position(0.f,0.f),size(0.f,0.f),isActive(true),isLive(true)
{
	this->UpdateRect();
}


GameObject::~GameObject()
{
}

void GameObject::SetPosition(Vector2 pos)
{
	this->position = pos;
	this->UpdateRect();
}

void GameObject::SetSize(Vector2 size)
{
	this->size = size;
	this->UpdateRect();
}

void GameObject::SetPivot(Pivot::Enum pivot)
{
	this->pivot = pivot;
	this->UpdateRect();
}

void GameObject::UpdateRect()
{
	switch (pivot)
	{
	case Pivot::LEFT_TOP:
		this->rc = RectMake(position.x, position.y, size.x, size.y);
		break;
	case Pivot::CENTER:
		this->rc = RectMakeCenter(position.x, position.y, size.x, size.y);
		break;
	case Pivot::BOTTOM:
		this->rc = RectMakeBottom(position.x, position.y, size.x, size.y);
		break;
	default:
		break;
	}
}
