#include "stdafx.h"
#include "Weeds.h"
#include "Image.h"
#include "Player.h"
#include "MoveItem.h"
#include "Effect.h"

Weeds::Weeds(Vector2 pos)
{
	this->_name = "Weeds";
	this->_position = pos;
	this->_size = Vector2(70, 70);
	this->_pivot = Pivot::CENTER;
	this->_renderRect = UpdateRect(_position, _size, _pivot);
	this->_speed = 70.0f;
	this->_hp = 40;
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
	//�κ��丮�� ������ ������ �����ӿ� ������ �ֱ� ���ؼ� �־���� �ݹ�޼���
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
	ObjectCollision();

	RECT collisionRc;
	if (IntersectRect(&collisionRc, &_renderRect, &_player->GetMainRect()))
	{
		_isAttack = true;
	}
	if (_isAttack)
	{
		_player->AttackedDamage(_damage);
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
//�κ��丮�� �¿����� �����ӿ� ������ �ַ��� ���� �Լ�.
void Weeds::InvenStop(bool stop)
{
	_isStop = stop;
}

void Weeds::AttackedDemege(int damage)
{
	_SoundManager->Play("Weeds_Hit", 0.6f);
	//������ �������� �Ѱ��ָ� ��������ŭ �� ü���� ��´�.
	_hp -= damage;
	//hp�� 0���� �۰ų� ������
	if (_hp <= 0)
	{
		//ī�޶� ����
		_Camera->Shake();

		//������ �Ѹ���
		SprayItemEnemy("item_brench");

		//����Ʈ : ����
		Effect::PlayEffect(EFFECT_BOOM, _position);

		_SoundManager->Play("enemyDeath", 1.0f);
		//�������. �ٸ� �״� ����� ������ ��� �����Լ� ����� ���ؼ� ������ �ٲ� ���� �ִ�.
		this->Destroy();
	}
	//���� �ʾҴٸ�
	else
	{
		//�ǰ��� ���ߴٴ� ������ Ʈ��� ����� �ְ�
		_attacked = true;

		//ī�޶� ����
		_Camera->Shake();

		//������ ��Ʈ ��¿�
		_DamageFontManager->ShowDamage(_position, damage);

		//�ڷ� �з�����. �÷��̾��� �ޱ��� ���� �־��ָ� ������ �߰��ϸ� ���⿡�� �ݴ�� �ޱ۰��� �����Ƿ� �ݴ�������� �з��� �� �ִ�.
		this->_attackedAngle = Math::GetAngle(_player->GetPosition().x, _player->GetPosition().y, _position.x, _position.y);
	}
}
