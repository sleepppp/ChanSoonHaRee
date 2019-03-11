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
	this->_hp = 20;
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
	//������Ʈ�� �浹
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

//�i�ų� �ǰݴ����� �� �����̱� ���� �Լ�.
//���Ŀ� �Ⱦ�� ����������
void Weeds::Move()
{
	//�i����� �߰��� ���� �ޱ۰����� �̵��� ���� ������
	if (_state == StateType::Chasing)
	{
		//�i������ �ޱ۰�.
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