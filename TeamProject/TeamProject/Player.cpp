#include "stdafx.h"
#include "Player.h"

#include "Image.h"
#include "Animation.h"
#include "Timer.h"
#include "Enemy.h"
#include "MoveItem.h"
#include "Inventory.h"
#include "Arrow.h"
#include "Effect.h"


//에너미 공ㅇ격 받을때 무적 판정(약 1초)	ok
//에너미 데미지 값 받을 함수				ok
//맞으면 알파값 깜빡임							ok		
//무기 보우, 방패
//한번만 칼 휘두르게
//두번 누를때 두번 휘두르게
//휘두르는 동안 제대로 렉트가 한번씩 먹히도록 수정한다.

//0310:보스 생성(최초) 이미지에서 뒷쪽으로 살짝 튀는 프레임 두어개쯤 있음
//대각선 롤링 완료
//칼 나누어서 휘두르기 어색해서 재수정

using namespace Figure;

//씬 변경으로 TItleScene에서 TitleObject의 TitleFlowObject.cpp
//23,27번 Dungeon_map_02 맵으로 수정함 

Player::Player(Vector2 pos)
{
	//이미지 추가, 매니저에서 FInd 하여 찾아옴
	_ImageManager->AddFrameImage("Will", L"../Resources/Player/will_dungeon.png", 10, 13);
	this->_imgMove = _ImageManager->FindImage("Will");
	_ImageManager->AddFrameImage("Will_Sword", L"../Resources/Player/will_sword.png", 11, 4);
	this->_imgAtkSword = _ImageManager->FindImage("Will_Sword");
	_ImageManager->AddFrameImage("Will_Bow", L"../Resources/Player/will_bow.png", 9, 4);
	this->_imgAtkBow = _ImageManager->FindImage("Will_Bow");


	//기본 변수 초기화
	this->_name = "Will";
	this->_size = Vector2(120, 120);
	this->_position = Vector2(627, 120);
	this->_position = pos;	//따로값 입력 안하면 메인신에서 값을 입력한대로
	this->_isActive = true;
	this->_pivot = Pivot::CENTER;
	this->_speed = 400.0f;
	this->UpdateMainRect();
	this->_maxHp = 100;
	this->_currentHp = 50;
	this->_isMoveStop = false;			//움직임을 멈추기 위한 bool값
	this->_isChangeSword = false;		//공격시 이미지 파일 변경을 위한 bool값
	this->_isChangeBow = false;			//활 공격시 이미지 파일 변경을 위한 bool값
	this->_isStandardMove = true;
	this->_damage = 20;					//플레이어 기본 무기 데미지

	this->_frameIdle = 0.1f;			//스피드 변경을 위한 변수
	this->_frameRun = 0.1f;				//스피드 변경을 위한 변수
	this->_frameBow = 0.08f;
	this->_swordWidth= 40;
	this->_swordHeight= 20;

	this->_isAttacked = false;
	this->_isChangeWeapon = false;		//false는 칼, true는 활
	_blink = 0;
	this->_alpha = 1.0f;

	this->_isDelay = 0.f;
	this->_count = 0;
	//정밀 충돌용 렉트 위치 초기화
	this->_collisionRect = RectMakeCenter(_position, Vector2(60.f, 60.f));	
	//상태별 애니메이션 전부 생성하여 맵에 담아둔다.
	this->CreateAnimation();

	// 처음 시작 상태를 위한 세팅
	this->ChangeState(State::DownIdle);

	//화살 클래스
	//_arrow = new Arrow(_pos, state);
	
}
Player::~Player() {}

