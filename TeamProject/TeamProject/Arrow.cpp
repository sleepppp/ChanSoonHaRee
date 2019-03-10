#include "stdafx.h"
#include "Arrow.h"
#include "Image.h"
//#include "Animation.h"
#include "Timer.h"
#include "Player.h"

Arrow::Arrow(Vector2 pos)
{
	this->_name = "arrow";
	this->_size = Vector2(10, 52);
	this->_position = pos;
	this->_speed = 20.0f;
	this->_damage = 20.f;	
	
	_ImageManager->AddImage("arrow_left", L"../Resources/Player/arrow_left.png");
	this->_imgArrow_left = _ImageManager->FindImage("arrow_left");
	_ImageManager->AddImage("arrow_right", L"../Resources/Player/arrow_right.png");
	this->_imgArrow_right = _ImageManager->FindImage("arrow_right");
	_ImageManager->AddImage("arrow_up", L"../Resources/Player/arrow_up.png");
	this->_imgArrow_up = _ImageManager->FindImage("arrow_up");
	_ImageManager->AddImage("arrow_down", L"../Resources/Player/arrow_down.png");
	this->_imgArrow_down = _ImageManager->FindImage("arrow_down");
}

Arrow::~Arrow()
{
}

void Arrow::Init()
{
}

void Arrow::Release()
{
}

void Arrow::Update()
{
	this->_mainRect = Figure::RectMakeCenter(_position, _size);	
	
	_player->GetState();
	switch (_state)
	{
	case Arrow::State::Left:
		_position.x -= _position.x*_speed;
		break;
	case Arrow::State::Right:
		_position.x += _position.x*_speed;
		break;
	case Arrow::State::Up:
		_position.y -= _position.y*_speed;
		break;
	case Arrow::State::Down:
		_position.y += _position.y*_speed;
		break;
	}
	
	if (_mainRect.right<0 || _mainRect.left>WinSizeX || _mainRect.bottom < 0 || _mainRect.top < WinSizeY)
	{

	}
}

void Arrow::Render()
{
	switch (_state)
	{
	case Arrow::State::Left:
		this->_size = Vector2(10, 52);
		_imgArrow_left->Render(_position.x, _position.y);
		break;
	case Arrow::State::Right:
		this->_size = Vector2(10, 52);
		_imgArrow_right->Render(_position.x, _position.y);
		break;
	case Arrow::State::Up:
		this->_size = Vector2(52, 10);
		_imgArrow_up->Render(_position.x, _position.y);
		break;
	case Arrow::State::Down:
		this->_size = Vector2(52, 10);
		_imgArrow_down->Render(_position.x, _position.y);
		break;
	}

	if (_isDebug)
	{
		_DXRenderer->DrawRectangle(_mainRect, DefaultBrush::red, true);
	}	
}