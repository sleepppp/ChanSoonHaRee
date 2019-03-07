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
	//HP�� �̹��� �����ӷ���
	_progressBarBackIMG = _ImageManager->AddFrameImage("hpBar1", L"../Resouces/UI/hpBar", 1, 6, false);
	_progressBarFrontIMG = _ImageManager->AddFrameImage("hpBar2", L"../Resouces/UI/hpBar", 1, 6, false);

	//Ŭ���� Ű �̸� ����
	this->_name = "ProgressBar";

	//������ �ʱ�ȭ
	this->_position = Vector2(0, 0);
	//��Ʈ ����
	this->_mainRect = Figure::RectMake(_position.x, _position.y, _progressBarBackIMG->GetWidth(), _progressBarBackIMG->GetHeight());
	
	//�̹��� ������ �ʱ�ȭ 
	_imgFrameX = 0;
	_imgFrameY = 0;

	//�׽�Ʈ�� ���� �ʱ�ȭ
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



