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
		float distance;
	case HandState::Up:
		cout << "up" << endl;

		//�׸��ڿ� �հ��� �Ÿ�
		distance = Math::GetDistance(_handPosition.x, _handPosition.y, _shadowPosition.x, _shadowPosition.y);
		
		//�Ÿ��� 500���� ������
		if (distance <= 700)
		{
			//���� �ö󰡶�.
			_handPosition.y -= (_speed * 0.7) * _TimeManager->DeltaTime();
		}
		//������� �ö�����
		if (distance >= 700)
		{	
			_handPosition.y -= (_speed * 0.0f) * _TimeManager->DeltaTime();
			this->ChangeShadowState(ShadowState::Chasing);
		}
		break;
	case HandState::Down:
		//�հ� �׸����� �ޱ۰�.
		angle = Math::GetAngle(_handPosition.x, _handPosition.y, _shadowPosition.x, _shadowPosition.y);
		//�׸��ڿ� �հ��� �Ÿ�
		distance = Math::GetDistance(_handPosition.x, _handPosition.y, _shadowPosition.x, _shadowPosition.y);
		cout << "down" << endl;
		//�׸��ڿ� ���� Y���� ���� �ʴٸ�
		if (distance > 10)
		{
			//�׸����� Y������ �̵��ض�.
			_handPosition.y += -sinf(angle) * (_speed * 3) * _TimeManager->DeltaTime();
		}

		//���� ���ٸ� 
		if (distance <= 10)
		{
			//��ð������־��.
			this->ChangeHandState(HandState::Stay);
		}
		break;
	case HandState::Stay:
		cout << "stay" << endl;

		_timeCount += _TimeManager->DeltaTime();
		if (_timeCount > 7)
		{
			//���� ���¸� �ö󰡴� ���·� �ٲ��ش�.
			this->ChangeHandState(HandState::Up);
		}
		break;
	case HandState::Chasing:
		cout << "chasing" << endl;
		//���� X���� ������ �׸����� X���� ����ٴѴ�.
		angle = Math::GetAngle(_handPosition.x, _handPosition.y, _shadowPosition.x, _shadowPosition.y);
		_handPosition.x = _shadowPosition.x;
		//�ټ����������� ��ų������ �����.
		if (_drapCount == 5)
		{
			this->ChangeState(StateType::Hand_Shoot_Last);
		}
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
	up->SetStartEndFrame(0, 0, 2, 0, false);
	up->SetIsLoop(false);
	up->SetFrameUpdateTime(0.2f);
	_handList.insert(make_pair(HandState::Up, up));

	Animation* down = new Animation;
	down->SetStartEndFrame(16, 0, 18, 0, false);
	down->SetIsLoop(false);
	down->SetFrameUpdateTime(0.2f);
	_handList.insert(make_pair(HandState::Down, down));

	Animation* stay = new Animation;
	stay->SetStartEndFrame(2, 0, 16, 0, false);
	stay->SetIsLoop(false);
	stay->SetFrameUpdateTime(0.1f);
	_handList.insert(make_pair(HandState::Stay, stay));
}