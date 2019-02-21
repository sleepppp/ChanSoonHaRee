#include "stdafx.h"
#include "Player.h"

/***************************************************************************************
## Player ##
기본 스피드 값 = 100.0f로 초기화
멤버 이니셜 라이즈
****************************************************************************************/
Player::Player()
	:speed(100.0f)
{

}
/***************************************************************************************
## ~Player ##
소멸자
****************************************************************************************/
Player::~Player()
{
}

/***************************************************************************************
## Init ## 
****************************************************************************************/
void Player::Init()
{
	this->name = "Player";
	this->position = Vector2(WinSizeX / 2, WinSizeY / 2);
	this->size = Vector2(50, 50);
	this->pivot = Pivot::CENTER;
	this->UpdateRect();
}
/***************************************************************************************
## Release ##
****************************************************************************************/
void Player::Release()
{
}
/***************************************************************************************
## Update ## 

_Input == KEYMANAGER 
_Input->GetKey() == KEYMANAGER->isStaykeyDown()
_Input->GetKeyDown() == KEYMANAGER->isOnceKeyDown()
_Input->GetKeyUp() == KEYMANAGER->isOnceKeyUp()
****************************************************************************************/
void Player::Update()
{
	//플레이어 이동 부분 
	if (_Input->GetKey('A'))
	{
		this->Move(Vector2(-speed, 0.f));
	}
	if (_Input->GetKey('D'))
	{
		this->Move(Vector2(speed, 0.f));
	}
	//"Enemy"라는 이름을 가진 적 객체가 생성되어 오브젝트 매니져에 
	//존재하면 해당 객체를 찾아온다.
	//FindObject함수는 찾으면 해당오브젝트 포인터를 반환하고 
	//찾지 못하면 nullptr을 반환한다 
	GameObject* enemy = _ObjectManager->FindObject("Enemy");
	//만약 nullptr이 아니라면 찾았다는 뜻이므로 
	if (enemy != nullptr)
	{
		//충돌 체크를 하고 
		RECT temp;
		if (IntersectRect(&temp, &enemy->GetRect(), &this->rc))
		{
			//충돌했다면 해당 객체의 bool isLive값을 false로 세팅해서 파괴해준다.
			enemy->SetIsLive(false);
		}
	}
}
/***************************************************************************************
## Render ##
_DXRenderer -> 전에 내가 올렸던 GIZMO클래스의 기능을 넣어놨다.
그 외에도 DXRenderer클래스에서 DirectX11,Direct2D 생성 및 초기화가 되어있지만 
우리는 우선 _DXRenderer에 도형 및 선, 텍스트 출력 함수만 사용할 줄 알면된다 일단은 
****************************************************************************************/
void Player::Render()
{
	_DXRenderer->DrawRectangle(rc, DefaultBrush::blue, true);
}
/***************************************************************************************
## Move ## 
@@ Vector2 moveValue : x,y이동량
****************************************************************************************/
void Player::Move(Vector2 moveValue)
{
	//좌표를 이동량(moveValue)만큼 움직여 주는데 DeltaTime(한 프레임당 걸린 시간을 곱해준다)
	//DeltaTime을 곱해주면 컴퓨터마다 프레임이 다르게 나오더라도 같은 속도로 움직이게 되므로 
	//컴퓨터의 프레임에 따라 어떤 상황에선 빨라지고 어떤 상황에서는 느려지는 현상이 없어지게 된다. 
	//moveValue에 들어갈 값은 결국 1초동안 움직일 양이 된다. 
	//앞으로는 프레임을 잴 때도 int count를 만들어서 ++하는 방식이 아니라 float frameTime;같은
	//변수를 만들어서 frameTime += _Time->DeltaTime()을 하자 
	//if(frameTime > 10.0f) //만약frameTime이 10초보다 커지면 같이 코딩하면된다. 
	this->position += moveValue * _Time->DeltaTime();
	this->UpdateRect();
}