/********************************************************************************/
//## Init ##
/********************************************************************************/
void Player::Init()
{	
	//AddCallbackMessage("InventoryOpen", [this](TagMessage message) {this->InventoryOnOff(); });
	AddCallbackMessage("InventoryClose", [this](TagMessage message) {this->InventoryOnOff(); });
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
	
	if (_isMoveStop == false)
	{
		if (_Input->GetKeyDown('I'))
		{
			GameObject* _inventory = (Inventory*)_ObjectManager->FindObject(ObjectType::UI, "Inventory");
			_isMoveStop = true;
			_inventory->SetActive(true);	
		}

		//무기 변경(칼<->활)
		if (_Input->GetKeyDown('Z'))
		{
			_isChangeBow = !_isChangeBow;
			
			//테스트용
			if (_isChangeBow)cout << "Bow" << endl;
			else  if (!_isChangeBow)cout << "Sword" << endl;
		}

		//&&&&&&공격 무브 OK
		//상태에 따라 다르게 업데이트
		switch (_state)
		{
		case Player::State::LeftIdle:
			if (_Input->GetKey('A')) this->ChangeState(State::LeftRun);
			else if (_Input->GetKey('D')) this->ChangeState(State::RightRun);
			else if (_Input->GetKey('W')) this->ChangeState(State::UpRun);
			else if (_Input->GetKey('S')) this->ChangeState(State::DownRun);
			else if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::LeftRoll);
			else if (!_isChangeBow && _Input->GetKey('J')) this->ChangeState(State::LeftSword1);
			else if (_isChangeBow && _Input->GetKey('J')) this->ChangeState(State::LeftBow);
			//else if(_Input->GetKeyDown('Z'))
			break;

		case Player::State::RightIdle:
			if (_Input->GetKey('A')) this->ChangeState(State::LeftRun);
			else if (_Input->GetKey('D')) this->ChangeState(State::RightRun);
			else if (_Input->GetKey('W')) this->ChangeState(State::UpRun);
			else if (_Input->GetKey('S')) this->ChangeState(State::DownRun);
			else if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::RightRoll);
			else if (!_isChangeBow && _Input->GetKey('J')) this->ChangeState(State::RightSword1);
			else if (_isChangeBow && _Input->GetKey('J')) this->ChangeState(State::RightBow);
			break;

		case Player::State::UpIdle:
			if (_Input->GetKey('A')) this->ChangeState(State::LeftRun);
			else if (_Input->GetKey('D')) this->ChangeState(State::RightRun);
			else if (_Input->GetKey('W')) this->ChangeState(State::UpRun);
			else if (_Input->GetKey('S')) this->ChangeState(State::DownRun);
			else if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::UpRoll);
			else if (!_isChangeBow&&_Input->GetKey('J')) this->ChangeState(State::UpSword1);
			else if (_isChangeBow&& _Input->GetKey('J')) this->ChangeState(State::UpBow);
			break;

		case Player::State::DownIdle:
			if (_Input->GetKey('A')) this->ChangeState(State::LeftRun);
			else if (_Input->GetKey('D')) this->ChangeState(State::RightRun);
			else if (_Input->GetKey('W')) this->ChangeState(State::UpRun);
			else if (_Input->GetKey('S')) this->ChangeState(State::DownRun);
			else if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::DownRoll);
			else if (!_isChangeBow&&_Input->GetKey('J')) this->ChangeState(State::DownSword1);
			else if (_isChangeBow&&_Input->GetKey('J')) this->ChangeState(State::DownBow);
			break;

		case Player::State::LeftRun:
			if (_Input->GetKey('A')) moveValue += Vector2(-1.0f, 0.0f);		//왼누르기
			if (_Input->GetKeyUp('A')) this->ChangeState(State::LeftIdle); //왼떼기

			//대각선 시작		
			if (_Input->GetKey('W'))										//대각선 위 누르기
			{
				ChangeAnimation(Player::State::UpRun);
				moveValue += Vector2(0.0f, -1.0f);
			}
			else if (_Input->GetKey('S'))									//대각선 아래 누르기
			{
				moveValue += Vector2(0.0f, 1.0f);
				ChangeAnimation(Player::State::DownRun);
			}

			if (_Input->GetKeyUp('W'))			//대각선 위 떼기
			{
				ChangeAnimation(Player::State::LeftRun);
			}
			else if (_Input->GetKeyUp('S'))			//대각선 아래 떼기
			{
				this->ChangeState(State::LeftRun);
			}

			if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::LeftRoll);
			if (!_isChangeBow&&_Input->GetKey('J')) this->ChangeState(State::LeftSword1);
			else if(_isChangeBow&&_Input->GetKey('J')) this->ChangeState(State::LeftBow);
			break;

		case Player::State::RightRun:
			if (_Input->GetKey('D')) moveValue += Vector2(1.0f, 0.0f);
			if (_Input->GetKeyUp('D')) this->ChangeState(State::RightIdle);
			
			//대각선 시작
			if (_Input->GetKey('W'))	//대각선 위
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
			}
			else if (_Input->GetKeyUp('S'))
			{
				ChangeAnimation(Player::State::RightRun);
			}
			if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::RightRoll);
			if (!_isChangeBow&&_Input->GetKey('J')) this->ChangeState(State::RightSword1);
			else if (_isChangeBow&&_Input->GetKey('J')) this->ChangeState(State::RightBow);
			break;

		case Player::State::UpRun:
			if (_Input->GetKey('W')) moveValue += Vector2(0.0f, -1.0f);
			if (_Input->GetKeyUp('W')) this->ChangeState(State::UpIdle);

			if (_Input->GetKey('A')) moveValue += Vector2(-1.0f, 0.0f);
			else if (_Input->GetKey('D')) moveValue += Vector2(1.0f, 0.0f);

			if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::UpRoll);
			if (!_isChangeBow&&_Input->GetKey('J')) this->ChangeState(State::UpSword1);
			else if (_isChangeBow&&_Input->GetKey('J')) this->ChangeState(State::UpBow);
			break;

		case Player::State::DownRun:
			if (_Input->GetKey('S')) moveValue += Vector2(0.0f, 1.0f);
			if (_Input->GetKeyUp('S')) this->ChangeState(State::DownIdle);

			if (_Input->GetKey('A')) moveValue += Vector2(-1.0f, 0.0f);
			else if (_Input->GetKey('D')) moveValue += Vector2(1.0f, 0.0f);

			if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::DownRoll);
			if (!_isChangeBow&&_Input->GetKey('J')) this->ChangeState(State::DownSword1);
			else if (_isChangeBow&&_Input->GetKey('J')) this->ChangeState(State::DownBow);
			break;

			//=====================================================================================
		case Player::State::LeftRoll:
			moveValue += Vector2(-2.0f, 0.0f);

			//대각선 시작		
			if (_Input->GetKey('W'))										//대각선 위 누르기
			{
				moveValue += Vector2(0.0f, -2.0f);
			}
			else if (_Input->GetKey('S'))										//대각선 위 누르기
			{
				moveValue += Vector2(0.0f, 2.0f);
			}
			break;

		case Player::State::RightRoll:
			moveValue += Vector2(2.0f, 0.0f);

			//대각선 시작		
			if (_Input->GetKey('W'))										//대각선 위 누르기
			{
				moveValue += Vector2(0.0f, -2.0f);
			}
			else if (_Input->GetKey('S'))										//대각선 위 누르기
			{
				moveValue += Vector2(0.0f, 2.0f);
			}
			break;

		case Player::State::UpRoll:
			moveValue += Vector2(0.0f, -2.0f);

			//대각선 시작		
			if (_Input->GetKey('A'))										//대각선 위 누르기
			{
				moveValue += Vector2(-2.0f, 0.0f);
			}
			else if (_Input->GetKey('D'))										//대각선 위 누르기
			{
				moveValue += Vector2(2.0f, 0.0f);
			}
			break;

		case Player::State::DownRoll:
			moveValue += Vector2(0.0f, 2.0f);

			//대각선 시작		
			if (_Input->GetKey('A'))										//대각선 위 누르기
			{
				moveValue += Vector2(-2.0f, 0.0f);
			}
			else if (_Input->GetKey('D'))										//대각선 위 누르기
			{
				moveValue += Vector2(2.0f, 0.0f);
			}


			break;
			//=====================================================================================
		case Player::State::LeftSword1:			
			this->Attack();
			break;

		case Player::State::RightSword1:			
			this->Attack();
			break;

		case Player::State::UpSword1:			
			this->Attack();
			break;

		case Player::State::DownSword1:			
			this->Attack();
			break;
			//=====================================================================================
		case Player::State::LeftSword2:
			this->Attack();
			break;

		case Player::State::RightSword2:
			this->Attack();
			break;

		case Player::State::UpSword2:
			this->Attack();
			break;

		case Player::State::DownSword2:
			this->Attack();
			break;

		case Player::State::LeftBow:		
			this->Enable();
			break;

		case Player::State::RightBow:
			//_ObjectManager->FindObject(ObjectType::Object, new Arrow(Vector2(_position), Arrow::State::Right));
			break;

		case Player::State::UpBow:
			//_ObjectManager->FindObject(ObjectType::Object, new Arrow(Vector2(_position), Arrow::State::Up));
			break;
			
		case Player::State::DownBow:
			//_ObjectManager->FindObject(ObjectType::Object, new Arrow(Vector2(_position), Arrow::State::Down));




		default:
			break;
		}

		//이동 및 충돌관련 함수 호출함
		this->Move(moveValue);
	}

	//프레임을 업데이트 해준다.
	_mainAnimation->UpdateFrame();
	
	//공격 판정 이후 처리 함수
	this->AtkDelay2();

}

