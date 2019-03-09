#include "stdafx.h"
#include "Image.h"
#include "Player.h"
#include "MoveItem.h"
#include "Golem.h"


Golem::Golem(Vector2 pos)
{
	//���ʹ��� �ڽ��ڽ� �⺻ ����.
	this->_name = "Golem";					//���̸��� ���̿�
	this->_position = pos;					//
	this->_size = Vector2(100, 100);		//ũ�⵵ 100, 100�̾�
	this->_pivot = Pivot::CENTER;			//�� ������ �߽ɿ��־�
	this->_speed = 90.0f;					//�ӵ��� 90.0f
	this->_hp = 200;						//200�� ü��
	this->_demage = 34;						//34�� ����

	this->_isAttack = false;				//������ ó������ ���ϰ�����
	bool _attackedColor = false;
	this->_renderRect = UpdateRect(_position, _size, Pivot::CENTER);

	//�� �̹��� ã��!
	this->_golemMove = _ImageManager->AddFrameImage("GolemMove", L"../Resources/Enemy/Golem/GolemMove.png", 8, 4);
	this->_golemMove_Red = _ImageManager->AddFrameImage("GolemMove_Red", L"../Resources/Enemy/Golem/GolemMove_Red.png", 8, 4);
	this->_golemMove_white = _ImageManager->AddFrameImage("GolemMove_White", L"../Resources/Enemy/Golem/GolemMove_White.png", 8, 4);

	this->_golemAttack = _ImageManager->AddFrameImage("GolemAttack", L"../Resources/Enemy/Golem/GolemAttack.png", 13, 4);
	this->_golemAttack_Red = _ImageManager->AddFrameImage("GolemAttack_Red", L"../Resources/Enemy/Golem/GolemAttack_Red.png", 13, 4);
	this->_golemAttack_White = _ImageManager->AddFrameImage("GolemAttack_White", L"../Resources/Enemy/Golem/GolemAttack_White.png", 13, 4);

	this->_shadow = _ImageManager->AddImage("shadow", L"../Resources/Object/Shadow.png");
	//���� ī��Ʈ �ʱ�ȭ
	this->_moveCount = 0;
	this->_attackCount = 0;
	this->_attackedCount = 0;
	this->_countMove = 0.f;
	this->_countAttack = 0.f;
	//���� ��Ʈ�� ���� ������ �ʱ�ȭ
	this->_positionLeft = Vector2(_position.x - 110, _position.y - 10);
	this->_positionRight = Vector2(_position.x + 10, _position.y - 15);
	this->_positionTop = Vector2(_position.x, _position.y - 10);
	this->_positionBottom = Vector2(_position.x, _position.y + 110);
	//���� ��Ʈ�� ���� ������ ���� �� �ʱ�ȭ
	this->_sizeLeft = Vector2(100, 60);
	this->_sizeRight = Vector2(100, 60);
	this->_sizeTop = Vector2(60, 70);
	this->_sizeBottom = Vector2(60, 80);
	//���ݿ���Ȯ���� ���� �Һ��� �ʱ�ȭ
	this->_isAttackTop = false;
	this->_isAttackLeft = false;
	this->_isAttackRight = false;
	this->_isAttackBottom = false;
	this->AddCallbackMessage("InventoryOpen", [this](TagMessage message) {this->InvenStop(1); });
	this->AddCallbackMessage("InventoryClose", [this](TagMessage message) {this->InvenStop(0); });

	//���ݷ�Ʈ �ʱ�ȭ
	//this->_attackLeft = UpdateRect(_positionLeft, _sizeLeft, Pivot::LEFT_TOP);
	//this->_attackRight = UpdateRect(_positionRight, _sizeRight, Pivot::LEFT_TOP);
	//this->_attackTop = UpdateRect(_positionTop, _sizeTop, Pivot::BOTTOM);
	//this->_attackBottom = UpdateRect(_positionBottom, _sizeBottom, Pivot::BOTTOM);
}

Golem::~Golem()
{
}

void Golem::Init()
{
	Enemy::Init();
}

void Golem::Release()
{

}

