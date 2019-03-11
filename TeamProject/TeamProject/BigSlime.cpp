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
	_hp = 500;
	_damage = 46;

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

}

void BigSlime::Render()
{
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
	case BigSlime::StateType::Chasing:
		break;
	case BigSlime::StateType::Attack:
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
		_mainAnimation = iter->second._animation;
		_mainAnimation->Stop();
		_mainAnimation->Play();
	}
}

void BigSlime::CreateAnimation()
{
	Animation* idle = new Animation;

	Animation* create = new Animation;

	Animation* moveLift = new Animation;

	Animation* moveRight = new Animation;

	Animation* attackLift = new Animation;

	Animation* attackRight = new Animation;

	Animation* dead = new Animation;
}