#include "stdafx.h"
#include "BigSlime.h"
#include "Player.h"
#include "Animation.h"
#include "Image.h"

BigSlime::BigSlime(Vector2 pos)
{	
	_name = "BigSlime";
	_position = pos;
	_size = Vector2(200, 200);
	_pivot = Pivot::CENTER;
	_speed = 100.0f;
	_hp = 500;
	_damage = 20;
	_renderRect = Figure::RectMakeCenter(_position, _size);
	CreateAnimation();
	this->_state = StateType::End;
	ChangeState(StateType::Idle);
}


BigSlime::~BigSlime()
{

}

void BigSlime::Init()
{
	Enemy::Init();
}

void BigSlime::Release()
{
}

void BigSlime::Update()
{
	UpdateState();
	_renderRect = Figure::RectMakeCenter(_position, _size);
	this->ObjectCollision();
	_ani->_animation->UpdateFrame();

}

void BigSlime::Render()
{
	_ani->_CreateImage->SetSize(Vector2(_size.x * 2, _size.y * 2));
	_ani->_CreateImage->FrameRender((int)_position.x, (int)_position.y, _ani->_animation->GetNowFrameX(), _ani->_animation->GetNowFrameY(), _pivot, true);

	if (_isDebug == true)
	{
		_DXRenderer->DrawEllipse(_position, _size.x * 0.55f, DefaultBrush::blue, true);
		_DXRenderer->DrawRectangle(_renderRect, DefaultBrush::green, true);
	}
}

void BigSlime::ChangeState(StateType state)
{
	if (this->_state == state)
		return;
	
	this->_state = state;

	this->ChangeAnimation(state);

	
	switch (_state)
	{
	case BigSlime::StateType::Idle:
		break;
	case BigSlime::StateType::Create:
		break;
	case BigSlime::StateType::Chasing_L:
		break;
	case BigSlime::StateType::Chasing_R:
		break;
	case BigSlime::StateType::Attack_L:
		_attackRc = Figure::RectMakeCenter(Vector2(_position.x - 100, _position.y), Vector2(70, 70));
		break;
	case BigSlime::StateType::Attack_R:
		_attackRc = Figure::RectMakeCenter(Vector2(_position.x + 100, _position.y), Vector2(70, 70));
		break;
	case BigSlime::StateType::Dead:
		break;
	case BigSlime::StateType::End:
		break;
	default:
		break;
	}
}
void BigSlime::ChangeAnimation(StateType state)
{
	// 들어온 상태값을 이터에 담아!
	_aniIter iter = _aniList.find(state);

	if (iter != _aniList.end())
	{
		_ani = iter->second;
		_ani->_animation->Stop();
		_ani->_animation->Play();
	}
}
void BigSlime::UpdateState()
{
	float angle = Math::GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
	float distance = Math::GetDistance(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);

	switch (_state)
	{
	case BigSlime::StateType::Idle:

		if (_size.x * 2 > distance)
		{
			ChangeState(StateType::Create);
		}
		break;
	case BigSlime::StateType::Create:
		if (_ani->_animation->GetNowFrameX() == 36)
		{
			ChasingMove();
		}
		break;
	case BigSlime::StateType::Chasing_L:

		_position.x += cosf(angle) * _speed * _TimeManager->DeltaTime();
		_position.y += -sinf(angle) * _speed * _TimeManager->DeltaTime();
			if (100 > distance)
			{
				if (_position.x > _player->GetPosition().x)
				{
					ChangeState(StateType::Attack_L);
				}
			}
		break;
	case BigSlime::StateType::Chasing_R:

		_position.x += cosf(angle) * _speed * _TimeManager->DeltaTime();
		_position.y += -sinf(angle) * _speed * _TimeManager->DeltaTime();

	
			if (100 > distance)
			{
				if (_position.x < _player->GetPosition().x)
				{
					ChangeState(StateType::Attack_R);
				}
			}
		break;
	case BigSlime::StateType::Attack_L:

		if (_ani->_animation->GetNowFrameX() == 21)
		{
			RECT temp;
			if (IntersectRect(&temp, &_attackRc, &_player->GetCollisionRect()))
			{
				_player->AttackedDamage(_damage);
			}

			ChasingMove();
		}
		break;
	case BigSlime::StateType::Attack_R:

		if (_ani->_animation->GetNowFrameX() == 21)
		{
			RECT temp;
			if (IntersectRect(&temp, &_attackRc, &_player->GetCollisionRect()))
			{
				_player->AttackedDamage(_damage);
			}
			ChasingMove();
		}
		break;
	case BigSlime::StateType::Dead:
		break;
	case BigSlime::StateType::End:
		break;
	default:
		break;
	}
}

