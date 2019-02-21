#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::Init()
{
	this->name = "Enemy";
	this->position = Vector2(WinSizeX - 300, WinSizeY / 2);
	this->size = Vector2(100, 100);
	this->pivot = Pivot::CENTER;
	this->UpdateRect();
}

void Enemy::Release()
{

}

void Enemy::Update()
{

}

void Enemy::Render()
{
	_DXRenderer->FillRectangle(rc, DefaultBrush::red, true);
}