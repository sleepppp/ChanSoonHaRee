#include "stdafx.h"
#include "TestAnimation.h"

#include "Animation.h"
#include "Image.h"

/****************************************************************
## TestAnimation ## 
�ִϸ��̼� �׽�Ʈ 
*****************************************************************/
TestAnimation::TestAnimation()
{
	this->_name = "TestAnimation";
	this->_position = Vector2(WinSizeX / 2, WinSizeY / 2);
	this->_size = Vector2(200, 200);
	this->_pivot = Pivot::CENTER;
	this->UpdateRect();
	//�̹��� ��� ��� 
	_ImageManager->AddFrameImage("TestAnimation", L"../Resources/PlayerTest.png", 8, 2);
	//����� �������� ã�Ƽ� ���� �̹��� �����Ϳ� �־�����
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
	////������ �̹��� �̹��� �޴����� ���
	////Ű��, ���,x������ �� , y�����Ӽ�
	//_ImageManager->AddFrameImage("TestAnimation", L"../Resources/PlayerTest.png", 8, 2);
	////�ִϸ��̼� ��� ó������ Ŭ���� ����
	//_animation = new Animation;
	////������ ������ ���
	//_animation->SetStartEndFrame(0, 0, 7, 0, false);
	////�̹��� ���� ���ְ� 
	//_animation->SetImage("TestAnimation");
	////�������� ����� �ð��� 0.1�ʷ� 
	//_animation->SetFrameUpdateTime(0.1f);
	////���� �����ְ� 
	//_animation->SetIsLoop(true);
	////�ʱ�ȭ �������� �ִϸ��̼� �����ض�
	//_animation->Start();
}
/****************************************************************
## Release ##
����� �������� ���� 
*****************************************************************/
void TestAnimation::Release()
{
	//SafeDelete(_animation);
}
/****************************************************************
## Update ##
�ִϸ��̼� ������ �����ְ� 
*****************************************************************/
void TestAnimation::Update()
{
	//_animation->UpdateFrame();
	//������ ��� �ð� ���� �����ְ� 
	this->_frameCount += _Time->DeltaTime();
	//������ ��� �ð��� ������ ��� �ð����� Ŀ������ �ϸ�
	if (_frameCount >= _frameRate)
	{
		//������ ���� ���ְ� 
		this->_frameX++;
		//������ ��� �ð��� ������ ��� �ð����� Ŀ������ �ϸ� 
		while (_frameCount >= _frameRate)
		{
			//������ ��½ð��� ������ ��� �ð����� �۾��������� ���ش�.
			_frameCount -= _frameRate;
		}
		//������x�� �ִ������Ӻ��� Ŀ������ �ϸ�
		if (_frameX >= _image->GetMaxFrameX())
		{
			//�������� �ʱ�ȭ�ض�
			this->_frameX = 0;
		}
	}
}
/****************************************************************
## Render ##
�ִϸ��̼� ������ �Ѵ�.
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
