#include "stdafx.h"
#include "Boss.h"
#include "Image.h"
#include "Animation.h"
#include "Player.h"


Boss::Boss()
{
	//보스의 몸통을 생성할 기본적인 골격들
	this->_position = Vector2(600, 100);	//좌표
	this->_size = Vector2(300, 300);		//크기
	this->_pivot = Pivot::CENTER;			//중심위치
	this->_hp = 800;						//체력
	this->_speed = 10.0f;					//속도
	this->_demage = 0;						//공격력
	this->_distance = 0.f;					//직선거리 (나중에 넣을거고 코드만짜려고)
	this->_angle = 0.f;						//앵글값 (직선거리와 같음)
	this->UpdateMainRect();					//렉트생성.
	//초기 상태값은 보스가 움직이지 않아야 하니까 가만히 있는 상태를 만들어준다.
	_state = StateType::Idle;
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
}

void Boss::Render()
{
}

void Boss::BossStateType()
{
	switch (_state)
	{
	case Boss::StateType::Idle:
		break;
	case Boss::StateType::Create:
		break;
	case Boss::StateType::Dead:
		break;
	case Boss::StateType::Hand_Shoot_First:
		break;
	case Boss::StateType::Hand_Shoot_Second:
		break;
	case Boss::StateType::Hand_Shoot_Last:
		break;
	case Boss::StateType::Rock_Shoot_First:
		break;
	case Boss::StateType::Rock_Shoot_Second:
		break;
	case Boss::StateType::Rock_Shoot_Last:
		break;
	case Boss::StateType::Fist_Shoot_First:
		break;
	case Boss::StateType::Fist_Shoot_Second:
		break;
	case Boss::StateType::Fist_Shoot_Last:
		break;
	case Boss::StateType::End:
		break;
	default:
		break;
	}
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
