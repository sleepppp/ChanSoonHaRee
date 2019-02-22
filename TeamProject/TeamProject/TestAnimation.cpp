#include "stdafx.h"
#include "TestAnimation.h"

#include "Animation.h"

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
	//������ �̹��� �̹��� �޴����� ���
	//Ű��, ���,x������ �� , y�����Ӽ�
	_ImageManager->AddFrameImage("TestAnimation", L"../Resources/PlayerTest.png", 8, 2);
	//�ִϸ��̼� ��� ó������ Ŭ���� ����
	_animation = new Animation;
	//������ ������ ���
	_animation->SetStartEndFrame(0, 0, 7, 0, false);
	//�̹��� ���� ���ְ� 
	_animation->SetImage("TestAnimation");
	//�������� ����� �ð��� 0.1�ʷ� 
	_animation->SetFrameUpdateTime(0.1f);
	//���� �����ְ� 
	_animation->SetIsLoop(true);
	//function<void()> �Լ� ������(���״�� �Լ��� ���� �� �ִ� ������) 
	//���ٽ��� ����ؼ� �ʱ�ȭ ���ִµ� ���� �ڼ��� ������ ���� 
	function<void()> func = [this]() 
	{
		this->GetAnimation()->SetIsReverseX(!this->GetAnimation()->GetIsReverseX());
	};
	//�Լ� ������ �߰� 
	_animation->SetCallbackFunc(func);

	//�ʱ�ȭ �������� �ִϸ��̼� �����ض�
	_animation->Start();
}
/****************************************************************
## Release ##
����� �������� ���� 
*****************************************************************/
void TestAnimation::Release()
{
	SafeDelete(_animation);
}
/****************************************************************
## Update ##
�ִϸ��̼� ������ �����ְ� 
*****************************************************************/
void TestAnimation::Update()
{
	_animation->UpdateFrame();
}
/****************************************************************
## Render ##
�ִϸ��̼� ������ �Ѵ�.
*****************************************************************/
void TestAnimation::Render()
{
	_animation->Render(_rc);
}
