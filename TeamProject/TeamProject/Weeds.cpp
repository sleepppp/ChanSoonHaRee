#include "stdafx.h"
#include "Weeds.h"
#include "Image.h"
#include "Player.h"
#include "MoveItem.h"


Weeds::Weeds(Vector2 pos)
{
	this->_name = "Weeds";
	this->_position = pos;
	this->_size = Vector2(70, 70);
	this->_pivot = Pivot::CENTER;
	this->_renderRect = UpdateRect(_position, _size, _pivot);
	this->_speed = 70.0f;
	this->_hp = 100;
	this->_damage = 16;
	this->_isAttack = false;
	this->_state = StateType::Chasing;
	this->_attackTime = 0.f;

	this->_weeds = _ImageManager->FindImage("weeds");
	this->_weeds_Red = _ImageManager->FindImage("weeds_Red");
	this->_weeds_White = _ImageManager->FindImage("weeds_White");

	this->_shadow = _ImageManager->FindImage("shadow");

	this->_imageCount = 0;
	this->_count = 0;
	this->_isStop = false;

	this->_moveCount = 0;
	this->_countMove = 0;
	//인벤토리가 열리고 닫힐때 움직임에 제한을 주기 위해서 넣어놓은 콜백메세지
	this->AddCallbackMessage("InventoryOpen", [this](TagMessage message) {this->InvenStop(1); });
	this->AddCallbackMessage("InventoryClose", [this](TagMessage message) {this->InvenStop(0); });
}
Weeds::~Weeds() {}

void Weeds::Init() 
{
	Enemy::Init();
}

void Weeds::Release() {}

void Weeds::Update()
{
	_countMove += _TimeManager->DeltaTime();
	if (_countMove >= 1.f / 6.0f)
	{
		_countMove = 0;
		_moveCount++;
	}
	if (!_isStop)
	{
		this->Move();
	}
	Collision();

	RECT collisionRc;
	if (IntersectRect(&collisionRc, &_renderRect, &_player->GetMainRect()))
	{
		_isAttack = true;
	}
	if (_isAttack)
	{
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

	this->_renderRect = UpdateRect(_position, _size, _pivot);

}
void Weeds::Render()
{
	_shadow->SetSize(_shadow->GetFrameSize(0));
	_shadow->SetAlpha(0.4f);
	_shadow->SetScale(0.66f);
	_shadow->Render(_position.x - 4, _position.y + 15, Pivot::CENTER, true);

	_weeds->SetSize(_weeds->GetFrameSize(0));
	_weeds->SetScale(0.9f);	
	_weeds->FrameRender(_position.x, _position.y, _imageCount, 0, Pivot::CENTER, true);
	if (_attacked)
	{
		_weeds_Red->SetSize(_weeds->GetFrameSize(0));
		_weeds_Red->SetScale(0.9f);
		if (_attackedColor == false)
		{
			_weeds_Red->FrameRender(_position.x, _position.y, _imageCount, 0, Pivot::CENTER, true);
		}
		_weeds_White->SetSize(_weeds->GetFrameSize(0));
		_weeds_White->SetScale(0.9f);
		if (_attackedColor == true)
		{
			_weeds_White->FrameRender(_position.x, _position.y, _imageCount, 0, Pivot::CENTER, true);
		}
	}
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
	const vector <class GameObject*>* object;
	object = _ObjectManager->GetObjectListPointer(ObjectType::Object);
	for (int i = 0; i < (*object).size(); i++)
	{
		Player* player = dynamic_cast<Player*>((*object)[i]);
		MoveItem* item = dynamic_cast<MoveItem*>((*object)[i]);
		if (player == nullptr && this != (*object)[i] && item == nullptr)
		{
			if (this->IntersectReaction(&_renderRect, &(*object)[i]->GetCollisionRect()))
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
		_attackTime++;
		if (_attackTime > 100)
		{
			_attackTime = 0.f;
		}
		_count += _TimeManager->DeltaTime();
		if (_count <= 0.5f)
		{
			this->_position.x += cosf(_attackedAngle) * _speed * _TimeManager->DeltaTime()* 3.f;
			this->_position.y += -sinf(_attackedAngle) * _speed * _TimeManager->DeltaTime()* 3.f;
			this->_renderRect = UpdateRect(_position, _size, Pivot::CENTER);

			if (_attackTime <= 70.f)
			{
				_attackedColor = false;
			}
			if (_attackTime > 70.f)
			{
				_attackedColor = true;
			}
		}
		if (_count > 0.5f)
		{
			_attacked = false;
			_count = 0.f;
		}
	}


}
//인벤토리의 온오프시 움직임에 제한을 주려고 만든 함수.
void Weeds::InvenStop(bool stop)
{
	_isStop = stop;
}
