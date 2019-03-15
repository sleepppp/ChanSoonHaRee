#include "stdafx.h"
#include "Npc_Lunk.h"
#include "Time.h"
#include "Image.h"
#include "Animation.h"
using namespace Figure;

Npc_Lunk::Npc_Lunk()
{
	movePoint.push_back(Vector2(600, 712));
	movePoint.push_back(Vector2(600, 987));
	movePoint.push_back(Vector2(847, 987));
	movePoint.push_back(Vector2(600, 987));

	_ImageManager->AddFrameImage("Lunk", L"../Resources/Npc/Lunk.png", 9, 4);
	_imgLunk = _ImageManager->FindImage("Lunk");

	_ImageManager->AddImage("Shadow", L"../Resources/Object/Shadow.png");
	this->_imgShadow = _ImageManager->FindImage("Shadow");

	this->_isActive = true;
	this->_pivot = Pivot::CENTER;
	this->_position = movePoint[0];
	this->_size = Vector2(78, 78);

	this->_speed = 30.f;
	this->_index = 1;
	this->_frameX = 0;
	this->_frameY = 0;

	this->_count = 0.0f;
	this->_pauseTime = 0.0f;
	this->_isArrive = false;
	this->UpdateMainRect();
}

Npc_Lunk::~Npc_Lunk()
{}

void Npc_Lunk::Init()
{}

void Npc_Lunk::Release()
{}

void Npc_Lunk::Update()
{
	//��� �ڸ��� �ӹ��� ���� ���ǰ� Ÿ�̸�
	if (_isArrive == true)
	{
		_pauseTime += _TimeManager->DeltaTime();

		if (_pauseTime > 2.0f)
		{
			_isArrive = false;
			_pauseTime = 0.0f;
			_index++;
			if (movePoint.size() <= _index)
			{
				_index = 0;
			}

		}
	}
	else
	{
		_position.x += cos(_angle)*_speed*_TimeManager->DeltaTime();
		_position.y -= sin(_angle)*_speed*_TimeManager->DeltaTime();
	}

	if (_distance <= 5.0f)
	{
		_isArrive = true;
	}
	//�Ÿ����� ���ؼ� ���� ��ġ������ �̵��� ������
	//��������� ���� ��ġ������ ���� �����Ѵ�.
	_distance = Math::GetDistance(_position.x, _position.y, movePoint[_index].x, movePoint[_index].y);

	this->_angle = Math::GetAngle(_position.x, _position.y, movePoint[_index].x, movePoint[_index].y);
	this->MoveType();
	this->StateType();


	//��ġ���� ���� �������� �����Ѵ�.
	//�������� ������ �ð��� �ش�.
	_count += _TimeManager->DeltaTime();
	if (_count > 0.2f)
	{
		//�ӹ����� �������� �����Ѵ�
		if (_isArrive == false)
		{
			if (_frameX > 7)
			{
				_frameX = 0;
			}
			else
			{
				_frameX++;
			}
			_count = 0.0f;
		}

	}

	this->UpdateMainRect();
}

void Npc_Lunk::Render()
{
	
	//�׸���
	_imgShadow->SetAlpha(0.4f);
	_imgShadow->SetSize(Vector2(48, 24));
	_imgShadow->Render(this->_position.x, this->_position.y + 30, Pivot::CENTER, true);

	_imgLunk->SetSize(Vector2(64, 64));
	_imgLunk->SetScale(1.0f);
	_imgLunk->FrameRender(_position.x, _position.y, _frameX, _frameY, Pivot::CENTER, true);
	//cout << _position.x << ", " <<_position.y<<endl;

	if (_isDebug)
	{
		_DXRenderer->DrawRectangle(_mainRect, DefaultBrush::blue, true);
	}

	
}

//�ޱ۰��� ���� ���� Ÿ���� ����.
void Npc_Lunk::MoveType()
{
	//45�� ~ 135���� ���⿡���� ž�� �ٶ󺸰� �Ѵ�.
	if (_angle > Math::PI / 4.f && _angle < ((3 * Math::PI) / 4.f))
	{
		_state = State::Up;
	}
	//135�� ~ 225���� ���⿡���� ����Ʈ�� �ٶ󺸰� �Ѵ�. 
	else if (_angle > ((3.f * Math::PI) / 4.f) && _angle < (Math::PI + (Math::PI / 4.f)))
	{
		_state = State::Left;
	}
	//225�� ~ 315���� ���⿡���� ������ �ٶ󺸰� �Ѵ�.
	else if (_angle > (Math::PI + (Math::PI / 4.f)) && _angle < (Math::PI + ((3.f * Math::PI) / 4.f)))
	{
		_state = State::Down;
	}
	//���� ������ �ƴ϶�� ����Ʈ�� �ٶ󺸰��Ѵ�.
	else
	{
		_state = State::Right;
	}
}

void Npc_Lunk::StateType()
{
	switch (_state)
	{
	case State::Left:
		_frameY = 2;
		break;
	case State::Right:
		_frameY = 3;
		break;
	case State::Up:
		_frameY = 1;
		break;
	case State::Down:
		_frameY = 0;
		break;
	}
}
