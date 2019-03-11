#include "stdafx.h"
#include "Plankton.h"
#include "Player.h"
#include "MoveItem.h"


Plankton::Plankton(Vector2 position)
{
	//Ŭ���� �̸� (������Ʈ Ű)
	this->_name = "plankton";

	//������ �̹��� �߰�
	this->_plankton = _ImageManager->FindImage("planktonIMG");
	this->_planktonRed = _ImageManager->FindImage("planktonRedIMG");
	this->_planktonWhite = _ImageManager->FindImage("planktonWhiteIMG");

	//������
	this->_position = position;
	//������
	this->_damage = 15;
	//HP	
	this->_hp = 75;
	//���ǵ�
	this->_speed = 15.0f;
	//������
	this->_size = Vector2(30, 30);
	//�ǹ�
	this->_pivot = Pivot::CENTER;
	//��Ʈ
	this->UpdateRect(_position, _size, _pivot);

	//�⺻ ���´� ���󰡱�
	this->_planktonState = PlanktonState::Follow;

	_isAttack = false;
}


Plankton::~Plankton()
{
}

void Plankton::Init()
{
	//���ʹ� Init
	Enemy::Init();
}

void Plankton::Release()
{
}

void Plankton::Update()
{
	//������Ʈ �浹 üũ �Լ�
	this->ObjectCollision();

	//�ö�ũ�� ���� �Լ�
	PlanktonStates();
}

void Plankton::Render()
{
	//_plankton->SetSize(_)
}

void Plankton::PlanktonStates()
{
	switch (_planktonState)
	{
	//���� : ���󰡱� Follow
	case Plankton::PlanktonState::Follow:
		//�ޱ� �� ���ϱ�
		this->_angle = Math::GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
		//���� �ޱ� ������ �÷��̾����� �̵���Ű��
		this->_position.x += cosf(_angle) * _speed * _TimeManager->DeltaTime();
		this->_position.y -= sinf(_angle) * _speed * _TimeManager->DeltaTime();
		//���� ������Ʈ
		this->_renderRect = UpdateRect(_position, _size, Pivot::CENTER);

		//�ö�ũ�� ��Ʈ�� �÷��̾� ��Ʈ�� �浹�ϸ� ���¸� ���� ���·� ����
		RECT temp;
		if (IntersectRect(&temp, &_renderRect, &_player->GetMainRect())) 
		{
			//���� ���� ����
			_planktonState = PlanktonState::Attack;
		}
		break;

	//���� : ���� Attack
	case Plankton::PlanktonState::Attack:
		//���� true
		_isAttack = true;
		//������ true�̸�
		if (_isAttack == true) 
		{
			//���� ��Ʈ ����
			_atkRect = UpdateRect(_position, _size, Pivot::CENTER);
			//���� ��Ʈ�� �÷��̾� ��Ʈ�� �浹�ϸ�
			if (IntersectRect(&temp, &_atkRect, &_player->GetMainRect())) 
			{
				//���� false
				_isAttack = false;
				//�ǰ� ���� ����
				_planktonState = PlanktonState::Attacked;
			}
		}
		else 
		{

		}
		break;

	//���� : �ǰ� Attacked
	case Plankton::PlanktonState::Attacked:
		//�ǰ� : �÷��̾� ������ �ޱ�
		this->AttackedDemege(_player->GetPlayerDamage());

		//�ǰ� ������ ���, �и���� �÷� ���� �ð� ������ �Լ�
		this->AtkedState(_position, this->_attackedAngle, 50.f, 0.3f);
		break;
	case Plankton::PlanktonState::End:
		break;
	default:
		break;
	}
}


//�ǰ� ������ ���, �и���� �÷� ���� �ð� ������ �Լ�
void Plankton::AtkedState(Vector2 position, float angle, float speed, float countValue)
{
	//��Ÿ Ÿ��
	float deltaTimeCount = 0.f;
	//��Ÿ Ÿ��++
	deltaTimeCount += _TimeManager->DeltaTime();
	
	//�ǰ� ī��Ʈ
	float atkedCount = 0.f;
	//�ǰ� ī��Ʈ++
	atkedCount += _TimeManager->DeltaTime();

	//��Ÿ Ÿ�� 0.5�ʺ��� �۰ų� ��������
	if (deltaTimeCount <= 0.5f) 
	{
		//�����ǰ� ��Ʈ ����
		position.x += cosf(angle) * speed * _TimeManager->DeltaTime();
		position.y -= sinf(angle) * speed * _TimeManager->DeltaTime();
		this->_renderRect = UpdateRect(position, _size, Pivot::CENTER);

		//�ǰ� ī��Ʈ�� ���� �ǰ� ���� �����ϱ�
		if (atkedCount <= countValue)
		{
			//�ǰ� ���� (���)
			_isAtkedRender = false;
		}
		else if (atkedCount > countValue)
		{
			//�ǰ� ���� (������)
			_isAtkedRender = true;

			//�ǰ� ī��Ʈ �� �ʱ�ȭ
			countValue = 0;
		}
	}
	//��Ÿ Ÿ�� 0.5�ʺ��� Ŀ����
	else if (deltaTimeCount > 0.5f) 
	{
		//��Ÿ Ÿ�� �ʱ�ȭ
		deltaTimeCount = 0;
		//���� : ���󰡱� ����
		_planktonState = PlanktonState::Follow;
	}
}
