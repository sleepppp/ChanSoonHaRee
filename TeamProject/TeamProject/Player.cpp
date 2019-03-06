#include "stdafx.h"
#include "Player.h"

#include "Image.h"
#include "Animation.h"
#include "Timer.h"

using namespace Figure;
/********************************************************************************/
//## Init ##
/********************************************************************************/
void Player::Init()
{
	//이미지 추가, 매니저에서 FInd 하여 찾아옴
	_ImageManager->AddFrameImage("Will", L"../Resources/Player/will_dungeon.png", 10, 13);
	this->_imgMove = _ImageManager->FindImage("Will");
	_ImageManager->AddFrameImage("Will_Sword1", L"../Resources/Player/will_sword1.png", 8, 4);
	this->_imgAtkSword1 = _ImageManager->FindImage("Will_Sword1");
	_ImageManager->AddFrameImage("Will_Sword2", L"../Resources/Player/will_sword2.png", 8, 4);
	this->_imgAtkSword2 = _ImageManager->FindImage("Will_Sword2");

	
	//기본 변수 초기화
	this->_name = "Will";
	this->_size = Vector2(120, 120);
	this->_position = Vector2(627, 120);
	this->_isActive = true;
	this->_pivot = Pivot::CENTER;
	this->_speed = 400.0f;
	//this->_speed = Vector2(300.0f, 300.0f);
	this->UpdateMainRect();

	//시간을 한번에!
	_frameRun = 0.1f;
	_frameIdle = 0.1f;
	//left = 0.05f;
	//	right = 0.05f;
	//	up = 0.05f;
	//	down = 0.05f;


	//정밀 충돌용 렉트 위치 초기화
	this->_collisionRect = RectMakeCenter(_position, Vector2(60.f, 60.f));
	
	//오브젝트와 충돌하기 위한 렉트(발부분만 있음)
	//this->_obColliRect = RectMakeBottom(_position.x, _position.y,10,30);
	
	//상태별 애니메이션 전부 생성하여 맵에 담아둔다.
	this->CreateAnimation();

	// 처음 시작 상태를 위한 세팅
	this->ChangeState(State::DownIdle);


	//_frameRoll = 0.1f;
}

/********************************************************************************/
//## Release ##
/********************************************************************************/
void Player::Release()
{
	AnimationIter iter = _animationList.begin();
	for (; iter != _animationList.end(); ++iter)
	{
		SafeDelete(iter->second);
	}
	_animationList.clear();
}

