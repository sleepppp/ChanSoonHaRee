#include "stdafx.h"
#include "TestAnimation.h"

#include "Animation.h"
#include "Image.h"

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
	//이미지 등록 방법 
	_ImageManager->AddFrameImage("TestAnimation", L"../Resources/PlayerTest.png", 8, 2);
	//등록이 끝났으면 찾아서 현재 이미지 포인터에 넣어주자
	this->_image = _ImageManager->FindImage("TestAnimation");
	this->_frameCount = 0.0f;
	this->_frameX = this->_frameY = 0;
	this->_frameRate = 0.053f;
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
	////프레임 이미지 이미지 메니져에 등록
	////키값, 경로,x프레임 수 , y프레임수
	//_ImageManager->AddFrameImage("TestAnimation", L"../Resources/PlayerTest.png", 8, 2);
	////애니메이션 대신 처리해줄 클래스 생성
	//_animation = new Animation;
	////프레임 정보를 등록
	//_animation->SetStartEndFrame(0, 0, 7, 0, false);
	////이미지 세팅 해주고 
	//_animation->SetImage("TestAnimation");
	////프레임이 감기는 시간은 0.1초로 
	//_animation->SetFrameUpdateTime(0.1f);
	////루프 돌려주고 
	//_animation->SetIsLoop(true);
	////초기화 끝냈으니 애니메이션 시작해라
	//_animation->Start();
}
/****************************************************************
## Release ##
사용이 끝났으면 삭제 
*****************************************************************/
void TestAnimation::Release()
{
	//SafeDelete(_animation);
}
/****************************************************************
## Update ##
애니메이션 프레임 감아주고 
*****************************************************************/
void TestAnimation::Update()
{
	//_animation->UpdateFrame();
	//프레임 재는 시간 증가 시켜주고 
	this->_frameCount += _Time->DeltaTime();
	//프레임 재는 시간이 프레임 대기 시간보다 커질려고 하면
	if (_frameCount >= _frameRate)
	{
		//프레임 증가 해주고 
		this->_frameX++;
		//프레임 재는 시간이 프레임 대기 시간보다 커질려고 하면 
		while (_frameCount >= _frameRate)
		{
			//프레임 재는시간이 프레임 대기 시간보다 작아질때까지 빼준다.
			_frameCount -= _frameRate;
		}
		//프레임x가 최대프레임보가 커질려고 하면
		if (_frameX >= _image->GetMaxFrameX())
		{
			//프레임을 초기화해라
			this->_frameX = 0;
		}
	}
}
/****************************************************************
## Render ##
애니메이션 렌더링 한다.
*****************************************************************/
void TestAnimation::Render()
{
	static float angle = 0.0f;
	if (_image != nullptr)
	{
		_image->SetSize(_size);
		_image->SetAngle(angle);
		_image->FrameRender(_position.x,_position.y, _frameX, _frameY, Pivot::CENTER, true);
		_DXRenderer->DrawRectangle(_rc, DefaultBrush::blue, true,3.0f);
	}

	ImGui::Begin("TestAnimation");
	{
		ImGui::Text("FrameX : %d", _frameX);
		ImGui::SliderFloat("Angle", &angle, 0.0f, 360.f);
		ImGui::SliderFloat("FrameRate", &_frameRate, 0.001f, 1.0f);
	}
	ImGui::End();
	//_animation->Render(_rc);
}
