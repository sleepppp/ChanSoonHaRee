#include "stdafx.h"
#include "Boss.h"
#include "Image.h"
#include "Animation.h"
#include "Player.h"


Boss::Boss()
{
	//보스의 몸통을 생성할 기본적인 골격들
	this->_position = Vector2(600, 100);	//좌표
	this->_size = Vector2(200, 200);		//크기
	this->_pivot = Pivot::CENTER;			//중심위치
	this->_hp = 700;						//체력
	this->_speed = 10.0f;					//속도
	this->_demage = 0;						//공격력
	this->_distance = 0.f;					//직선거리 (나중에 넣을거고 코드만짜려고)
	this->_angle = 0.f;						//앵글값 (직선거리와 같음)
	this->UpdateMainRect();					//렉트생성.
	//초기 상태값은 보스가 움직이지 않아야 하니까 가만히 있는 상태를 만들어준다.
	this->ChangeState(StateType::Idle);
}


Boss::~Boss()
{
}


void Boss::Init()
{

	//플레이어의 이름으로 불러와서 내가 쓸수 있게 만들어 준다.
	this->_player = (Player*)_ObjectManager->FindObject(ObjectType::Object, "player");	
}

void Boss::Release()
{
}

void Boss::Update()
{
	switch (_state)
	{
	case Boss::StateType::Idle:
		if (_distance > _size.x)
			StateType::Create;
		break;
	case Boss::StateType::Create:
		//if(/*지정한 이미지의 카운트 값이 된다면*/)
			//랜덤으로 세가지 상태중 하나로 바꿔라.
		break;
	case Boss::StateType::Dead:
		break;
	case Boss::StateType::Rock_Shoot:
		break;
	case Boss::StateType::Hand_Shoot:
		break;
	case Boss::StateType::Fist_Shoot:
		break;
	case Boss::StateType::End:
		break;
	default:
		break;
	}
}

void Boss::Render()
{
}

//상태에 따라 바뀌줄 이넘값을 설정해 준다.
void Boss::ChangeState(StateType state)
{
	//바뀐 상태값이 기존상태값이라면 바뀌면 안되니까 함수를 빠져나가게 하고
	if (_state == state)
		return;
	//빠져나가지 않았다면 바뀐 거니까 상태를 변경해 준다.
	_state = state;
	
	//상태에 따라 애니메이션도 바꿔준다.
	this->ChangeAnimation(state);

	switch (_state)
	{
	case Boss::StateType::Idle:
		break;
	case Boss::StateType::Create:
		break;
	case Boss::StateType::Dead:
		break;
	case Boss::StateType::Rock_Shoot:
		break;
	case Boss::StateType::Hand_Shoot:
		break;
	case Boss::StateType::Fist_Shoot:
		break;
	case Boss::StateType::End:
		break;
	default:
		break;
	}
}
//바뀐 상태에 따라 애니메이션도 재설정 해준다.
void Boss::ChangeAnimation(StateType state)
{
	// 들어온 상태값을 이터에 담아!
	StateAnimationIter iter = _stateAnimationList.find(state);
	//마지막까지 돌지않고 상태값을 담은 이터를 찾았다면!
	if (iter != _stateAnimationList.end())
	{
		//그 키값의 내용을 실행시켜라!
		_mainAnimation = iter->second;
		//기존꺼는 끄고
		_mainAnimation->Stop();
		//새로운건 루프!
		_mainAnimation->Play();
	}

}
//애니메이션 루프시킬 내용들 제작과정
void Boss::CreateAnimation()
{
	//이미지가 없어서 나중에 넣어야지

	//기본 움직이지 않는 상태일때
	Animation* Idle = new Animation;
	//플레이어를 인식하고 동작하기 위해서 조립되고있을때
	Animation* Create = new Animation;
	//플레이어에게 얻어맞아 죽을 때
	Animation* Dead = new Animation;
	//플레이어를 공격하기 위해서 돌을 떨굴때
	Animation* Rock_Shoot = new Animation;
	//플레이어를 공격하기 위해 손을 떨굴때
	Animation* Hand_Shoot = new Animation;
	//플레이어를 공격하기 위해 쬰쬬니를 날릴때
	Animation* Fist_Shoot = new Animation;
}

//직선거리 길이 구하는 공식.
float Boss::Distance(Vector2 position)
{
	//직선거리를 구하고
	float distance = Math::GetDistance(position.x, position.y, _player->GetPosition().x, _player->GetPosition().y);
	//반환해
	return distance;
}

//앵글값구하는 공식.
float Boss::Angle(Vector2 position)
{
	//앵글값을 구하고
	float angle = Math::GetAngle(position.x, position.y, _player->GetPosition().x, _player->GetPosition().y);
	//반환해
	return angle;
}
