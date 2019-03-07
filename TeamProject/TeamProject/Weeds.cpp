#include "stdafx.h"
#include "Weeds.h"
#include "Image.h"
#include "Player.h"

Weeds::Weeds(Vector2 pos)
{
	this->_name = "Weeds";
	this->_position = pos;
	this->_size = Vector2(70, 70);
	this->_pivot = Pivot::CENTER;
	this->_renderRect = UpdateRect(_position, _size, _pivot);
	this->_speed = 70.0f;
	this->_hp = 100;
	this->_demage = 16;
	this->_isAttack = false;
	this->_state = StateType::Chasing;

	this->_weeds = _ImageManager->AddFrameImage("weeds", L"../Resources/Enemy/Weeds/Weeds.png", 12, 1);
	this->_imageCount = 0;
	this->_count = 0;
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

	Collision();

	RECT collisionRc;
	if (IntersectRect(&collisionRc, &_renderRect, &_player->GetMainRect()))
	{
		_isAttack = true;
	}
	if (_isAttack)
	{
		this->AttackedDemege(0);
		_isAttack = false;
	}
	if (!_isAttack)
	{
		_state = StateType::Chasing;
	}

	_count += _TimeManager->DeltaTime();
	if (_count >= 1.f / 2.0f)
	{
		_count = 0;
		_imageCount++;
	}
	if (_imageCount >= 12)
	{
		_imageCount = 0;
	}

	if (_Input->GetKeyDown('0'))
	{
		this->AttackedDemege(0);
	}

	this->_renderRect = UpdateRect(_position, _size, _pivot);

}
void Weeds::Render()
{
	_weeds->SetSize(_weeds->GetFrameSize(0));
	_weeds->SetScale(0.9f);	
	_weeds->FrameRender(_position.x, _position.y, _imageCount, 0, Pivot::CENTER, true);
	if (_isDebug)
	{
		_DXRenderer->DrawRectangle(_renderRect, DefaultBrush::red, true);
	}
}

void Weeds::Collision()
{
	//=======================================
	//오브젝트와 충돌
	//=======================================
	vector <class GameObject*> object;
	object = _ObjectManager->GetObjectList(ObjectType::Object);
	for (int i = 0; i < object.size(); i++)
	{
		if (object[i]->GetName() != this->_name)
		{
			if (this->IntersectReaction(&_renderRect, &object[i]->GetCollisionRect()))
			{
				_position.x = (_renderRect.right - _renderRect.left) / 2 + _renderRect.left;
				_position.y = (_renderRect.bottom - _renderRect.top) / 2 + _renderRect.top;
				this->_renderRect = UpdateRect(_position, _size, _pivot);
			}
		}
	}
}

//쫒거나 피격당했을 시 움직이기 위한 함수.
//아파요 싫어요 하지마세요
void Weeds::Move()
{
	//쫒을대상 추격을 위한 앵글값계산과 이동을 위한 변수들
	if (_state == StateType::Chasing)
	{
		//쫒기위한 앵글값.
		this->_angle = Math::GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
		this->_position.x += cosf(_angle) * _speed * _TimeManager->DeltaTime();
		this->_position.y += -sinf(_angle)*_speed * _TimeManager->DeltaTime();
		this->_renderRect = UpdateRect(_position, _size, Pivot::CENTER);
	}

	if (_attacked)
	{
		_count += _TimeManager->DeltaTime();
		if (_count <= 0.5f)
		{
			this->_position.x += cosf(_attackedAngle) * _speed * _TimeManager->DeltaTime()* 3.f;
			this->_position.y += -sinf(_attackedAngle) * _speed * _TimeManager->DeltaTime()* 3.f;
			this->_renderRect = UpdateRect(_position, _size, Pivot::CENTER);
		}
		if (_count > 0.5f)
		{
			_attacked = false;
			_count = 0.f;
		}
	}


}