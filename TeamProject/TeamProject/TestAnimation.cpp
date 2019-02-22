#include "stdafx.h"
#include "TestAnimation.h"

#include "Animation.h"

/****************************************************************
## TestAnimation ## 
애니메이션 테스트 
*****************************************************************/
TestAnimation::TestAnimation()
{
	this->_name = "TestAnimation";
	this->_position = Vector2(WinSizeX / 2, WinSizeY / 2);
	this->_size = Vector2(200, 200);
	this->_pivot = Pivot::CENTER;
	this->UpdateRect();
}
/****************************************************************
## ~TestAnimation ##
*****************************************************************/

TestAnimation::~TestAnimation()
{
}
/****************************************************************
## Init ##
*****************************************************************/
void TestAnimation::Init()
{
	//프레임 이미지 이미지 메니져에 등록
	//키값, 경로,x프레임 수 , y프레임수
	_ImageManager->AddFrameImage("TestAnimation", L"../Resources/PlayerTest.png", 8, 2);
	//애니메이션 대신 처리해줄 클래스 생성
	_animation = new Animation;
	//프레임 정보를 등록
	_animation->SetStartEndFrame(0, 0, 7, 0, false);
	//이미지 세팅 해주고 
	_animation->SetImage("TestAnimation");
	//프레임이 감기는 시간은 0.1초로 
	_animation->SetFrameUpdateTime(0.1f);
	//루프 돌려주고 
	_animation->SetIsLoop(true);
	//function<void()> 함수 포인터(말그대로 함수를 담을 수 있는 포인터) 
	//람다식을 사용해서 초기화 해주는데 내일 자세히 설명할 예정 
	function<void()> func = [this]() 
	{
		this->GetAnimation()->SetIsReverseX(!this->GetAnimation()->GetIsReverseX());
	};
	//함수 포인터 추가 
	_animation->SetCallbackFunc(func);

	//초기화 끝냈으니 애니메이션 시작해라
	_animation->Start();
}
/****************************************************************
## Release ##
사용이 끝났으면 삭제 
*****************************************************************/
void TestAnimation::Release()
{
	SafeDelete(_animation);
}
/****************************************************************
## Update ##
애니메이션 프레임 감아주고 
*****************************************************************/
void TestAnimation::Update()
{
	_animation->UpdateFrame();
}
/****************************************************************
## Render ##
애니메이션 렌더링 한다.
*****************************************************************/
void TestAnimation::Render()
{
	_animation->Render(_rc);
}
