#include "stdafx.h"
#include "player.h"


void player::Init()
{
	this->_position = Vector2(WinSizeX / 2, WinSizeY / 2);
	this->_size = Vector2(50, 50);
	this->_speed = 200.0f;
	_pivot = Pivot::CENTER;
	this->UpdateMainRect();
}

void player::Release()
{
}

void player::Update()
{
	this->PlayerMove();
	this->UpdateMainRect();
}

void player::Render()
{
	_DXRenderer->DrawRectangle(_mainRect, DefaultBrush::blue);
}

void player::PlayerMove()
{
	if (_Input->GetKey(VK_LEFT))
	{
		this->_position.x -= _speed*  _TimeManager->DeltaTime();
		this->UpdateMainRect();
	}
	if (_Input->GetKey(VK_RIGHT))
	{
		this->_position.x += _speed * _TimeManager->DeltaTime();
		this->UpdateMainRect();
	}
	if (_Input->GetKey(VK_UP))
	{
		this->_position.y -= _speed * _TimeManager->DeltaTime();
		this->UpdateMainRect();
	}
	if (_Input->GetKey(VK_DOWN))
	{
		this->_position.y += _speed * _TimeManager->DeltaTime();
		this->UpdateMainRect();
	}

}

player::player()
{
	_name = "player";
}


player::~player()
{
}
