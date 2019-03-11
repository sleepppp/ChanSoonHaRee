#include "stdafx.h"
#include "Rock.h"
#include "Image.h"

Rock::Rock(Vector2 pos)
{
	_name = "Rock";
	_position = pos;
	_size = Vector2(70,70);
	_pivot = Pivot::CENTER;
	this->UpdateMainRect();
	_rock = _ImageManager->FindImage("rock");
}


Rock::~Rock()
{
}

void Rock::Init()
{

}
void Rock::Release()
{
}

void Rock::Update()
{
}
void Rock::Render()
{
	_rock->SetSize(_size);
	_rock->Render(_position.x, _position.y, _pivot, true);
	if(_isDebug == true)
	{
		_DXRenderer->DrawRectangle(_mainRect, DefaultBrush::blue, true);
	}
}