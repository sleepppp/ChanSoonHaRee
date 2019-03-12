#include "stdafx.h"
#include "Boss.h"
#include "Image.h"
#include "Animation.h"
#include "Player.h"


void Boss::HandShootHand()
{
	switch (_hand)
	{
		float angle;
		
	case HandState::Up:

		//�׸��ڿ� �հ��� �Ÿ�
		_distance = Math::GetDistance(_handPosition.x, _handPosition.y, _shadowPosition.x, _shadowPosition.y);
		
		//�Ÿ��� 500���� ������
		if (_distance <= 700)
		{
			//���� �ö󰡶�.
			_handPosition.y -= (_speed * 0.7) * _TimeManager->DeltaTime();
		}
		_handRc = Figure::RectMakeCenter(_handPosition, _handSize);
		//������� �ö�����
		if (_distance >= 700)
		{	
			_handPosition.y -= (_speed * 0.0f) * _TimeManager->DeltaTime();
			this->ChangeShadowState(ShadowState::Chasing);
		}
		break;
	case HandState::Down:
		
		//�հ� �׸����� �ޱ۰�.
		angle = Math::GetAngle(_handPosition.x, _handPosition.y, _shadowPosition.x, _shadowPosition.y);
		//�׸��ڿ� �հ��� �Ÿ�
		_distance = Math::GetDistance(_handPosition.x, _handPosition.y, _shadowPosition.x, _shadowPosition.y);

		//�׸��ڿ� ���� Y���� ���� �ʴٸ�
		if (_distance > 10)
		{
			//�׸����� Y������ �̵��ض�.
			_handPosition.y += -sinf(angle) * (_speed * 4) * _TimeManager->DeltaTime();
		}
		_handRc = Figure::RectMakeCenter(_handPosition, _handSize);
		//���� ���ٸ� 
		if (_distance <= 10)
		{
			_Camera->Shake(5.f, 0.5f);
			//��ð������־��.
			this->ChangeHandState(HandState::Stay);
		}
		break;
	case HandState::Stay:

		_timeCount += _TimeManager->DeltaTime();
		if (_timeCount > 2.f)
		{
			//���� ���¸� �ö󰡴� ���·� �ٲ��ش�.
			this->ChangeHandState(HandState::Up);
		}
		_handRc = Figure::RectMakeCenter(_handPosition, _handSize);
		break;
	case HandState::Chasing:
		
		//���� X���� ������ �׸����� X���� ����ٴѴ�.
		angle = Math::GetAngle(_handPosition.x, _handPosition.y, _shadowPosition.x, _shadowPosition.y);
		_handPosition.x = _shadowPosition.x;
		//�ټ����������� ��ų������ �����.
		if (_drapCount == 5)
		{
			_drapCount = 0;
			this->ChangeState(StateType::Hand_Shoot_Last);
		}
		_handRc = Figure::RectMakeCenter(_handPosition, _handSize);
		break;
	case HandState::End:
		break;
	default:
		break;
	}
}

void Boss::ChangeHandState(HandState hand)
{
	if (_hand == hand)
		return;

	_hand = hand;

	this->ChangeHandAnimation(hand);

	switch (_hand)
	{
	case HandState::Up:
		//������������� �˱����� ī��Ʈ�� �����ְ�
		this->_drapCount++;

		break;
	case HandState::Down:
		break;
	case HandState::Stay:
		RECT temp;
		if (IntersectRect(&temp, &_handRc, &_player->GetCollisionRect()))
		{
			_player->AttackedDamage(_damage);
		}
		break;
	case HandState::Chasing:
		break;
	case HandState::End:
		break;
	default:
		break;
	}
}

void Boss::ChangeHandAnimation(HandState hand)
{
	_handIter iter = _handList.find(hand);

	if (iter != _handList.end())
	{
		_handAni = iter->second;
		_handAni->Stop();
		_handAni->Play();;
	}
}

void Boss::CreateHandAnimation()
{
	Animation* chasing = new Animation;
	chasing->SetStartEndFrame(0, 0, 0, 0, false);
	chasing->SetIsLoop(false);
	chasing->SetFrameUpdateTime(1.f);
	_handList.insert(make_pair(HandState::Chasing, chasing));

	Animation* up = new Animation;
	up->SetStartEndFrame(16, 0, 18, 0, false);
	up->SetIsLoop(false);
	up->SetFrameUpdateTime(0.1f);
	_handList.insert(make_pair(HandState::Up, up));

	Animation* down = new Animation;
	down->SetStartEndFrame(0, 0, 3, 0, false);
	down->SetIsLoop(false);
	down->SetFrameUpdateTime(0.1f);
	_handList.insert(make_pair(HandState::Down, down));

	Animation* stay = new Animation;
	stay->SetStartEndFrame(3, 0, 16, 0, false);
	stay->SetIsLoop(false);
	stay->SetFrameUpdateTime(0.1f);
	_handList.insert(make_pair(HandState::Stay, stay));
}