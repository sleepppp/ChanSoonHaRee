#include "stdafx.h"
#include "Plankton.h"
#include "Player.h"
#include "MoveItem.h"
#include "Animation.h"


Plankton::Plankton(Vector2 position)
{
	//Ŭ���� �̸� (������Ʈ Ű)
	this->_name = "plankton";

	//������ �̹��� �߰�
	this->_plankton = _ImageManager->FindImage("planktonIMG");
	this->_planktonRed = _ImageManager->FindImage("planktonRedIMG");
	this->_planktonWhite = _ImageManager->FindImage("planktonWhiteIMG");

	//�ִϸ��̼� new
	_planktonAnimation = new Animation;

	//���� ������ x,y�� �� ������ x,y
	_planktonAnimation->SetStartEndFrame(0, 0, _plankton->GetMaxFrameX() - 1, 0, false);
	//���� ����
	_planktonAnimation->SetIsLoop(true);
	//������ ���� �ð�
	_planktonAnimation->SetFrameUpdateTime(0.2f);
	//������ ����
	_planktonAnimation->Play();

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
	//��Ʈ ����
	this->UpdateRect(_position, _size, _pivot);

	//�⺻ ���´� ���󰡱�
	this->_planktonState = PlanktonState::Follow;

	//���� bool
	_isAttack = false;

	//�κ� ���� bool
	_isInvenStop = false;

	//�ǰ� bool
	_isAtked = false;

	//���� ī��Ʈ �ʱ�ȭ
	_atkCount = 0;

	//���� �޽��� Ȱ��ȭ
	this->AddCallbackMessage("InventoryOpen", [this](TagMessage message) {this->InvenStop(1); });
	this->AddCallbackMessage("InventoryClose", [this](TagMessage message) {this->InvenStop(0); });
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
	//������
	SafeDelete(_planktonAnimation);
}

void Plankton::Update()
{

	//������Ʈ �浹 üũ �Լ�
	this->ObjectCollision();

	if (!_isInvenStop)
	{
		//�ö�ũ�� ���� �Լ�
		PlanktonStates();
	}

	//�ö�ũ�� ������ ����
	_planktonAnimation->Play();

	//�ö�ũ�� ������ ������Ʈ
	_planktonAnimation->UpdateFrame();
	

	if (_isAtked == true) 
	{
		//�ǰ� ������ ���, �и���� �÷� ���� �ð� ������ �Լ�
		this->AtkedState(_position, this->_attackedAngle, 50.f, 0.3f);
	}
}

void Plankton::Render()
{
	if (_planktonState == PlanktonState::Follow || _planktonState == PlanktonState::Attack)
	{
		//�ö�ũ�� ������
		_plankton->SetSize(_plankton->GetFrameSize(0));
		//�ö�ũ�� ������ ����
		_plankton->FrameRender(_position.x, _position.y, _planktonAnimation->GetNowFrameX(), 0, Pivot::CENTER, true);
	}
	
	//���� �ǰ� ������ ���
	else if (_planktonState == PlanktonState::Attacked) 
	{
		//�ö�ũ�� ������
		//�ö�ũ�� ����
		_planktonRed->SetSize(_plankton->GetFrameSize(0));
		//�ö�ũ�� �Ͼ�
		_planktonWhite->SetSize(_plankton->GetFrameSize(0));

		//���� �ǰ� ������ true�̸�
		if (_isAtkedRender == true) 
		{
			//�ö�ũ�� ������ ����
			_planktonRed->FrameRender(_position.x, _position.y, _planktonAnimation->GetNowFrameX(), 0, Pivot::CENTER, true);
		}
		//���� �ǰ� ������ false�̸�
		else if (_isAtkedRender == false) 
		{
			//�ö�ũ�� ������ ����
			_planktonWhite->FrameRender(_position.x, _position.y, _planktonAnimation->GetNowFrameX(), 0, Pivot::CENTER, true);
		}

		//������ ��Ʈ ��¿�
		_DamageFontManager->ShowDamage(_position, _player->GetPlayerDamage());
	}

	//����� (F1)
	if (_isDebug) 
	{
		//���� �簢�� ����
		_DXRenderer->DrawRectangle(_renderRect, DefaultBrush::red, true);
		_DXRenderer->DrawRectangle(_atkRect, DefaultBrush::gray, true, 5.0f);
	}

}

//�ö�ũ�� ���� �Լ� (switch��)
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
		if (IntersectRect(&temp, &_renderRect, &_player->GetCollisionRect())) 
		{
			//���� ���� ����
			_planktonState = PlanktonState::Attack;
		}
		break;

	//���� : ���� Attack
	case Plankton::PlanktonState::Attack:
		//���� true
		_isAttack = true;

		//���� ī��Ʈ
		_atkCount += _TimeManager->DeltaTime();

		//���� ��Ʈ ����
		_atkRect = UpdateRect(_position, _size, Pivot::CENTER);

		//������ true�̸�
		if (_isAttack == true) 
		{
			//���� ��Ʈ�� �÷��̾� ��Ʈ�� �浹�ϸ�
			if (IntersectRect(&temp, &_atkRect, &_player->GetCollisionRect()))
			{
				//�ǰ� ���� ����
				_planktonState = PlanktonState::Attacked;

				//�ǰ� : �÷��̾� ������ ����
				_player->AttackedDamage(_damage);

				//���� false
				_isAttack = false;
			}
		}
		//���� false�̸�
		else if(_isAttack == false)
		{
			//���󰡱� ���·� ����
			_planktonState = PlanktonState::Follow;
		}
		break;

	//���� : �ǰ� Attacked
	case Plankton::PlanktonState::Attacked:
		//�ǰ� true
		_isAtked = true;
		break;

	//���� : ���� Dead
	case Plankton::PlanktonState::Dead:

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
		if (atkedCount > countValue)
		{
			//�ǰ� ���� (������)
			_isAtkedRender = true;

			//�ǰ� ī��Ʈ �� �ʱ�ȭ
			countValue = 0;
		}
	}
	//��Ÿ Ÿ�� 0.5�ʺ��� Ŀ����
	if (deltaTimeCount > 0.5f) 
	{
		//��Ÿ Ÿ�� �ʱ�ȭ
		deltaTimeCount = 0;
		//���� : ���󰡱� ����
		_planktonState = PlanktonState::Follow;
		
		//�ǰ� false
		_isAtked = false;
	}
}

void Plankton::InvenStop(bool isInvenStop)
{
	//�Լ��� ȣ��Ǹ� _isInvenStop�� ���¸� ���� ������ ���� 
	_isInvenStop = isInvenStop;
}
