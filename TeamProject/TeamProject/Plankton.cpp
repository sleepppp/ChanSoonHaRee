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


	//�ö�ũ�� ���� �Լ�
	PlanktonStates();
}

void Plankton::Render()
{
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


		break;
	case Plankton::PlanktonState::Attack:


		break;
	case Plankton::PlanktonState::Attacked:

		break;
	case Plankton::PlanktonState::End:
		break;
	default:
		break;
	}
}