/********************************************************************************/
//## Update ##
/********************************************************************************/
void Player::Update()
{
	//이동량 측정할 변수
	Vector2 moveValue(0, 0);

	//상태에 따라 다르게 업데이트
	switch (_state)
	{
	case Player::State::LeftIdle:
		if (_Input->GetKey('A')) this->ChangeState(State::LeftRun);		
		else if (_Input->GetKey('D')) this->ChangeState(State::RightRun);		
		else if (_Input->GetKey('W')) this->ChangeState(State::UpRun);		
		else if (_Input->GetKey('S')) this->ChangeState(State::DownRun);
		else if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::LeftRoll);
		//this->IdleKeyInput();
		cout << "LeftIdle" << endl;
		break;
	case Player::State::RightIdle:
		if (_Input->GetKey('A')) this->ChangeState(State::LeftRun);
		else if (_Input->GetKey('D')) this->ChangeState(State::RightRun);
		else if (_Input->GetKey('W')) this->ChangeState(State::UpRun);
		else if (_Input->GetKey('S')) this->ChangeState(State::DownRun);
		else if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::RightRoll);
		cout << "RightIdle" << endl;
		//this->IdleKeyInput();
		break;

	case Player::State::UpIdle:
		if (_Input->GetKey('A')) this->ChangeState(State::LeftRun);
		else if (_Input->GetKey('D')) this->ChangeState(State::RightRun);
		else if (_Input->GetKey('W')) this->ChangeState(State::UpRun);
		else if (_Input->GetKey('S')) this->ChangeState(State::DownRun);
		else if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::UpRoll);
		cout << "UpIdle" << endl;
		//this->IdleKeyInput();
		break;

	case Player::State::DownIdle:
		if (_Input->GetKey('A')) this->ChangeState(State::LeftRun);
		else if (_Input->GetKey('D')) this->ChangeState(State::RightRun);
		else if (_Input->GetKey('W')) this->ChangeState(State::UpRun);
		else if (_Input->GetKey('S')) this->ChangeState(State::DownRun);
		else if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::DownRoll);
		cout << "DownIdle" << endl;
		//this->IdleKeyInput();
		break;

		//대각선일경우 이미지 무조건 상하로 변경됨
		//롤링도 대각선으로 감

	case Player::State::LeftRun:		
		if (_Input->GetKey('A')) moveValue += Vector2(-1.0f, 0.0f);	//왼누르기
		if (_Input->GetKeyUp('A')) this->ChangeState(State::LeftIdle); //왼떼기
		
		//대각선 시작		
		if (_Input->GetKey('W'))				//대각선 위 누르기
		{
			ChangeAnimation(Player::State::UpRun);
			moveValue += Vector2(0.0f, -1.0f);
		}
		else if (_Input->GetKey('S'))			//대각선 아래 누르기
		{
			moveValue += Vector2(0.0f, 1.0f);
			ChangeAnimation(Player::State::DownRun);
		}

		if (_Input->GetKeyUp('W'))			//대각선 위 떼기
		{			
			ChangeAnimation(Player::State::LeftRun);
			//moveValue += Vector2(-1.0f, 0.0f);
			//this->ChangeState(State::LeftRun);
		}		
		else if (_Input->GetKeyUp('S'))			//대각선 아래 떼기
		{			
			this->ChangeState(State::LeftRun);
			//ChangeAnimation(Player::State::LeftRun);
		//	moveValue += Vector2(-1.0f, 0.0f);
		}	
		
		if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::LeftRoll);
		cout << "LeftRun" << endl;

		break;
		//=====================================================================================
	case Player::State::RightRun:
		if (_Input->GetKey('D')) moveValue += Vector2(1.0f, 0.0f);
		if (_Input->GetKeyUp('D')) this->ChangeState(State::RightIdle);
		
		
		
		//대각선 시작
		if ( _Input->GetKey('W'))	//대각선 위
		{
			ChangeAnimation(Player::State::UpRun);
			moveValue += Vector2(0.0f, -1.0f);
		}
		else if (_Input->GetKey('S'))	//대각선 아래
		{
			moveValue += Vector2(0.0f, 1.0f);
			ChangeAnimation(Player::State::DownRun);
		}

		if (_Input->GetKeyUp('W'))
		{
			ChangeAnimation(Player::State::RightRun);
			//moveValue += Vector2(1.0f, 0.0f);
		}
		else if (_Input->GetKeyUp('S'))
		{
			ChangeAnimation(Player::State::RightRun);
			//moveValue += Vector2(1.0f, 0.0f);
		}
		
		if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::RightRoll);
		cout << "RightRun" << endl;
		break;
		//=====================================================================================
	case Player::State::UpRun:
		if (_Input->GetKey('W')) moveValue += Vector2(0.0f, -1.0f);
		if (_Input->GetKeyUp('W')) this->ChangeState(State::UpIdle);		

		if (_Input->GetKey('A')) moveValue += Vector2(-1.0f, 0.0f);
		else if (_Input->GetKey('D')) moveValue += Vector2(1.0f, 0.0f);
		

		if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::UpRoll);
		cout << "UpRun" << endl;
		break; 		 	  	  
		//=====================================================================================
	case Player::State::DownRun:		
		if (_Input->GetKey('S')) moveValue += Vector2(0.0f, 1.0f);		
		if (_Input->GetKeyUp('S')) this->ChangeState(State::DownIdle);

		if (_Input->GetKey('A')) moveValue += Vector2(-1.0f, 0.0f);		
		else if (_Input->GetKey('D')) moveValue += Vector2(1.0f, 0.0f);

		if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::DownRoll);
		cout << "DownRun" << endl;
		
		break;
		//=====================================================================================
	case Player::State::LeftRoll:
		moveValue += Vector2(-2.0f, 0.0f);

		//if(this->CreateAnimation->upRun)
		break;

	case Player::State::RightRoll:
		moveValue += Vector2(2.0f, 0.0f);
		break;

	case Player::State::UpRoll:
		moveValue += Vector2(0.0f, -2.0f);
		break;

	case Player::State::DownRoll:
		moveValue += Vector2(0.0f, 2.0f);
		break;

	default:
		break;
	}
	this->Move(moveValue);
	_mainAnimation->UpdateFrame();
	this->GetCollisionRect();
	

}

