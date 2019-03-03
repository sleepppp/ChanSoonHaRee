#include "stdafx.h"
#include "TownObject.h"

TownObject::TownObject(string imagekey, Vector2 pos)
	:GameObject("TownObject", pos, Vector2(), Pivot::LEFT_TOP)
{
	_image = _ImageManager->FindImage(imagekey);
	_size = _image->GetSize();
	this->UpdateMainRect();
}

TownObject::~TownObject()
{
}

void TownObject::Init()
{

}

void TownObject::Release()
{
}

void TownObject::Render()
{
	_image->Render((int)_position.x, (int)_position.y, Pivot::LEFT_TOP, true);

	if (_isDebug)
		_DXRenderer->DrawRectangle(_mainRect, DefaultBrush::red, true,1.0f);
}
