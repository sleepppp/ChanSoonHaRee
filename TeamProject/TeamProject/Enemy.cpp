#include "stdafx.h"
#include "Image.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy()
{
}
Enemy::~Enemy()
{
}

void Enemy::Init()
{
	EnemyInit();
	GolemImageInit();
	this->_player = (Player*)_ObjectManager->FindObject(ObjectType::Object, "Will");

}

void Enemy::Release()
{

}

void Enemy::Update()
{
	_count++;
	//�� ���ݻ��°� �ƴ϶�� ������ �� �־�
	if (_state == StateType::Chasing)
	{
		this->Move();
	}
	//������ ���ݻ��¶�� ���ڸ����� ��������
	this->Attack();

	this->CardinalPointsAttack();
	//���� �ٶ󺸴� ������ ����� ������!
	this->MoveType();
	//�� �̹����� ������ ���� �Լ�.
	this->GolemImageCount();
}

void Enemy::Render()
{
	//���ʹ� ��Ʈ �����ֱ�
	if (_Input->IsToggleKey('1'))
	{
		//���� �ʷϻ����� ������� �������־�
		_DXRenderer->DrawRectangle(_mainRect, DefaultBrush::green);
		//������ �ƴ϶�� �� ������ ��Ÿ��� �Ķ������� ������
		if (_state == StateType::Chasing)
		{
			_DXRenderer->DrawEllipse(_position, (_size.x * 2), DefaultBrush::blue);
		}
		//���ݽ������̶�� �� ��Ÿ��� ���������� ���ؿ�
		if (_state == StateType::attack)
		{
			_DXRenderer->DrawEllipse(_position, (_size.x * 2), DefaultBrush::red);
		}
		AttackRender();
	}
	//����Ʈ ����Ʈ ž ���� ��.
	if (_state == StateType::Chasing && _move == MoveType::Top)
	{
		_golemMove->SetSize(_golemMove->GetFrameSize(0));
		_golemMove->SetScale(1.0f);
		_golemMove->FrameRender(_position.x, _position.y, _golemMoveCount, 2, Pivot::CENTER, true);
	}

	if (_state == StateType::Chasing &&_move == MoveType::Left)
	{
		_golemMove->SetSize(_golemMove->GetFrameSize(0));
		_golemMove->SetScale(1.0f);
		_golemMove->FrameRender(_position.x, _position.y, _golemMoveCount, 0, Pivot::CENTER, true);
	}
	
	if (_state == StateType::Chasing &&_move == MoveType::Right)
	{
		_golemMove->SetSize(_golemMove->GetFrameSize(0));
		_golemMove->SetScale(1.0f);
		_golemMove->FrameRender(_position.x, _position.y, _golemMoveCount, 1, Pivot::CENTER, true);
	}
	
	if (_state == StateType::Chasing &&_move == MoveType::Bottom)
	{
		_golemMove->SetSize(_golemMove->GetFrameSize(0));
		_golemMove->SetScale(1.0f);
		_golemMove->FrameRender(_position.x, _position.y, _golemMoveCount, 3, Pivot::CENTER, true);
	}

	if (_state == StateType::attack && _move == MoveType::Top)
	{
		_golemAttack->SetSize(_golemAttack->GetFrameSize(0));
		_golemAttack->SetScale(1.0f);
		_golemAttack->FrameRender(_position.x, _position.y, _golemAttackCount, 2, Pivot::CENTER, true);
	}

	if (_state == StateType::attack &&_move == MoveType::Left)
	{
		_golemAttack->SetSize(_golemAttack->GetFrameSize(0));
		_golemAttack->SetScale(1.0f);
		_golemAttack->FrameRender(_position.x, _position.y, _golemAttackCount, 0, Pivot::CENTER, true);
	}
	
	if (_state == StateType::attack &&_move == MoveType::Right)
	{
		_golemAttack->SetSize(_golemAttack->GetFrameSize(0));
		_golemAttack->SetScale(1.0f);
		_golemAttack->FrameRender(_position.x, _position.y, _golemAttackCount, 1, Pivot::CENTER, true);
	}

	if (_state == StateType::attack &&_move == MoveType::Bottom)
	{
		_golemAttack->SetSize(_golemAttack->GetFrameSize(0));
		_golemAttack->SetScale(1.0f);
		_golemAttack->FrameRender(_position.x, _position.y, _golemAttackCount, 3, Pivot::CENTER, true);
	}

}