/********************************************************************************/
//## Render ##
/********************************************************************************/
void Player::Render()
{
	//이미지 사이즈 지정
	_imgMove->SetSize(_size);
	_imgAtkSword1->SetSize(_size);
	_imgAtkSword2->SetSize(_size);

	//렌더링
	_imgMove->FrameRender((int)_position.x, _position.y, _mainAnimation->GetNowFrameX(), _mainAnimation->GetNowFrameY(), Pivot::CENTER, true);

	//디버그 모드라면 디버그 렉트들 렌더링 (F1)
	if (_isDebug)
	{
		_DXRenderer->DrawRectangle(_mainRect, DefaultBrush::red, true);
		_DXRenderer->DrawRectangle(_collisionRect, DefaultBrush::red, true);
		//_DXRenderer->DrawRectangle(_obColliRect, DefaultBrush::green, true);
	}
}

/********************************************************************************/
//## ChangeState ##
//상태를 바꿀 때는 _state=state; 보다는 직접 함수를 통해서 변경하면 
//디버깅 및 코드 관리가 쉬워진다.
/********************************************************************************/
void Player::ChangeState(State state)
{
	//현 상태와 동일하다면 실행시키지 않고 빠져나간다
	if (_state == state) return;

	//현 상태와 동일하지 않다면 변경한다.
	_state = state;
	//상태가 바뀌면서 애니메이션도 변경한다
	this->ChangeAnimation(state);


	//상태가 바뀌는 순간 처리할 ..사항을 적기 위함
	switch (_state)
	{
	case Player::State::LeftIdle:
		break;
	case Player::State::RightIdle:
		break;
	case Player::State::UpIdle:
		break;
	case Player::State::DownIdle:
		break;
	case Player::State::LeftRun:
		//_speed = 300.0f;
		break;
	case Player::State::RightRun:
		break;
	case Player::State::UpRun:
		break;
	case Player::State::DownRun:
		break;
	case Player::State::LeftRoll:
		break;
	case Player::State::RightRoll:
		break;
	case Player::State::UpRoll:
		break;
	case Player::State::DownRoll:
		break;
	default:
		break;
	}
}

/********************************************************************************/
//## Move ##
//Vector2 direction:방향
/********************************************************************************/
void Player::Move(Vector2 direction)
{
	//현 좌표는 방향*스피드*델타타임
	this->_position += direction.Normalize()*_speed*_TimeManager->DeltaTime();
	//이동했으니 정밀 충돌 렉트 위치도 갱신한다.
	_collisionRect = RectMakeCenter(_position, Vector2(60.0f, 60.0f));
	
	//이동했으니 정밀 충돌 렉트 위치도 갱신한다.
	//this->_obColliRect = RectMakeBottom(_position.x, _collisionRect.bottom, 60, 10);
	
	//mainRect의 위치도 갱신
	this->UpdateMainRect();


	
	//=======================================
	//오브젝트와 충돌
	//=======================================
	vector <class GameObject*> object;
	object = _ObjectManager->GetObjectList(ObjectType::Object);
	for (int i = 0; i < object.size(); i++)
	{
		if(object[i]->GetName()!=this->_name)
		{
			if (this->InterRect(&_collisionRect, &object[i]->GetCollisionRect()))
			{
				_position.x = (_collisionRect.right - _collisionRect.left) / 2 + _collisionRect.left;
				_position.y = (_collisionRect.bottom - _collisionRect.top) / 2 + _collisionRect.top;
				_mainRect = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);
			}
		}
		
		
		
	}
	cout << _position.x << " " << _position.y << endl;
	
		//this->_obColliRect = RectMakeBottom(_position.x, _position.y, 10, 30);
}

