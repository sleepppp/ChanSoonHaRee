#include "stdafx.h"
#include "StaticObject.h"

StaticObject::StaticObject(string imagekey, Vector2 pos,float angle)
	:GameObject("TownObject", pos, Vector2(), Pivot::LEFT_TOP), _angle(angle)
{
	_image = _ImageManager->FindImage(imagekey);
	_size = _image->GetSize();
	this->UpdateMainRect();
}

StaticObject::~StaticObject()
{
}

void StaticObject::Release()
{
}

void StaticObject::Render()
{
	if (FLOAT_EQUAL(_angle, 0.f) == false)
	{
		_image->SetAngle(_angle);
	}
	_image->Render((int)_position.x, (int)_position.y, Pivot::LEFT_TOP, true);
}
