#include "stdafx.h"
#include "ProgressBar.h"
#include "Player.h"

ProgressBar::ProgressBar()
{
}


ProgressBar::~ProgressBar()
{
}

void ProgressBar::Init()
{	
	//HP�� �̹��� �����ӷ���
	_progressBarBackIMG = _ImageManager->AddFrameImage("hpBar1", L"../Resources/UI/hpBar.png", 1, 6, false);
	_progressBarFrontIMG = _ImageManager->AddFrameImage("hpBar2", L"../Resources/UI/hpBar.png", 1, 6, false);

	//Ŭ���� Ű �̸� ����
	this->_name = "ProgressBar";

	//������ �ʱ�ȭ
	this->_position = Vector2(100, 15);
	//��Ʈ ����
	this->_mainRect = Figure::RectMake(_position.x, _position.y, _progressBarBackIMG->GetWidth(), _progressBarBackIMG->GetHeight());
	
	//�̹��� ������ �ʱ�ȭ 
	_imgFrameX = 0;
	_imgFrameY = 1;
	
	_testMaxHp = 100;
	_testCurrentHp = 100;

	//���̺� hp �� currentHp;
	//Player* _player = (Player*)_ObjectManager->FindObject(ObjectType::Object, "Will");
	//_saveHp = _player->GetPlayerMaxHp();
	_saveHp = _testMaxHp; 



	//�׽�Ʈ�� ���� �ʱ�ȭ
	//_testCurrentHp = 50;
	//_testMaxHp = 100;

	SetGauge(_testCurrentHp, _testMaxHp);
	this->_hpWidth = ((float)_saveHp / (float)_testMaxHp) * (float)_progressBarFrontIMG->GetWidth();
}

void ProgressBar::Release()
{
}

void ProgressBar::Update()
{
	//���� ��Ʈ ����
	this->_mainRect = Figure::RectMake(_position.x, _position.y, _progressBarBackIMG->GetWidth(), _progressBarBackIMG->GetHeight());

	//�÷��̾� Ŭ���� �����ؼ� �÷��̾� �Լ� ��������
	Player* _player = (Player*)_ObjectManager->FindObject(ObjectType::Object, "Will");

	//���̺� HP�� ���� HP�� ���
	//_saveHp = _player->GetPlayerCurrentHp();
	if (_Input->GetKeyDown('P'))
	{
		_testCurrentHp -= 10;
	}


	//��ȭ�� HP�� ���� ���
	//SetGauge(_player->GetPlayerCurrentHp(), _player->GetPlayerMaxHp());
	
	SetGauge(_testCurrentHp, _testMaxHp);
	
	//������Ʈ ��Ʈ
	this->UpdateMainRect();



}

void ProgressBar::Render()
{
	//HP�� �׵θ� �̹���
	_progressBarBackIMG->SetSize(Vector2(_progressBarBackIMG->GetFrameSize(0).x * 1.5f, 45.f));
	_progressBarBackIMG->FrameRender(_mainRect.left, _mainRect.top, 0, 0, Pivot::LEFT_TOP, false);
	
	//HP�� HP(ü��) �̹���
	_progressBarFrontIMG->SetSize(Vector2(_hpWidth *  1.5f, 45.f));
	_progressBarFrontIMG->FrameRender(_mainRect.left, _mainRect.top, _imgFrameX, _imgFrameY, Pivot::LEFT_TOP, false);
}

bool ProgressBar::SetGauge(int currentHp, int maxHp)
{
	if (_saveHp != _testCurrentHp)
	{
		_saveHp -= 20.0f * _TimeManager->DeltaTime();
		if (_saveHp <= _testCurrentHp)
			_saveHp = _testCurrentHp;
		this->_hpWidth = ((float)_saveHp / (float)maxHp) * (float)_progressBarFrontIMG->GetWidth();
		return true;
	}
	return false;
}



