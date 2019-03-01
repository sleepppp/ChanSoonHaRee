#include "stdafx.h"
#include "Enemy.h"
#include "player.h"

Enemy::Enemy()
{	
}
Enemy::~Enemy()
{
}

void Enemy::Init()
{
	EnemyInit();

	this->_player = (player*)_ObjectManager->FindObject(ObjectType::Object,"player");
}

void Enemy::Release()
{

}

void Enemy::Update()
{
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
}

//���ʹ��� �ʱ�ȭ��Ȳ
void Enemy::EnemyInit()
{
	this->_name = "Enemy";						//�� �̸��� Enemy��
	this->_position = Vector2(100, 100);		//100, 100�������� �������
	this->_size = Vector2(50, 50);				//ũ��� 50, 50 ����?
	this->_pivot = Pivot::CENTER;				//�߽��� �߾�����!
	this->_speed = 90.0f;						//90.0f�� �ӵ��� �����δٱ�!
	this->_isAttack = false;					//���� �� �����ϰ� ���� �ʾ�
	this->_attackCount = 0;						//���ݸ���� �ӵ�? ��ɰž�
	this->_hp = 100;
	this->_demege = 34;
	this->_isAttackedCount = 0;
	//���� ���� ���ο� ���� ����, �׸����� ��Ʈ ����! 
	this->_sizeLeft = Vector2(-100, 10);
	this->_sizeRight = Vector2(100, 10);
	this->_sizeTop = Vector2(10, -100);
	this->_sizeBottom = Vector2(10, 100);
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

//���� ��Ȳ
void Enemy::Move()
{
	// �� �׻� �÷��̾ �߽����� ������ �ž�
	this->_angle = Math::GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
	if (_state == StateType::Chasing)
	{
		this->_position.x += cosf(_angle) * _speed * _TimeManager->DeltaTime();
		this->_position.y += -sinf(_angle) * _speed * _TimeManager->DeltaTime();
		//�����϶����� ���� �׷���
		this->UpdateMainRect();
	}
	if (_state == StateType::Attacked && this->_isAttackedCount < 200)
	{
		this->_position.x += cosf(_angle - Math::PI) * _speed * _TimeManager->DeltaTime();
		this->_position.y += -sinf(_angle - Math::PI) * _speed * _TimeManager->DeltaTime();
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
	if (_attackCount > 300)
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
		if (_move == MoveType::Left && _attackCount > 280)
		{
			_isAttackLeft = true;
			this->_attackLeft = Figure::RectMakeCenter({ _position.x - 60, _position.y }, _sizeLeft);
		}
		else _isAttackLeft = false;

		if (_move == MoveType::Right && _attackCount > 280)
		{
			_isAttackRight = true;
			this->_attackRight = Figure::RectMakeCenter({ _position.x + 60, _position.y }, _sizeRight);
		}
		else _isAttackRight = false;

		if (_move == MoveType::Top && _attackCount > 280)
		{
			_isAttackTop = true;
			this->_attackTop = Figure::RectMakeCenter({ _position.x ,_position.y - 60 }, _sizeTop);
		}
		else _isAttackTop = false;

		if (_move == MoveType::Bottom && _attackCount > 280)
		{
			_isAttackBottom = true;
			this->_attackBottom = Figure::RectMakeCenter({ _position.x, _position.y + 60 }, _sizeBottom);
		}
		else _isAttackBottom = false;
	}
}

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