//���ʹ��� �ʱ�ȭ��Ȳ
void Enemy::EnemyInit()
{
	this->_name = "Enemy";						//�� �̸��� Enemy��
	this->_position = Vector2(100, 100);		//100, 100�������� �������
	this->_size = Vector2(100, 100);				//ũ��� 50, 50 ����?
	this->_pivot = Pivot::CENTER;				//�߽��� �߾�����!
	this->_speed = 90.0f;						//90.0f�� �ӵ��� �����δٱ�!
	this->_isAttack = false;					//���� �� �����ϰ� ���� �ʾ�
	this->_attackCount = 0;						//���ݸ���� �ӵ�? ��ɰž�
	this->_hp = 100;
	this->_demege = 34;
	this->_isAttackedCount = 0;
	//���� ���� ���ο� ���� ����, �׸����� ��Ʈ ����! 
	this->_sizeLeft = Vector2(-100, 20);
	this->_sizeRight = Vector2(100, 20);
	this->_sizeTop = Vector2(20, -100);
	this->_sizeBottom = Vector2(20, 100);
	this->_isAttackTop = false;
	this->_isAttackLeft = false;
	this->_isAttackRight = false;
	this->_isAttackBottom = false;
	this->_attackLeft = Figure::RectMakeCenter(_position, _sizeLeft);
	this->_attackRight = Figure::RectMakeCenter(_position, _sizeRight);
	this->_attackTop = Figure::RectMakeCenter(_position, _sizeTop);
	this->_attackBottom = Figure::RectMakeCenter(_position, _sizeBottom);

	this->UpdateMainRect();						//���� �׷��ְ�����
}
//���ʹ� �̹��� �ʱ�ȭ �� �ʱ����
void Enemy::GolemImageInit()
{
	//����Ʈ ����Ʈ ž ���� ��.
	this->_golemMove = _ImageManager->AddFrameImage("GolemMove", L"../Resources/Enemy/Golem/GolemMove.png", 8, 4);
	this->_golemAttack = _ImageManager->AddFrameImage("GolemAttack", L"../Resources/Enemy/Golem/GolemAttack.png", 13, 4);
	this->_golemMoveCount = 0;
	this->_golemAttackCount = 0;

	this->_state = StateType::Chasing;
	this->_move = MoveType::Left;

}
//���ʹ� �̹��� ī��Ʈ�� ���� �Լ�.
void Enemy::GolemImageCount()
{
	if (_state == StateType::Chasing && _move == MoveType::Top)
	{
		if (_count % 60 == 0)
		{
			_golemMoveCount++;
		}
		if (_golemMoveCount >= 8)
		{
			_golemMoveCount = 0;
		}
	}

	if (_state == StateType::Chasing &&_move == MoveType::Left)
	{
		if (_count % 60 == 0)
		{
			_golemMoveCount++;
		}
		if (_golemMoveCount >= 8)
		{
			_golemMoveCount = 0;
		}
	}

	if (_state == StateType::Chasing &&_move == MoveType::Right)
	{
		if (_count % 60 == 0)
		{
			_golemMoveCount++;
		}
		if (_golemMoveCount >= 8)
		{
			_golemMoveCount = 0;
		}
	}

	if (_state == StateType::Chasing &&_move == MoveType::Bottom)
	{
		if (_count % 60 == 0)
		{
			_golemMoveCount++;
		}
		if (_golemMoveCount >= 8)
		{
			_golemMoveCount = 0;
		}
	}

	if (_state == StateType::attack && _move == MoveType::Top)
	{
		if (_count % 60 == 0)
		{
			_golemAttackCount++;
		}
		if (_golemAttackCount >= 13)
		{
			_golemAttackCount = 0;
		}
	}

	if (_state == StateType::attack &&_move == MoveType::Left)
	{
		if (_count % 60 == 0)
		{
			_golemAttackCount++;
		}
		if (_golemAttackCount >= 13)
		{
			_golemAttackCount = 0;
		}
	}

	if (_state == StateType::attack &&_move == MoveType::Right)
	{
		if (_count % 60 == 0)
		{
			_golemAttackCount++;
		}
		if (_golemAttackCount >= 13)
		{
			_golemAttackCount = 0;
		}
	}

	if (_state == StateType::attack &&_move == MoveType::Bottom)
	{
		if (_count % 60 == 0)
		{
			_golemAttackCount++;
		}
		if (_golemAttackCount >= 13)
		{
			_golemAttackCount = 0;
		}
	}
}
//���� ��Ȳ
void Enemy::Move()
{
	// �� �׻� �÷��̾ �߽����� ������ �ž�
	if (_state == StateType::Chasing)
	{
		this->_angle = Math::GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
		this->_position.x += cosf(_angle) * _speed * _TimeManager->DeltaTime();
		this->_position.y += -sinf(_angle) * _speed * _TimeManager->DeltaTime();
		//�����϶����� ���� �׷���
		this->UpdateMainRect();
	}
	if (_state == StateType::Attacked && this->_isAttackedCount < 200)
	{
		this->_angle = Math::GetAngle(_player->GetPosition().x, _player->GetPosition().y, _position.x, _position.y);
		this->_position.x += cosf(_angle ) * _speed * _TimeManager->DeltaTime();
		this->_position.y += -sinf(_angle ) * _speed * _TimeManager->DeltaTime();
		//�����϶����� ���� �׷���
		this->UpdateMainRect();
	}
}
//���� ��Ȳ
void Enemy::Attack()
{
	//�÷��̾�� ���� ���� �Ÿ��� ��� ������!
	_distance = Math::GetDistance(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

	//���� ���� �÷��̾�� �Ÿ��� �� ��ũ���� �ι谡 �ȵȴٸ�
	if (_distance < (_size.x * 2))
	{
		//�� ������ �����Ұž�
		_state = StateType::attack;
	}
	//������ �����Ѵٸ�?
	if (_state == StateType::attack)
	{
		//�� ���ݸ���� �����ֱ����� ī��Ʈ��!
		_attackCount++;
	}
	//ī��Ʈ�� 300���� Ŀ���ٸ�?!
	if (_attackCount > 800)
	{
		//�� �̹� ������ �������� ī��Ʈ�� �����ְ�
		_attackCount = 0;
		//���ݻ��¸� ���� ���·� �ٲܰž�
		_state = StateType::Chasing;
	}
}
//���� ���� �ȿ� ������ ��� �������� ���������� ó��.
void Enemy::MoveType()
{
	if (_angle > Math::PI / 4 && _angle < ((3 * Math::PI) / 4))
	{
		_move = MoveType::Top;
	}
	else if (_angle > ((3 * Math::PI) / 4) && _angle < (Math::PI + (Math::PI / 4)))
	{
		_move = MoveType::Left;
	}
	else if (_angle > (Math::PI + (Math::PI / 4)) && _angle < (Math::PI + ((3 * Math::PI) / 4)))
	{
		_move = MoveType::Bottom;
	}
	else
		_move = MoveType::Right;
}
//���� ��Ʈ ����.
void Enemy::AttackRender()
{
	//���� ž�κ��̶�� 
	if (this->_isAttackTop == true && this->_state == StateType::attack)
	{
		_DXRenderer->DrawRectangle(_attackTop, DefaultBrush::red);
	}
	//���� ����Ʈ �κ��̶��
	if (this->_isAttackLeft == true && this->_state == StateType::attack)
	{
		_DXRenderer->DrawRectangle(_attackLeft, DefaultBrush::red);
	}
	//���� ����Ʈ �κ��̶��
	if (this->_isAttackRight == true && this->_state == StateType::attack)
	{
		_DXRenderer->DrawRectangle(_attackRight, DefaultBrush::red);
	}
	//���� ���Һκ��̶��
	if (this->_isAttackBottom == true && this->_state == StateType::attack)
	{
		_DXRenderer->DrawRectangle(_attackBottom, DefaultBrush::red);
	}
}
//���� �÷��̾ �����Ҷ� �� ��Ȳ��� �׿� �´� ���ݼ��� ó��.
void Enemy::CardinalPointsAttack()
{
	if (_state == StateType::attack)
	{
		if (_move == MoveType::Left && _attackCount > 700)
		{
			_isAttackLeft = true;
			this->_attackLeft = Figure::RectMakeCenter({ _position.x - 60, _position.y }, _sizeLeft);
		}
		else _isAttackLeft = false;

		if (_move == MoveType::Right && _attackCount > 700)
		{
			_isAttackRight = true;
			this->_attackRight = Figure::RectMakeCenter({ _position.x + 60, _position.y }, _sizeRight);
		}
		else _isAttackRight = false;

		if (_move == MoveType::Top && _attackCount > 700)
		{
			_isAttackTop = true;
			this->_attackTop = Figure::RectMakeCenter({ _position.x ,_position.y - 60 }, _sizeTop);
		}
		else _isAttackTop = false;

		if (_move == MoveType::Bottom && _attackCount > 700)
		{
			_isAttackBottom = true;
			this->_attackBottom = Figure::RectMakeCenter({ _position.x, _position.y + 60 }, _sizeBottom);
		}
		else _isAttackBottom = false;
	}
}
//������ ���� ���� ��Ȳ.
void Enemy::Collision()
{
	RECT Temp = { 0 };
	if (IntersectRect(&Temp, &_attackLeft, &_player->GetMainRect()))
	{
		_isAttack = true;
	}
	if (IntersectRect(&Temp, &_attackTop, &_player->GetMainRect()))
	{
		_isAttack = true;
	}
	if (IntersectRect(&Temp, &_attackRight, &_player->GetMainRect()))
	{
		_isAttack = true;
	}
	if (IntersectRect(&Temp, &_attackBottom, &_player->GetMainRect()))
	{
		_isAttack = true;
	}
}
//�� ������ �ѱ�� ���� �Լ�.
void Enemy::AttackedDemege(int damage)
{
	_hp -= damage;
	if (_hp <= 0)
	{
		this->Destroy();
	}
	else
	{
		_state = StateType::Attacked;
		_isAttackedCount++;
		if (this->_isAttackedCount > 200)
		{
			this->_isAttackedCount = 0;
			_state = StateType::Chasing;
		}
	}
}





