#include "stdafx.h"
#include "Arrow.h"
#include "Image.h"
#include "Enemy.h"
#include "Effect.h"
//#include "Animation.h"
//#include "Timer.h"
//#include "Player.h"

Arrow::Arrow(Vector2 pos, State state)
{
	this->_name = "arrow";
	this->_size = Vector2(10, 52);
	this->_position = pos;
	this->_speed = 400.0f;
	this->_damage = 20.f;		
	this->_state = state;
	
	_ImageManager->AddImage("arrow_left", L"../Resources/Player/arrow_left.png");
	this->_imgArrow_left = _ImageManager->FindImage("arrow_left");
	_ImageManager->AddImage("arrow_right", L"../Resources/Player/arrow_right.png");
	this->_imgArrow_right = _ImageManager->FindImage("arrow_right");
	_ImageManager->AddImage("arrow_up", L"../Resources/Player/arrow_up.png");
	this->_imgArrow_up = _ImageManager->FindImage("arrow_up");
	_ImageManager->AddImage("arrow_down", L"../Resources/Player/arrow_down.png");
	this->_imgArrow_down = _ImageManager->FindImage("arrow_down");
	//_mainRect = Figure::RectMakeCenter(_position, _size);
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
	
	switch (_state)
	{
	case Arrow::State::Left:
		_position.x -= _speed * _TimeManager->DeltaTime();
		_size = Vector2(52,10);
		this->_mainRect = Figure::RectMakeCenter(_position, _size);
		break;
	case Arrow::State::Right:
		_position.x += _speed * _TimeManager->DeltaTime();
		_size = Vector2(52, 10);
		this->_mainRect = Figure::RectMakeCenter(_position, _size);
		break;
	case Arrow::State::Up:
		_position.y -= _speed * _TimeManager->DeltaTime();
		_size = Vector2(10, 52);
		this->_mainRect = Figure::RectMakeCenter(_position, _size);
		break;
	case Arrow::State::Down:
		_position.y += _speed * _TimeManager->DeltaTime();
		_size = Vector2(10, 52);
		this->_mainRect = Figure::RectMakeCenter(_position, _size);
		break;
	}
	RECT renderRc = _Camera->GetRelativeRect(_mainRect);
	if (renderRc.left > WinSizeX + 100 || renderRc.right < -100 ||
		renderRc.top > WinSizeY + 100 || renderRc.bottom < -100)
	{
		this->Destroy();
	}
	
}

void Arrow::Render()
{
	switch (_state)
	{
	case Arrow::State::Left:
		this->_size = Vector2(10, 52);
		_imgArrow_left->Render(_position.x, _position.y,Pivot::CENTER,true);
		break;
	case Arrow::State::Right:
		this->_size = Vector2(10, 52);
		_imgArrow_right->Render(_position.x, _position.y, Pivot::CENTER, true);
		break;
	case Arrow::State::Up:
		this->_size = Vector2(52, 10);
		_imgArrow_up->Render(_position.x, _position.y, Pivot::CENTER, true);
		break;
	case Arrow::State::Down:
		this->_size = Vector2(52, 10);
		_imgArrow_down->Render(_position.x, _position.y, Pivot::CENTER, true);
		break;
	}
	if (_isDebug)
	{
		_DXRenderer->DrawRectangle(_mainRect, DefaultBrush::red, true);
	}	
}



//===================================
//화살 충돌 함수
//===================================
void Arrow::ArrowAttack()
{
	const vector<class GameObject*>* object;
	object = _ObjectManager->GetObjectListPointer(ObjectType::Object);

	for (UINT i = 0; i < object->size(); ++i)
	{
		if (object->at(i)->GetName() != this->_name)
		{
			Enemy* enemy = dynamic_cast<Enemy*>(object->at(i));

			if (enemy == nullptr)
			{
				RECT temp;
				if(IntersectRect(&temp, &_mainRect, &object->at(i)->GetCollisionRect()))
				{
					//데미지 값을 넘겨준다
					enemy->AttackedDemege(this->_damage);
					Effect::PlayEffect(EFFECT_SWORDATK, Vector2(_mainRect.left, _mainRect.top));
				}
			}


		}
	}


}