/********************************************************************************/
//## Render ##
/********************************************************************************/
void Player::Render()
{
	//이미지 사이즈 지정
	_imgMove->SetSize(_size);
	_imgAtkSword->SetSize(_size);
	_imgAtkBow->SetSize(_size);
	//알파값을 받아오기위한 선언
	_imgMove->SetAlpha(_alpha);

	//렌더링: 두개의 이미지를 상황에 맞게 번갈아가면서 사용하도록 조건을 준다.
	//무기 교체만 하는 상태에도 기본 무브 사용해야 하므로 공격 버튼 누를때만 렌더하도록 다른 조건을 줄 것
	
	if (_isStandardMove == true)
	{
		_imgMove->FrameRender((int)_position.x, _position.y, _mainAnimation->GetNowFrameX(), _mainAnimation->GetNowFrameY(), Pivot::CENTER, true);
	}
	else if (_isChangeSword == true)
	{		
		_imgAtkSword->FrameRender((int)_position.x, _position.y, _mainAnimation->GetNowFrameX(), _mainAnimation->GetNowFrameY(), Pivot::CENTER, true);
	}	
	else if (_isChangeBow == true)
	{
		_imgAtkBow->FrameRender((int)_position.x, _position.y, _mainAnimation->GetNowFrameX(), _mainAnimation->GetNowFrameY(), Pivot::CENTER, true);
		//_arrow->Render();
	}
	
	//디버그 모드라면 디버그 렉트들 렌더링 (F1)
	if (_isDebug)
	{
		_DXRenderer->DrawRectangle(_mainRect, DefaultBrush::red, true);
		_DXRenderer->DrawRectangle(_collisionRect, DefaultBrush::red, true);
		//공격모션(이미지)가 true이고 공격판정이 false일때만 그린다
		
		if (_isChangeSword && !_isAttacked)_DXRenderer->DrawRectangle(_swordRect, DefaultBrush::green, true);
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
	//'I'버튼을 누르면 움직이지 않고 멈춤
	if (_isMoveStop == true) return;

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
		_isChangeSword = false;		
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
	case Player::State::RightIdle:
		_isChangeSword = false;
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
	case Player::State::UpIdle:
		_isChangeSword = false;
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
	case Player::State::DownIdle:
		_isChangeSword = false;
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
	case Player::State::LeftRun:
		_isChangeSword = false;
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
	case Player::State::RightRun:
		_isChangeSword = false;
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
	case Player::State::UpRun:
		_isChangeSword = false;
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
	case Player::State::DownRun:
		_isChangeSword = false;
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
	case Player::State::LeftRoll:
		_isChangeSword = false;
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
	case Player::State::RightRoll:
		_isChangeSword = false;
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
	case Player::State::UpRoll:
		_isChangeSword = false;
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
	case Player::State::DownRoll:
		_isChangeSword = false;
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
		//======================================================
	case Player::State::LeftSword1:
		_isChangeSword = true;		
		//_isChangeBow = false;
		_isAttacked = false;
		_isStandardMove = false;
		//if(_isChangeSword)this->_swordRect = RectMakeCenter(_position.x - 40, _position.y, _swordWidth, _swordHeight); //칼 렉트
		if (_isChangeSword)this->_swordRect = RectMakeCenter(_position.x - 40, _position.y, _swordWidth, _swordHeight); //칼 렉트
		break;
	case Player::State::RightSword1:
		_isChangeSword = true;
		//_isChangeBow = false;
		_isAttacked = false;	
		_isStandardMove = false;
		if (_isChangeSword)this->_swordRect = RectMakeCenter(_position.x + 40, _position.y, _swordWidth, _swordHeight); //칼 렉트 
		break;
	case Player::State::UpSword1:
		_isChangeSword = true;	
		//_isChangeBow = false;
		_isAttacked = false;	
		_isStandardMove = false;
		if (_isChangeSword)this->_swordRect = RectMakeCenter(_position.x, _position.y - 40, _swordHeight, _swordWidth); //칼 렉트
		break;
	case Player::State::DownSword1:
		_isChangeSword = true;
		//_isChangeBow = false;
		_isAttacked = false;
		_isStandardMove = false;
		if (_isChangeSword)this->_swordRect = RectMakeCenter(_position.x, _position.y + 40, _swordHeight, _swordWidth); //칼 렉트
		break;
		//======================================================
	case Player::State::LeftSword2:
		_isChangeSword = true;
		//_isChangeBow = false;
		_isAttacked = false;
		_isStandardMove = false;
		if (_isChangeSword)this->_swordRect = RectMakeCenter(_position.x - 40, _position.y, _swordWidth, _swordHeight); //칼 렉트
		break;
	case Player::State::RightSword2:
		_isChangeSword = true;
		//_isChangeBow = false;
		_isAttacked = false;
		_isStandardMove = false;
		if (_isChangeSword)this->_swordRect = RectMakeCenter(_position.x + 40, _position.y, _swordWidth, _swordHeight);  //칼 렉트
		break;
	case Player::State::UpSword2:
		_isChangeSword = true;
		//_isChangeBow = false;
		_isAttacked = false;
		_isStandardMove = false;
		if (_isChangeSword)this->_swordRect = RectMakeCenter(_position.x, _position.y - 40, _swordHeight, _swordWidth);  //칼 렉트
		break;
	case Player::State::DownSword2:
		_isChangeSword = true;
		//_isChangeBow = false;
		_isAttacked = false;
		_isStandardMove = false;
		if (_isChangeSword)this->_swordRect = RectMakeCenter(_position.x, _position.y + 40, _swordHeight, _swordWidth);  //칼 렉트
		break;
		//======================================================
	case Player::State::LeftBow:
		_isChangeSword = false;
		//_isChangeBow = true;
		_isStandardMove = false;
		_ObjectManager->AddObject(ObjectType::Object, new Arrow(Vector2(_position), Arrow::State::Left));
		break;

	case Player::State::RightBow:
		_isChangeSword = false;
		//_isChangeBow = true;
		_isStandardMove = false;
		_ObjectManager->AddObject(ObjectType::Object, new Arrow(Vector2(_position), Arrow::State::Right));
		break;

	case Player::State::UpBow:
		_isChangeSword = false;
		//_isChangeBow = true;
		_isStandardMove = false;
		_ObjectManager->AddObject(ObjectType::Object, new Arrow(Vector2(_position), Arrow::State::Up));
		break;

	case Player::State::DownBow:
		_isChangeSword = false;
		//_isChangeBow = true;
		_isStandardMove = false;
		_ObjectManager->AddObject(ObjectType::Object, new Arrow(Vector2(_position), Arrow::State::Down));
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
	//이동하지 않았다면 Float EQUAL에 소수점오차값으로 확인하여 이동을 하지 않았다면 return처리하여 빠져나간다.
	if (FLOAT_EQUAL(direction.x,0.f) && FLOAT_EQUAL(direction.y,0.f))
		return;

	//현 좌표는 방향*스피드*델타타임
	this->_position += direction.Normalize()*_speed*_TimeManager->DeltaTime();
	//이동했으니 정밀 충돌 렉트 위치도 갱신한다.
	_collisionRect = RectMakeCenter(_position, Vector2(60.0f, 60.0f));
	
	//mainRect의 위치도 갱신
	this->UpdateMainRect();	
	
	//=======================================
	//오브젝트와 충돌(InterRect함수 사용)
	//=======================================
	const vector <class GameObject*>* object;
	object = _ObjectManager->GetObjectListPointer(ObjectType::Object);
	
	//모든 오브젝트를  for문으로 충돌 검사를 해준다.
	//enemy와의 충돌도 담음
	//enemy가 값을 호출하면(!=) 충돌 검사를 한다.
	for (int i = 0; i < object->size(); i++)
	{
		//플레이어 자신을 제외하기 위한 조건문
		if(object->at(i)->GetName()!=this->_name)
		{
			//에너미 클래스 형변환으로 오브젝트 i로 불러온다.
			Enemy* enemy = dynamic_cast<Enemy*>(object->at(i));
			//아이템 클래스 형변환으로 오브젝트 i로 불러온다.
			MoveItem* item = dynamic_cast<MoveItem*>(object->at(i));
				
			//값 반환이 없는 빈 내용물이 아닌 경우에만 사용한다.
			if (enemy == nullptr && item == nullptr)
			{
				//만든 함수 InterRee로 플레이어 충돌용 함수와 전체 오브젝트를 충돌 검사한다.
				if (this->InterRee(&_collisionRect, &object->at(i)->GetCollisionRect()))
				{
					//충돌한 캐릭터 플레이어를 반대로 밀어주면서 그자리에 머문것처럼 한다.
					_position.x = (_collisionRect.right - _collisionRect.left) / 2 + _collisionRect.left;
					_position.y = (_collisionRect.bottom - _collisionRect.top) / 2 + _collisionRect.top;
					_mainRect = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);
				}
			}
		}
	}	
	//에너미와의 충돌	
	//this->SendCallbackMessage(TagMessage("PlayerHP",0.0f, this->_currentHp));
	
	//Enemy* enemy = dynamic_cast<Enemy*>(object[i]);
	//Enemy 클래스를 가리키는 enemy에 담는다.
	//dynamic_case다이나믹 캐스(상속관계일 경우 형변환(ex: (float)hp ), 없으면 null값을 반환해줘서 편리!)
	//<Enemy*> 데이터 타입에... 에너미를 가리키는 클래스를 담았나?
	//해당 오브젝트 배열[i]로 호출
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
	Animation* leftIdle = new Animation;							//상태별로 하나씩 new로 맹들었지렁
	leftIdle->SetStartEndFrame(0, 9, 9, 9, false);					//한동작의 시작x,y,끝x,y 저억으시오
	leftIdle->SetIsLoop(true);										//루프돌릴지 true, faㅣse
	leftIdle->SetFrameUpdateTime(_frameIdle);						//프레임당 시간을 넣어주면 됨미다
	_animationList.insert(make_pair(State::LeftIdle, leftIdle));	//값 다 만드셨으면 inset로 맵에 콱 박으쇼

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
	//======================================================================
	Animation* leftSword1 = new Animation;
	leftSword1->SetStartEndFrame(0, 3, 4, 3, false);
	leftSword1->SetIsLoop(false);
	leftSword1->SetFrameUpdateTime(_frameRun);
	leftSword1->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::LeftSword1, leftSword1));

	Animation* rightSword1 = new Animation;
	rightSword1->SetStartEndFrame(0, 2, 4, 2, false);
	rightSword1->SetIsLoop(false);
	rightSword1->SetFrameUpdateTime(_frameRun);
	rightSword1->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::RightSword1, rightSword1));

	Animation* upSword1 = new Animation;
	upSword1->SetStartEndFrame(0, 0, 4, 0, false);
	upSword1->SetIsLoop(false);
	upSword1->SetFrameUpdateTime(_frameRun);
	upSword1->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::UpSword1, upSword1));

	Animation* downSword1 = new Animation;	
	downSword1->SetStartEndFrame(0, 1, 4, 1, false);
	downSword1->SetIsLoop(false);
	downSword1->SetFrameUpdateTime(_frameRun);
	downSword1->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::DownSword1, downSword1));
	//=======================================================================
	Animation* leftSword2 = new Animation;
	leftSword2->SetStartEndFrame(5, 3, 10, 3, false);
	leftSword2->SetIsLoop(false);
	leftSword2->SetFrameUpdateTime(_frameRun);
	leftSword2->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::LeftSword2, leftSword2));

	Animation* rightSword2 = new Animation;
	rightSword2->SetStartEndFrame(5, 2, 10, 2, false);
	rightSword2->SetIsLoop(false);
	rightSword2->SetFrameUpdateTime(_frameRun);
	rightSword2->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::RightSword2, rightSword2));

	Animation* upSword2 = new Animation;
	upSword2->SetStartEndFrame(5, 0, 10, 0, false);
	upSword2->SetIsLoop(false);
	upSword2->SetFrameUpdateTime(_frameRun);
	upSword2->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::UpSword2, upSword2));

	Animation* downSword2 = new Animation;
	downSword2->SetStartEndFrame(5, 1, 10, 1, false);
	downSword2->SetIsLoop(false);
	downSword2->SetFrameUpdateTime(_frameRun);
	downSword2->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::DownSword2, downSword2));
	//=====================================================================================
	Animation* leftBow = new Animation;
	leftBow->SetStartEndFrame(0, 3, 8, 3, false);
	leftBow->SetIsLoop(false);
	leftBow->SetFrameUpdateTime(_frameBow);
	leftBow->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::LeftBow, leftBow));

	Animation* rightBow = new Animation;
	rightBow->SetStartEndFrame(0, 2, 8, 2, false);
	rightBow->SetIsLoop(false);
	rightBow->SetFrameUpdateTime(_frameBow);
	rightBow->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::RightBow, rightBow));

	Animation* upBow = new Animation;
	upBow->SetStartEndFrame(0, 0, 8, 0, false);
	upBow->SetIsLoop(false);
	upBow->SetFrameUpdateTime(_frameBow);
	upBow->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::UpBow, upBow));

	Animation* downBow = new Animation;
	downBow->SetStartEndFrame(0, 1, 8, 1, false);
	downBow->SetIsLoop(false);
	downBow->SetFrameUpdateTime(_frameBow);
	downBow->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::DownBow, downBow));

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
		if (_Input->GetKey('W')) this->ChangeState(State::UpRun);
		else					this->ChangeState(State::UpIdle);
		break;
	case Player::State::DownRoll:
		if (_Input->GetKey('S')) this->ChangeState(State::DownRun);
		else					this->ChangeState(State::DownIdle);
		break;
		//================================================================
	case Player::State::LeftSword1:
		if (_Input->GetKey('J')) this->ChangeState(State::LeftSword2);
		else if (_Input->GetKeyDown('J')) this->ChangeState(State::LeftSword2);
		else if (_Input->GetKey('A')) this->ChangeState(State::LeftRun);
		else					this->ChangeState(State::LeftIdle);
		break;
	case Player::State::RightSword1:
		if (_Input->GetKey('J')) this->ChangeState(State::RightSword2);
		else if (_Input->GetKey('D')) this->ChangeState(State::RightRun);
		else					this->ChangeState(State::RightIdle);
		break;
	case Player::State::UpSword1:
		if (_Input->GetKey('J')) this->ChangeState(State::UpSword2);
		else if (_Input->GetKey('W')) this->ChangeState(State::UpRun);
		else					this->ChangeState(State::UpIdle);
		break;
	case Player::State::DownSword1:
		if (_Input->GetKey('J')) this->ChangeAnimation(State::DownSword2);
		else if (_Input->GetKey('S')) this->ChangeState(State::DownRun);
		else					this->ChangeState(State::DownIdle);
		break;
		//================================================================
	case Player::State::LeftSword2:
		if (_Input->GetKey('J')) this->ChangeAnimation(State::LeftSword1);
		else if (_Input->GetKey('A')) this->ChangeState(State::LeftRun);
		else					this->ChangeState(State::LeftIdle);
		break;
	case Player::State::RightSword2:
		if (_Input->GetKey('J')) this->ChangeAnimation(State::RightSword1);
		else if (_Input->GetKey('D')) this->ChangeState(State::RightRun);
		else					this->ChangeState(State::RightIdle);
		break;
	case Player::State::UpSword2:
		if (_Input->GetKey('J')) this->ChangeAnimation(State::UpSword1);
		else if (_Input->GetKey('W')) this->ChangeState(State::UpRun);
		else					this->ChangeState(State::UpIdle);
		break;
	case Player::State::DownSword2:
		if (_Input->GetKey('J')) this->ChangeAnimation(State::DownSword1);
		else if (_Input->GetKey('S')) this->ChangeState(State::DownRun);
		else					this->ChangeState(State::DownIdle);		
		break;
		//==============================================================
	case Player::State::LeftBow:
		if (_Input->GetKeyDown('J')) this->ChangeState(State::LeftBow);
		//else if (_Input->GetKey('A')) this->ChangeAnimation(State::LeftRun);
		else							this->ChangeState(State::LeftIdle);
		break;

	case Player::State::RightBow:
		if (_Input->GetKeyDown('J')) this->ChangeState(State::RightBow);
		//else if (_Input->GetKey('S')) this->ChangeAnimation(State::RightRun);
		else
		{
			this->ChangeState(State::RightIdle);
		}

		break;

	case Player::State::UpBow:
		if (_Input->GetKeyDown('J')) this->ChangeState(State::UpBow);
		//else if (_Input->GetKey('S')) this->ChangeAnimation(State::UpRun);
		else						this->ChangeState(State::UpIdle);
		break;

	case Player::State::DownBow:
		if (_Input->GetKeyDown('J')) this->ChangeState(State::DownBow);
		else
		{
			this->ChangeState(State::DownIdle);
		}
		break;

	default:
		break;
	}
}

