#include "stdafx.h"
#include "ProgressBar.h"


ProgressBar::ProgressBar()
{
}


ProgressBar::~ProgressBar()
{
}

void ProgressBar::Init()
{	
	//HP바 이미지 프레임렌더
	_progressBarBackIMG = _ImageManager->AddFrameImage("hpBar1", L"../Resouces/UI/hpBar", 1, 6, false);
	_progressBarFrontIMG = _ImageManager->AddFrameImage("hpBar2", L"../Resouces/UI/hpBar", 1, 6, false);

	//클래스 키 이름 선언
	this->_name = "ProgressBar";

	//포지션 초기화
	this->_position = Vector2(0, 0);
	//렉트 생성
	this->_mainRect = Figure::RectMake(_position.x, _position.y, _progressBarBackIMG->GetWidth(), _progressBarBackIMG->GetHeight());
	
	//이미지 프레임 초기화 
	_imgFrameX = 0;
	_imgFrameY = 0;

	//테스트용 인자 초기화
	_testCurrentHp = 50;
	_testMaxHp = 100;

}

void ProgressBar::Release()
{
}

void ProgressBar::Update()
{
	this->_mainRect = Figure::RectMake(_position.x, _position.y, _progressBarBackIMG->GetWidth(), _progressBarBackIMG->GetHeight());
	this->UpdateMainRect();
}

void ProgressBar::Render()
{

	_progressBarBackIMG->FrameRender(_mainRect.left, 0, 1, 1, Pivot::LEFT_TOP, false);

	_progressBarFrontIMG->FrameRender(_mainRect.left, 0, _imgFrameX, _imgFrameY, Pivot::LEFT_TOP, false);
}

void ProgressBar::SetGauge()
{
	//this->wi


}



