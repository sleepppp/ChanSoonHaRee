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
	//HP바 이미지 프레임렌더
	_progressBarBackIMG = _ImageManager->AddFrameImage("hpBar1", L"../Resources/UI/hpBar.png", 1, 6, false);
	_progressBarFrontIMG = _ImageManager->AddFrameImage("hpBar2", L"../Resources/UI/hpBar.png", 1, 6, false);

	//클래스 키 이름 선언
	this->_name = "ProgressBar";

	//포지션 초기화
	this->_position = Vector2(100, 15);
	//렉트 생성
	this->_mainRect = Figure::RectMake(_position.x, _position.y, _progressBarBackIMG->GetWidth(), _progressBarBackIMG->GetHeight());
	
	//이미지 프레임 초기화 
	_imgFrameX = 0;
	_imgFrameY = 1;
	
	_testMaxHp = 100;
	_testCurrentHp = 100;

	//세이브 hp 는 currentHp;
	//Player* _player = (Player*)_ObjectManager->FindObject(ObjectType::Object, "Will");
	//_saveHp = _player->GetPlayerMaxHp();
	_saveHp = _testMaxHp; 



	//테스트용 인자 초기화
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
	//메인 렉트 선언
	this->_mainRect = Figure::RectMake(_position.x, _position.y, _progressBarBackIMG->GetWidth(), _progressBarBackIMG->GetHeight());

	//플레이어 클래스 접근해서 플레이어 함수 가져오기
	Player* _player = (Player*)_ObjectManager->FindObject(ObjectType::Object, "Will");

	//세이브 HP에 현재 HP에 담기
	//_saveHp = _player->GetPlayerCurrentHp();
	if (_Input->GetKeyDown('P'))
	{
		_testCurrentHp -= 10;
	}


	//변화한 HP바 길이 얻기
	//SetGauge(_player->GetPlayerCurrentHp(), _player->GetPlayerMaxHp());
	
	SetGauge(_testCurrentHp, _testMaxHp);
	
	//업데이트 렉트
	this->UpdateMainRect();



}

void ProgressBar::Render()
{
	//HP바 테두리 이미지
	_progressBarBackIMG->SetSize(Vector2(_progressBarBackIMG->GetFrameSize(0).x * 1.5f, 45.f));
	_progressBarBackIMG->FrameRender(_mainRect.left, _mainRect.top, 0, 0, Pivot::LEFT_TOP, false);
	
	//HP바 HP(체력) 이미지
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



