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

	if (_state == StateType::Chasing && _move == MoveType::Top)
	{
		_golemTopMove->SetSize(_golemTopMove->GetFrameSize(0));
		_golemTopMove->SetScale(1.0f);
		_golemTopMove->FrameRender(_position.x, _position.y, _golemTopMoveCount, 0, Pivot::CENTER, true);
	}

	if (_state == StateType::Chasing &&_move == MoveType::Left)
	{
		_golemLeftMove->SetSize(_golemLeftMove->GetFrameSize(0));
		_golemLeftMove->SetScale(1.0f);
		_golemLeftMove->FrameRender(_position.x, _position.y, _golemLeftMoveCount, 0, Pivot::CENTER, true);
	}
	
	if (_state == StateType::Chasing &&_move == MoveType::Right)
	{
		_golemRightMove->SetSize(_golemRightMove->GetFrameSize(0));
		_golemRightMove->SetScale(1.0f);
		_golemRightMove->FrameRender(_position.x, _position.y, _golemRightMoveCount, 0, Pivot::CENTER, true);
	}
	
	if (_state == StateType::Chasing &&_move == MoveType::Bottom)
	{
		_golemBottomMove->SetSize(_golemBottomMove->GetFrameSize(0));
		_golemBottomMove->SetScale(1.0f);
		_golemBottomMove->FrameRender(_position.x, _position.y, _golemBottomMoveCount, 0, Pivot::CENTER, true);
	}

	if (_state == StateType::attack && _move == MoveType::Top)
	{
		_golemTopAttack->SetSize(_golemTopAttack->GetFrameSize(0));
		_golemTopAttack->SetScale(1.0f);
		_golemTopAttack->FrameRender(_position.x, _position.y, _golemTopAttackCount, 0, Pivot::CENTER, true);
	}

	if (_state == StateType::attack &&_move == MoveType::Left)
	{
		_golemLeftAttack->SetSize(_golemLeftAttack->GetFrameSize(0));
		_golemLeftAttack->SetScale(1.0f);
		_golemLeftAttack->FrameRender(_position.x, _position.y, _golemLeftAttackCount, 0, Pivot::CENTER, true);
	}
	
	if (_state == StateType::attack &&_move == MoveType::Right)
	{
		_golemRightAttack->SetSize(_golemRightAttack->GetFrameSize(0));
		_golemRightAttack->SetScale(1.0f);
		_golemRightAttack->FrameRender(_position.x, _position.y, _golemRightAttackCount, 0, Pivot::CENTER, true);
	}

	if (_state == StateType::attack &&_move == MoveType::Bottom)
	{
		_golemBottomAttack->SetSize(_golemBottomAttack->GetFrameSize(0));
		_golemBottomAttack->SetScale(1.0f);
		_golemBottomAttack->FrameRender(_position.x, _position.y, _golemBottomAttackCount, 0, Pivot::CENTER, true);
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

void Enemy::GolemImageInit()
{
	_ImageManager->AddFrameImage("GolemTopMove", L"../Resources/Enemy/Golem/GolemTopMove.png", 47, 1);
	_ImageManager->AddFrameImage("GolemLeftMove", L"../Resources/Enemy/Golem/GolemLeftMove.png", 47, 1);
	_ImageManager->AddFrameImage("GolemRightMove", L"../Resources/Enemy/Golem/GolemRightMove.png", 47, 1);
	_ImageManager->AddFrameImage("GolemBottomMove", L"../Resources/Enemy/Golem/GolemBottomMove.png", 47, 1);

	_ImageManager->AddFrameImage("GolemTopAttack", L"../Resources/Enemy/Golem/GolemTopAttack.png", 13, 1);
	_ImageManager->AddFrameImage("GolemLeftAttack", L"../Resources/Enemy/Golem/GolemLeftAttack.png", 13, 1);
	_ImageManager->AddFrameImage("GolemRightAttack", L"../Resources/Enemy/Golem/GolemRightAttack.png", 13, 1);
	_ImageManager->AddFrameImage("GolemBottomAttack", L"../Resources/Enemy/Golem/GolemBottomAttack.png", 13, 1);

	this->_golemTopMove = _ImageManager->FindImage("GolemTopMove");
	this->_golemLeftMove = _ImageManager->FindImage("GolemLeftMove");
	this->_golemRightMove = _ImageManager->FindImage("GolemRightMove");
	this->_golemBottomMove = _ImageManager->FindImage("GolemBottomMove");

	this->_golemTopAttack = _ImageManager->FindImage("GolemTopAttack");
	this->_golemLeftAttack = _ImageManager->FindImage("GolemLeftAttack");
	this->_golemRightAttack = _ImageManager->FindImage("GolemRightAttack");
	this->_golemBottomAttack = _ImageManager->FindImage("GolemBottomAttack");


	this->_golemTopMoveCount = 0;
	this->_golemLeftMoveCount = 0;
	this->_golemRightMoveCount = 0;
	this->_golemBottomMoveCount = 0;

	this->_golemTopAttackCount = 0;
	this->_golemLeftAttackCount = 0;
	this->_golemRightAttackCount = 0;
	this->_golemBottomAttackCount = 0;

	this->_state = StateType::Chasing;
	this->_move = MoveType::Left;

}

void Enemy::GolemImageCount()
{
	if (_state == StateType::Chasing && _move == MoveType::Top)
	{
		if (_count % 5 == 0)
		{
			_golemTopMoveCount++;
		}
		if (_golemTopMoveCount > 47)
		{
			_golemTopMoveCount = 0;
		}
	}
	else
		_golemTopMoveCount = 0;

	if (_state == StateType::Chasing &&_move == MoveType::Left)
	{
		if (_count % 5 == 0)
		{
			_golemLeftMoveCount++;
		}
		if (_golemLeftMoveCount > 47)
		{
			_golemLeftMoveCount = 0;
		}
	}
	else
		_golemLeftMoveCount = 0;
	if (_state == StateType::Chasing &&_move == MoveType::Right)
	{
		if (_count % 5 == 0)
		{
			_golemRightMoveCount++;
		}
		if (_golemRightMoveCount > 47)
		{
			_golemRightMoveCount = 0;
		}
	}
	else
		_golemRightMoveCount = 0;

	if (_state == StateType::Chasing &&_move == MoveType::Bottom)
	{
		if (_count % 5 == 0)
		{
			_golemBottomMoveCount++;
		}
		if (_golemBottomMoveCount > 47)
		{
			_golemBottomMoveCount = 0;
		}
	}
	else
		_golemBottomMoveCount = 0;


	if (_state == StateType::attack && _move == MoveType::Top)
	{
		if (_count % 5 == 0)
		{
			_golemTopAttackCount++;
		}
		if (_golemTopAttackCount > 13)
		{
			_golemTopAttackCount = 0;
		}
	}
	else
		_golemTopAttackCount = 0;

	if (_state == StateType::attack &&_move == MoveType::Left)
	{
		if (_count % 5 == 0)
		{
			_golemLeftAttackCount++;
		}
		if (_golemLeftAttackCount > 13)
		{
			_golemLeftAttackCount = 0;
		}
	}
	else
		_golemLeftAttackCount = 0;

	if (_state == StateType::attack &&_move == MoveType::Right)
	{
		if (_count % 5 == 0)
		{
			_golemRightAttackCount++;
		}
		if (_golemRightAttackCount > 13)
		{
			_golemRightAttackCount = 0;
		}
	}
	else
		_golemRightAttackCount = 0;

	if (_state == StateType::attack &&_move == MoveType::Bottom)
	{
		if (_count % 5 == 0)
		{
			_golemBottomAttackCount++;
		}
		if (_golemBottomAttackCount > 13)
		{
			_golemBottomAttackCount = 0;
		}
	}
	else
		_golemBottomAttackCount = 0;


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