/********************************************************************************/
//## ChangeAnimation ##
//상태에 따라 애니메이션을 바꿔준다. (키값은 State state)
/********************************************************************************/
void Player::ChangeAnimation(State state)
{
	//반복자를 통해 맵에서 해당 키값의 애니메이션을 찾는다.
	AnimationIter iter = _animationList.find(state);

	//만약 끝이 아니면 찾은 것이니 현 애니메이션을 바꿀 애니메이션으로 교체한다.
	if (iter != _animationList.end())
	{
		if (iter->second != _mainAnimation)
		{
			_mainAnimation = iter->second;
			_mainAnimation->Stop();
			_mainAnimation->Play();
		}
	}
}

/********************************************************************************/
//## CreateAnimation ##
//애니메이션 전부 미리 생성 및 초기화 해준 후 맵에 담아서 관리
/********************************************************************************/
void Player::CreateAnimation()
{
	Animation* leftIdle = new Animation;
	leftIdle->SetStartEndFrame(0, 9, 9, 9, false);
	leftIdle->SetIsLoop(true);
	leftIdle->SetFrameUpdateTime(_frameIdle);
	_animationList.insert(make_pair(State::LeftIdle, leftIdle));

	Animation* rightIdle = new Animation;
	rightIdle->SetStartEndFrame(0, 8, 9, 8, false);
	rightIdle->SetIsLoop(true);
	rightIdle->SetFrameUpdateTime(_frameIdle);
	_animationList.insert(make_pair(State::RightIdle, rightIdle));

	Animation* upIdle = new Animation;
	upIdle->SetStartEndFrame(0, 10, 9, 10, false);
	upIdle->SetIsLoop(true);
	upIdle->SetFrameUpdateTime(_frameIdle);
	_animationList.insert(make_pair(State::UpIdle, upIdle));

	Animation* downIdle = new Animation;
	downIdle->SetStartEndFrame(0, 11, 9, 11, false);
	downIdle->SetIsLoop(true);
	downIdle->SetFrameUpdateTime(_frameIdle);
	_animationList.insert(make_pair(State::DownIdle, downIdle));

	Animation* leftRun = new Animation;
	leftRun->SetStartEndFrame(0, 3, 7, 3, false);
	leftRun->SetIsLoop(true);
	leftRun->SetFrameUpdateTime(_frameRun);
	_animationList.insert(make_pair(State::LeftRun, leftRun));

	Animation* rightRun = new Animation;
	rightRun->SetStartEndFrame(0, 2, 7, 2, false);
	rightRun->SetIsLoop(true);
	rightRun->SetFrameUpdateTime(_frameRun);
	_animationList.insert(make_pair(State::RightRun, rightRun));

	Animation* upRun = new Animation;
	upRun->SetStartEndFrame(0, 0, 7, 0, false);
	upRun->SetIsLoop(true);
	upRun->SetFrameUpdateTime(_frameRun);
	_animationList.insert(make_pair(State::UpRun, upRun));

	Animation* downRun = new Animation;
	downRun->SetStartEndFrame(0, 1, 7, 1, false);
	downRun->SetIsLoop(true);
	downRun->SetFrameUpdateTime(_frameRun);
	_animationList.insert(make_pair(State::DownRun, downRun));

	Animation* leftRoll = new Animation;
	leftRoll->SetStartEndFrame(0, 5, 7, 5, false);
	leftRoll->SetIsLoop(false);
	leftRoll->SetFrameUpdateTime(_frameRun);	
	leftRoll->SetCallbackFunc([this]() {this->EndAnimation(); });	
	_animationList.insert(make_pair(State::LeftRoll, leftRoll));

	Animation* rightRoll = new Animation;
	rightRoll->SetStartEndFrame(0, 4, 7, 4, false);
	rightRoll->SetIsLoop(false);
	rightRoll->SetFrameUpdateTime(_frameRun);
	rightRoll->SetCallbackFunc([this]() {this->EndAnimation(); });	//람다식 함수 호출
	_animationList.insert(make_pair(State::RightRoll, rightRoll));

	Animation* upRoll = new Animation;
	upRoll->SetStartEndFrame(0, 6, 7, 6, false);
	upRoll->SetIsLoop(false);
	upRoll->SetFrameUpdateTime(_frameRun);
	upRoll->SetCallbackFunc([this]() {this->EndAnimation(); });		//프레임이 다 돌면 종료한다
	_animationList.insert(make_pair(State::UpRoll, upRoll));

	Animation* downRoll = new Animation;
	downRoll->SetStartEndFrame(0, 7, 7, 7, false);
	downRoll->SetIsLoop(false);
	downRoll->SetFrameUpdateTime(_frameRun);
	downRoll->SetCallbackFunc([this]() {this->EndAnimation(); });	//이 방식은 public에 선언된 애만 가능해!
	_animationList.insert(make_pair(State::DownRoll, downRoll));
}

