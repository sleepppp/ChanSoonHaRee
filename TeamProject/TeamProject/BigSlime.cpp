#include "stdafx.h"
#include "BigSlime.h"
#include "Player.h"
#include "Animation.h"
#include "Image.h"

//BigSlime::BigSlime(Vector2 pos)
//{
//	this->_name = "bigSlime";
//	this->_position = pos;
//	this->_size = Vector2(200, 200);
//	this->_speed = 70.0f;
//	this->_pivot = Pivot::CENTER;
//	this->_hp = 1000;
//	this->_demage = 60;
//	this->_distance = 0;
//	this->_renderRect = UpdateRect(_position, _size, _pivot);
//	this->_attackedCollisionRc = UpdateRect(_position, Vector2(_size.x - 50, _size.y - 20), Pivot::CENTER);
//
//	//생성과 이동, 공격이미지를 넣어준다.
//	this->_createSlimeImage = _ImageManager->AddFrameImage("CreateSlime", L"../Resources/Enemy/MiddleBoss/CreateSlime.png", 37, 1);
//	this->_SlimeMove = _ImageManager->AddFrameImage("SlimeMove", L"../Resources/Enemy/MiddleBoss/SlimeMove.png", 8, 2);
//	this->_SlimeAttack = _ImageManager->AddFrameImage("SlimeAttack", L"../Resources/Enemy/MiddleBoss/SlimeAttack.png", 22, 2);
//
//	//처음시작 상태는 아무것도 하고있찌 않는 기본상태로 시작한다.
//	this->ChangeState(SlimeStateType::Idle);
//	
//}
//
//
//BigSlime::~BigSlime()
//{
//
//}
//
//void BigSlime::Init()
//{
//	Enemy::Init();
//}
//
//void BigSlime::Release()
//{
//	AnimationIter iter = _animationList.begin();
//	for (; iter != _animationList.end(); ++iter)
//	{
//		SafeDelete(iter->second);
//	}
//	_animationList.clear();
//}
//
//void BigSlime::Update()
//{
//	SlimeIdle();
//	SlimeCreateBigSlime();
//	SlimeChasingMove();
//	this->_attackedCollisionRc = UpdateRect(_position, Vector2(_size.x - 50, _size.y - 20), Pivot::CENTER);
//}
//
//void BigSlime::Render()
//{
//	//렉트보여주기.
//	/*if (_isDebug == true)
	{
		_DXRenderer->DrawRectangle(_renderRect, DefaultBrush::black);
		_DXRenderer->DrawEllipse(_position, (_size.x * 1.2f), DefaultBrush::red);
		_DXRenderer->DrawRectangle(_attackedCollisionRc, DefaultBrush::gray);
	}
	if (_slimeType == SlimeStateType::Create)
	{
		_createSlimeImage->SetScale(1.3f);
		this->_createSlimeImage->SetSize(_createSlimeImage->GetFrameSize(0));
		//this->_createSlimeImage->SetScale(1.0f);
		this->_createSlimeImage->FrameRender(_position.x, _position.y, _createSlimeCount, 0, Pivot::CENTER, true);
	}
	if (_slimeType == SlimeStateType::Chasing && _move2 == MoveType2::Left)
	{
		_SlimeMove->SetScale(1.3f);
		this->_SlimeMove->SetSize(_SlimeMove->GetFrameSize(0));
		this->_SlimeMove->FrameRender(_position.x, _position.y, _chasingSlimeCount, 0, Pivot::CENTER, true);
	}
	if (_slimeType == SlimeStateType::Chasing && _move2 == MoveType2::Right)
	{
		_SlimeMove->SetScale(1.3f);
		this->_SlimeMove->SetSize(_SlimeMove->GetFrameSize(0));
		this->_SlimeMove->FrameRender(_position.x, _position.y, _chasingSlimeCount, 1, Pivot::CENTER, true);
	}*/
//}
//
//void BigSlime::ChangeState(SlimeStateType state)
//{
//	if (_slimeType == state)
//		return;
//
//	_slimeType = state;
//
//	this->ChangeAnimation(state);
//
//	switch (_slimeType)
//	{
//	case BigSlime::Idle:
//		break;
//	case BigSlime::Create:
//		break;
//	case BigSlime::Chasing:
//		break;
//	case BigSlime::Attack:
//		break;
//	case BigSlime::Attacked:
//		break;
//	case BigSlime::Dead:
//		break;
//	case BigSlime::End:
//		break;
//	default:
//		break;
//	}
//}
//
//void BigSlime::ChangeAnimation(SlimeStateType state)
//{
//	AnimationIter iter = _animationList.find(state);
//
//	if (iter != _animationList.end())
//	{
//		_mainAnimation = iter->second;
//		_mainAnimation->Stop();
//		_mainAnimation->Play();
//	}
//}
//
//void BigSlime::UpdateState()
//{
//	switch (_slimeType)
//	{
//	case BigSlime::Idle:
//		break;
//	case BigSlime::Create:
//		break;
//	case BigSlime::Chasing:
//		break;
//	case BigSlime::Attack:
//		break;
//	case BigSlime::Attacked:
//		break;
//	case BigSlime::Dead:
//		break;
//	case BigSlime::End:
//		break;
//	default:
//		break;
//	}
//}
//
//void BigSlime::CreateAnimation()
//{
//	Animation* create = new Animation;
//}
//
////숨어있을때의 슬라임.
//void BigSlime::SlimeIdle()
//{
//	if (_slimeType == SlimeStateType::Idle)
//	{
//		_distance = Math::GetDistance(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
//
//		if (_distance < (_size.x * 1.2f))
//		{
//			_slimeType = SlimeStateType::Create;
//		}
//	}
//}
//
//void BigSlime::SlimeAttack()
//{
//}
//
////반경안에 들어오면 생성되는 모션이 등장.
//void BigSlime::SlimeCreateBigSlime()
//{
//	//if (_slimeType == SlimeStateType::Create)
//	//{
//	//	_createTimeCount += _TimeManager->DeltaTime();
//	//	if (_createTimeCount >= 0.5f / 5.f)
//	//	{
//	//		//35개
//	//		_createTimeCount = 0;
//	//		_createSlimeCount++;
//	//	}
//	//	if (_createSlimeCount > 36)
//	//	{
//	//		_createSlimeCount = 37;
//	//		_slimeType = SlimeStateType::Chasing;
//	//	}
//	//}
//}
////플레이어를 쫒는 슬라임.
//void BigSlime::SlimeChasingMove()
//{
//	//if (_slimeType == SlimeStateType::Chasing)
//	//{
//	//	this->EnemyMove2Type();
//	//	this->Move();
//	//
//	//	_chasingTimaCount += _TimeManager->DeltaTime();
//	//	if (_chasingTimaCount >= 0.5f / 5.f)
//	//	{
//	//		_chasingTimaCount = 0;
//	//		_chasingSlimeCount++;
//	//	}
//	//	if (_chasingSlimeCount >= 8)
//	//	{
//	//		_chasingSlimeCount = 0;
//	//	}
//	//}
//}


