#include "stdafx.h"
#include "Weeds.h"
#include "Image.h"
#include "Enemy.h"
#include "Player.h"
#include "Golem.h"

Weeds::Weeds(Vector2 pos)
{
	this->_name = "Weeds";
	this->_position = pos;
	this->_size = Vector2(100, 100);
	this->_pivot = Pivot::CENTER;
	this->_renderRect = UpdateRect(_renderRect, _position, _size, _pivot);
	this->_speed = 70.0f;
	this->_hp = 100;
	this->_demage = 16;

	this->_state = StateType::Chasing;
}
Weeds::~Weeds() {}

void Weeds::Init() 
{
	Enemy::Init();
}

void Weeds::Release() {}

void Weeds::Update()
{
	this->Move();

	//RECT collisionRc;
	//if (IntersectRect(&collisionRc, &_renderRect, &_player->GetMainRect()))
	//{
	//	_state = StateType::attack;
	//}
	//else
	//	_state = StateType::Chasing;
	//this->_renderRect = UpdateRect(_renderRect, _position, _size, _pivot);
}
void Weeds::Render()
{
	_DXRenderer->DrawRectangle(_renderRect, DefaultBrush::red);
}