//다해부림
bool Player::InterRect(RECT* moveRc, RECT* unMoveRc)
{
	RECT temp;
	if (!IntersectRect(&temp, moveRc, unMoveRc))
	{
		return false;
		//return false면 실행하지 않고 나가게 됨. 그래서 false는 먼저 적는게 좋음
		//reuturn을 만나면 나가는거 중요!
	}
	
	int tempWidth = temp.right - temp.left;
	int tempHeight = temp.bottom - temp.top;


	//가로길이가 더 넓다면 //상하로 부딪힌 경우이다.
	if (tempWidth > tempHeight)
	{		
		//플레이어 상->하로 충돌
		if (moveRc->bottom == temp.bottom)
		{
			//충돌지점 길이만큼 플레이어에게 더해줘서 밑으로 내린다.
			//_position.y -= tempHeight;
			moveRc->top -= tempHeight;
			moveRc->bottom -= tempHeight;
		}

		//플레이어 하->상으로 충돌
		if (moveRc->top == temp.top)
		{
			//충돌지점 길이만큼 플레이어에게 빼줘서 위로 올린다.
			//_position.y += tempHeight;
			moveRc->top += tempHeight;
			moveRc->bottom += tempHeight;
		}
	}

	//만약 세로 길이가 더 길다면 //좌우로 부딪힌 경우이다
	else if (tempHeight > tempWidth)
	{
		//return false;
		//플레이어 우->좌로 충돌
		if (moveRc->left == temp.left)
		{
			//만약 플레이어 렉트가 충돌지점보다 오른쪽에서 있다면,템프길이만큼 더해준다.
			//_position.x += tempWidth;
			moveRc->left += tempWidth;
			moveRc->right += tempWidth;
		}
		
		//플레이어 좌->우로 충돌
		else if (moveRc->right == temp.right)
		{
			//_position.x -= tempWidth;
			moveRc->left -= tempWidth;
			moveRc->right -= tempWidth;
		}
	}
	return true;
	//return true
}

//해당 상태 종료 후 변경할 상태 
void Player::EndAnimation()
{
	switch (_state)
	{
	case Player::State::LeftIdle:
		break;
	case Player::State::RightIdle:
		break;
	case Player::State::UpIdle:
		break;
	case Player::State::DownIdle:
		break;
	case Player::State::LeftRun:
		break;
	case Player::State::RightRun:
		break;
	case Player::State::UpRun:
		break;
	case Player::State::DownRun:
		break;
	case Player::State::LeftRoll:
		if(_Input->GetKey('A')) this->ChangeState(State::LeftRun);
		else					this->ChangeState(State::LeftIdle);		
		break;
	case Player::State::RightRoll:
		if (_Input->GetKey('D')) this->ChangeState(State::RightRun);
		else					this->ChangeState(State::RightIdle);
		break;
	case Player::State::UpRoll:
		if (_Input->GetKey('D')) this->ChangeState(State::UpRun);
		else					this->ChangeState(State::UpIdle);
		break;
	case Player::State::DownRoll:
		if (_Input->GetKey('D')) this->ChangeState(State::DownRun);
		else					this->ChangeState(State::DownIdle);
		break;
	default:
		break;
	}
}

/********************************************************************************/
//## IdleKeyInut ##
//Idle 상태일 때 키 입력 처리
/********************************************************************************/
void Player::IdleKeyInput()
{
	if (_Input->GetKeyDown('A'))
	{
		this->ChangeState(State::LeftRun);
	}
	else if (_Input->GetKeyDown('D'))
	{
		this->ChangeState(State::RightRun);
	}
	else if (_Input->GetKeyDown('W'))
	{
		this->ChangeState(State::UpRun);
	}
	else if (_Input->GetKeyDown('S'))
	{
		this->ChangeState(State::DownRun);
	}
}