void Golem::Update()
{
	_countMove +=_TimeManager->DeltaTime();
	if (_countMove >= 1.f /6.0f)
	{
		_countMove = 0;
		_moveCount++;
	}
	if (!_isStop)
	{
		this->Move();
		this->Attack();
	}
	this->EnemyMoveType();
	this->ImageCount();
	this->AttackPosition();
	this->Collision();
	this->ObjectCollision();

	if (_Input->GetKeyDown('0'))
	{
		this->AttackedDemege(0);
	}
}

void Golem::Render()
{
	this->RectRender();
	this->ImageRender();
}

//������ ������ ���� �Լ�.
void Golem::ImageCount()
{
	//�̹��� �����ӵ�����(�i�»���)
	if (_state == StateType::Chasing)
	{
		if (_moveCount >= 8)
			_moveCount = 0;
	}

	//�̹��� ������ ������ (���ݻ���)
	if (_state == StateType::attack)
	{
		if (_attackCount > 14)
			_attackCount = 0;
	}
}

//���� ��Ÿ��� ����ϱ� ���ؼ� �����Ÿ���� �� ���� ���� ���ϰ�� ���� ����
void Golem::Attack()
{
	_distance = Math::GetDistance(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

	if (_distance < (_size.x * 1.2f))
	{
		_state = StateType::attack;
	}
	if (_state == StateType::attack)
	{
		_countAttack +=_TimeManager->DeltaTime();
		if (_countAttack >= 1.f / 8.0f)
		{
			_countAttack = 0;
			_attackCount++;
		}
	}
	if (_attackCount > 12)
	{
		_attackCount = 0;
		_state = StateType::Chasing;
	}
}

void Golem::AttackPosition()
{
	this->_positionLeft = Vector2(_position.x - 110, _position.y - 10);
	this->_positionRight = Vector2(_position.x + 10, _position.y - 15);
	this->_positionTop = Vector2(_position.x, _position.y - 10);
	this->_positionBottom = Vector2(_position.x, _position.y + 110);

	if (_state == StateType::attack)
	{
  		if (_move == MoveType::Left && _attackCount > 9)
		{
			this->_isAttackLeft = true;
			this->_attackLeft = UpdateRect(_positionLeft, _sizeLeft, Pivot::LEFT_TOP);
		}
		else _isAttackLeft = false;

		if (_move == MoveType::Right && _attackCount > 9)
		{
			this->_isAttackRight = true;
			this->_attackRight = UpdateRect(_positionRight, _sizeRight, Pivot::LEFT_TOP);
		}
		else _isAttackRight = false;
		if (_move == MoveType::Top && _attackCount > 9)
		{
			this->_isAttackTop = true;
			this->_attackTop = UpdateRect(_positionTop, _sizeTop, Pivot::BOTTOM);
		}
		else _isAttackTop = false;
		if (_move == MoveType::Bottom && _attackCount > 9)
		{
			this->_isAttackBottom = true;
			this->_attackBottom = UpdateRect(_positionBottom, _sizeBottom, Pivot::BOTTOM);
		}
		else _isAttackBottom = false;
	}
}

void Golem::AttackRender()
{
	if (_state == StateType::attack)
	{
		if (this->_isAttackLeft == true)
		{
			_DXRenderer->DrawRectangle(_attackLeft, DefaultBrush::yello, true);
		}
		if (this->_isAttackRight == true)
		{
			_DXRenderer->DrawRectangle(_attackRight, DefaultBrush::yello, true);
		}
		if (this->_isAttackTop == true)
		{
			_DXRenderer->DrawRectangle(_attackTop, DefaultBrush::yello, true);
		}
		if (this->_isAttackBottom == true)
		{
			_DXRenderer->DrawRectangle(_attackBottom, DefaultBrush::yello, true);
		}
	}
}

void Golem::Collision()
{
	RECT CollisionRc = { 0 };
	if (this->_isAttackLeft == true)
	{
		if (IntersectRect(&CollisionRc, &_attackLeft, &_player->GetCollisionRect()))
		{
			_isAttack = true;
		}
	}
	if (this->_isAttackRight == true)
	{
		if (IntersectRect(&CollisionRc, &_attackRight, &_player->GetCollisionRect()))
		{
			_isAttack = true;
		}
	}
	if (this->_isAttackTop == true)
	{
		if (IntersectRect(&CollisionRc, &_attackTop, &_player->GetCollisionRect()))
		{
			_isAttack = true;
		}
	}
	if (this->_isAttackBottom == true)
	{
		if (IntersectRect(&CollisionRc, &_attackBottom, &_player->GetCollisionRect()))
		{
			_isAttack = true;
		}
	}
	if (IntersectRect(&CollisionRc, &_renderRect, &_player->GetCollisionRect()))
	{
		_isAttack = true;
	}

	//�����ϰ� �ִ� ��Ȳ�̰�
	if (_state == StateType::attack)
	{
		//�׸��� ���ݿ� ����������
		if (_isAttack == true)
		{
			//�� ������ �Ѱ����.
			_player->AttackedDamage(_demage);
			//������ �Ϸ� ������ �������� �ִ� ������ �޽����Ѷ�.
			_isAttack = false;

			_isAttackLeft = false;
			_isAttackRight = false;
			_isAttackTop = false;
			_isAttackBottom = false;
		}
	}
}

void Golem::RectRender()
{
	if (_isDebug == true)
	{
		_DXRenderer->DrawRectangle(_renderRect, DefaultBrush::gray, true);
		if (_state == StateType::Chasing)
		{
			_DXRenderer->DrawEllipse(_position, (_size.x * 1.2f), DefaultBrush::blue, true);
		}
		if (_state == StateType::attack)
		{
			_DXRenderer->DrawEllipse(_position, (_size.x * 1.2f), DefaultBrush::red, true);
		}
		this->AttackRender();
	}
}

void Golem::ImageRender()
{
	_shadow->SetSize(_shadow->GetFrameSize(0));
	_shadow->SetAlpha(0.3f);
	_shadow->SetScale(0.7f);
	_shadow->Render(_position.x, _position.y + 50, Pivot::CENTER, true);

	if (_state == StateType::Chasing)
	{
		_golemMove->SetSize(_golemMove->GetFrameSize(0));
		_golemMove->SetScale(1.0f);

		_golemMove_Red->SetSize(_golemMove_Red->GetFrameSize(0));
		_golemMove_Red->SetScale(1.0f);
		_golemMove_white->SetSize(_golemMove_white->GetFrameSize(0));
		_golemMove_white->SetScale(1.0f);

		if (_move == MoveType::Left)
		{
			if (!_attacked)
			{
				_golemMove->FrameRender(_position.x, _position.y, _moveCount, 0, Pivot::CENTER, true);
			}
			if (_attacked)
			{
				if (_attackedColor == false)
				{
					_golemMove_Red->FrameRender(_position.x, _position.y, _moveCount, 0, Pivot::CENTER, true);
				}
				if (_attackedColor == true)
				{
					_golemMove_white->FrameRender(_position.x, _position.y, _moveCount, 0, Pivot::CENTER, true);
				}
			}
		}
		if (_move == MoveType::Right)
		{
			if (!_attacked)
			{
				_golemMove->FrameRender(_position.x, _position.y, _moveCount, 1, Pivot::CENTER, true);
			}
			if (_attacked)
			{
				if (_attackedColor == false)
				{
					_golemMove_Red->FrameRender(_position.x, _position.y, _moveCount, 1, Pivot::CENTER, true);
				}
				if (_attackedColor == true)
				{
					_golemMove_white->FrameRender(_position.x, _position.y, _moveCount, 1, Pivot::CENTER, true);
				}
			}
		}
		if (_move == MoveType::Top)
		{
			if (!_attacked)
			{
				_golemMove->FrameRender(_position.x, _position.y, _moveCount, 2, Pivot::CENTER, true);
			}
			if (_attacked)
			{
				if (_attackedColor == false)
				{
					_golemMove_Red->FrameRender(_position.x, _position.y, _moveCount, 2, Pivot::CENTER, true);
				}
				if (_attackedColor == true)
				{
					_golemMove_white->FrameRender(_position.x, _position.y, _moveCount, 2, Pivot::CENTER, true);
				}
			}
		}
		if (_move == MoveType::Bottom)
		{
			if (!_attacked)
			{
				_golemMove->FrameRender(_position.x, _position.y, _moveCount, 3, Pivot::CENTER, true);
			}
			if (_attacked)
			{
				if (_attackedColor == false)
				{
					_golemMove_Red->FrameRender(_position.x, _position.y, _moveCount, 3, Pivot::CENTER, true);
				}
				if (_attackedColor == true)
				{
					_golemMove_white->FrameRender(_position.x, _position.y, _moveCount, 3, Pivot::CENTER, true);
				}
			}
		}
	}

	if (_state == StateType::attack)
	{
		_golemAttack->SetSize(_golemAttack->GetFrameSize(0));
		_golemAttack->SetScale(1.0f);

		_golemAttack_Red->SetSize(_golemAttack_Red->GetFrameSize(0));
		_golemAttack_Red->SetScale(1.0f);
		_golemAttack_White->SetSize(_golemAttack_White->GetFrameSize(0));
		_golemAttack_White->SetScale(1.0f);

		if (_move == MoveType::Left)
		{
			if (!_attacked)
			{
				_golemAttack->FrameRender(_position.x, _position.y, _attackCount, 0, Pivot::CENTER, true);
			}

			if (_attacked)
			{
				if (_attackedColor == false)
				{
					_golemAttack_Red->FrameRender(_position.x, _position.y, _moveCount, 0, Pivot::CENTER, true);
				}
				if (_attackedColor == true)
				{
					_golemAttack_White->FrameRender(_position.x, _position.y, _moveCount, 0, Pivot::CENTER, true);
				}
			}
		}
		if (_move == MoveType::Right)
		{
			if (!_attacked)
			{
				_golemAttack->FrameRender(_position.x, _position.y, _attackCount, 1, Pivot::CENTER, true);
			}

			if (_attacked)
			{
				if (_attackedColor == false)
				{
					_golemAttack_Red->FrameRender(_position.x, _position.y, _moveCount, 1, Pivot::CENTER, true);
				}
				if (_attackedColor == true)
				{
					_golemAttack_White->FrameRender(_position.x, _position.y, _moveCount, 1, Pivot::CENTER, true);
				}
			}
		}
		if (_move == MoveType::Top)
		{
			if (!_attacked)
			{
				_golemAttack->FrameRender(_position.x, _position.y, _attackCount, 2, Pivot::CENTER, true);
			}

			if (_attacked)
			{
				if (_attackedColor == false)
				{
					_golemAttack_Red->FrameRender(_position.x, _position.y, _moveCount, 2, Pivot::CENTER, true);
				}
				if (_attackedColor == true)
				{
					_golemAttack_White->FrameRender(_position.x, _position.y, _moveCount, 2, Pivot::CENTER, true);
				}
			}
		}
		if (_move == MoveType::Bottom)
		{
			if (!_attacked)
			{
				_golemAttack->FrameRender(_position.x, _position.y, _attackCount, 3, Pivot::CENTER, true);
			}

			if (_attacked)
			{
				if (_attackedColor == false)
				{
					_golemAttack_Red->FrameRender(_position.x, _position.y, _moveCount, 3, Pivot::CENTER, true);
				}
				if (_attackedColor == true)
				{
					_golemAttack_White->FrameRender(_position.x, _position.y, _moveCount, 3, Pivot::CENTER, true);
				}
			}
		}
	}
}

void Golem::InvenStop(bool stop)
{
	_isStop = stop;
}

//�i�ų� �ǰݴ����� �� �����̱� ���� �Լ�.
//���Ŀ� �Ⱦ�� ����������
void Golem::Move()
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
	//������ �¾����� ������� �̹���
	if (_attacked)
	{
		_count += _TimeManager->DeltaTime();
		if (_count <= 0.5f)
		{
			this->_position.x += cosf(_attackedAngle) * _speed * _TimeManager->DeltaTime()* 0.7f;
			this->_position.y += -sinf(_attackedAngle) * _speed * _TimeManager->DeltaTime()* 0.7;
			this->_renderRect = UpdateRect(_position, _size, Pivot::CENTER);

			if (_count < 0.2f)
			{
				_attackedColor = false;
			}
			if (_count > 0.2f)
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


void Golem::ObjectCollision()
{
	//=======================================
	//������Ʈ�� �浹
	//=======================================
	const vector <class GameObject*>* object;
	object = _ObjectManager->GetObjectListPointer(ObjectType::Object);
	for (int i = 0; i < object->size(); i++)
	{
		
		MoveItem* item = dynamic_cast<MoveItem*>((*object)[i]);
		Player* player = dynamic_cast<Player*>((*object)[i]);
		
		if (item == nullptr && player == nullptr && this != (*object)[i])
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