void BigSlime::ChasingMove()
{
	if (_player->GetPosition().x < _position.x)
	{
		ChangeState(StateType::Chasing_L);
	}
	else if (_player->GetPosition().x > _position.x)
	{
		ChangeState(StateType::Chasing_R);
	}
}

void BigSlime::CreateAnimation()
{
	Ani* Idle = new Ani;
	Idle->_animation = new Animation;
	Idle->_CreateImage = _ImageManager->FindImage("Create");
	Idle->_animation->SetStartEndFrame(0, 0, 0, 0, false);
	Idle->_animation->SetIsLoop(false);
	Idle->_animation->SetFrameUpdateTime(1.0f);
	_aniList.insert(make_pair(StateType::Idle, Idle));

	Ani* Create = new Ani;
	Create->_animation = new Animation;
	Create->_CreateImage = _ImageManager->FindImage("Create");
	Create->_animation->SetStartEndFrame(0, 0, 36, 0, false);
	Create->_animation->SetIsLoop(false);
	Create->_animation->SetFrameUpdateTime(0.1f);
	_aniList.insert(make_pair(StateType::Create, Create));

	Ani* Move_L = new Ani;
	Move_L->_animation = new Animation;
	Move_L->_CreateImage = _ImageManager->FindImage("Move");
	Move_L->_animation->SetStartEndFrame(0, 0, 7, 0, false);
	Move_L->_animation->SetIsLoop(true);
	Move_L->_animation->SetFrameUpdateTime(0.2f);
	_aniList.insert(make_pair(StateType::Chasing_L, Move_L));

	Ani* Move_R = new Ani;
	Move_R->_animation = new Animation;
	Move_R->_CreateImage = _ImageManager->FindImage("Move");
	Move_R->_animation->SetStartEndFrame(0, 1, 7, 1, false);
	Move_R->_animation->SetIsLoop(true);
	Move_R->_animation->SetFrameUpdateTime(0.2f);
	_aniList.insert(make_pair(StateType::Chasing_R, Move_R));

	Ani* Attack_L = new Ani;
	Attack_L->_animation = new Animation;
	Attack_L->_CreateImage = _ImageManager->FindImage("Attack");
	Attack_L->_animation->SetStartEndFrame(0, 1, 21, 1, false);
	Attack_L->_animation->SetIsLoop(false);
	Attack_L->_animation->SetFrameUpdateTime(0.1f);
	_aniList.insert(make_pair(StateType::Attack_L, Attack_L));

	Ani* Attack_R = new Ani;
	Attack_R->_animation = new Animation;
	Attack_R->_CreateImage = _ImageManager->FindImage("Attack");
	Attack_R->_animation->SetStartEndFrame(0, 0, 21, 0, false);
	Attack_R->_animation->SetIsLoop(false);
	Attack_R->_animation->SetFrameUpdateTime(0.1f);
	_aniList.insert(make_pair(StateType::Attack_R, Attack_R));
	
	Ani* dead = new Ani;
	dead->_animation = new Animation;
	dead->_CreateImage = _ImageManager->FindImage("SlimeDead");
	dead->_animation->SetStartEndFrame(0, 0, 0, 0, false);
	dead->_animation->SetIsLoop(false);
	dead->_animation->SetFrameUpdateTime(0.1f);
	_aniList.insert(make_pair(StateType::Dead, dead));

}