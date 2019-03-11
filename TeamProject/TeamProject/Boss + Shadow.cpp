#include "stdafx.h"
#include "Boss.h"
#include "Image.h"
#include "Animation.h"
#include "Player.h"


void Boss::HandShootShadow()
{
	switch (_shadow)
	{
		float angle;
		//�׸��ڰ� �÷��̾ �i����
	case ShadowState::Chasing:
		if (Math::GetDistance(_shadowPosition.x, _shadowPosition.y, _player->GetPosition().x, _player->GetPosition().y) > 2)
		{
			angle = Math::GetAngle(_shadowPosition.x, _shadowPosition.y, _player->GetPosition().x, _player->GetPosition().y);
			_shadowPosition.x += cosf(angle) * _speed * _TimeManager->DeltaTime();
			_shadowPosition.y += -sinf(angle) * _speed * _TimeManager->DeltaTime();
			_shadowRc = Figure::RectMakeCenter(_shadowPosition, _shadowSize);
		}
			_timeCount += _TimeManager->DeltaTime();
			//���� Ÿ��ī��Ʈ�� �Ѿ��
			if (_timeCount > 10.0f)
			{
				_timeCount = 0.f;
				this->ChangeShadowState(ShadowState::Stop);
			}
		
		break;
	case ShadowState::Stop:

		break;
	case ShadowState::Idle:
		break;

	case ShadowState::End:
		break;
	default:
		break;
	}
}

void Boss::ChangeShadowState(ShadowState shadow)
{
	if (_shadow == shadow)
		return;
	_shadow = shadow;

	switch (_shadow)
	{
	case ShadowState::Chasing:
		//���� �׸��ڸ� �i�ƶ�.
		this->ChangeHandState(HandState::Chasing);
		break;
	case ShadowState::Stop:
		//�׸��ڰ� ���߸� ���� �����Ͷ�.
		this->ChangeHandState(HandState::Down);
		break;
	case ShadowState::Idle:
		break;
	case ShadowState::End:
		break;
	default:
		break;
	}
}