/********************************************************************************/
//## InterRect ##
//오브젝트와 충돌을 위한 함수
/********************************************************************************/
bool Player::InterRee(RECT* moveRc, RECT* unMoveRc)
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

//=======================================
//플레이어 위치 전달 함수 (인벤용 XY값 전달)
//=======================================
POINT Player::GetPlayerIndex()
{
	POINT IndexXY = { _mainAnimation->GetNowFrameX(), _mainAnimation->GetNowFrameY() };
	return IndexXY;
}

//=======================================
//검 공격함수
//=======================================
void Player::Attack()
{
	if (_isAttacked == false)
	{
		const vector <class GameObject*>* object;
		object = _ObjectManager->GetObjectListPointer(ObjectType::Object);
		for (int i = 0; i < object->size(); i++)
		{
			//플레이어 자신을 제외하기 위한 조건문
			if (object->at(i)->GetName() != this->_name)
			{
				Enemy* enemy = dynamic_cast<Enemy*>(object->at(i));

				//무기와 에너미 충돌, 가져온 오브젝트에 값이 있을 경우만 검사
				if (enemy != nullptr)
				{
					RECT temp;
					if (IntersectRect(&temp, &_swordRect, &object->at(i)->GetCollisionRect()))
					{
						//충돌했을때 false상태일때(그 전에 충돌 상태가 아니었을때)

						//데미지값을 받아서 체력을 깎는다
						enemy->AttackedDemege(_damage);
						_isAttacked = true;
					}
				}
			}

			if (_isAttacked == true)
			{
				Effect::PlayEffect(EFFECT_SWORDATK, Vector2(_swordRect.left, _swordRect.top));
			}
		}
	}

}

//=======================================
//인벤토리 on/off 버튼용 함수
//=======================================
void Player::InventoryOnOff()
{
	_isMoveStop = false;
}

//=======================================
//데미지값 받아서 플레이어 체력을 깎는 함수
//조건은 에너미에서, 이 함수를 받아 체력이 깎이면 무기와 플레이어 몸체가 충돌한 것
//=======================================
void Player::AttackedDamage(int damage)
{
	if (_isDelay == false)
	{
		cout << "Fucking " << endl;
		this->_currentHp -= damage;
		_isDelay = true;
		_blink = 0;
	}	
}

//=======================================
//에너미와 충돌시, 무적시간 부여/플레이어 깜빡임 함수
//=======================================
void Player::AtkDelay2()
{	
	if (_isDelay == true)
	{
		_count += _TimeManager->DeltaTime();
		if (_count > 0.2f)
		{
			_blink++;
			_count = 0;
			_alpha = !_alpha;
			
			if (_blink == 6)
			{
				_isDelay = false;
				_alpha = 1.0f;
			}
		}
		
	}
}