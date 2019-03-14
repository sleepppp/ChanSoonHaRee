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
	_progressBarBackIMG = _ImageManager->FindImage("hpBar1");
	_progressBarFrontIMG = _ImageManager->FindImage("hpBar2");

	//��Ʈ �̹��� ����
	_heartIMG = _ImageManager->AddImage("heart", L"../Resources/UI/heart.png", false);

	//Ŭ���� Ű �̸� ����
	this->_name = "ProgressBar";

	//������ �ʱ�ȭ
	this->_position = Vector2(140, 15);
	//��Ʈ ����
	this->_mainRect = Figure::RectMake(_position.x, _position.y, _progressBarBackIMG->GetWidth(), _progressBarBackIMG->GetHeight());

	//�̹��� ������ �ʱ�ȭ 
	_imgFrameX = 0;
	_imgFrameY = 1;

	//���̺� hp �� currentHp;
	Player* _player = (Player*)_ObjectManager->FindObject(ObjectType::Object, "Will");
	_saveHp = _player->GetPlayerCurrentHp();

	//����Ʈ ����
	_barState = ProgressState::DefaultState;

	SetGauge(_player->GetPlayerCurrentHp(), _player->GetPlayerMaxHp());
	this->_hpWidth = ((float)_saveHp / (float)_player->GetPlayerMaxHp()) * (float)_progressBarFrontIMG->GetWidth();
}

void ProgressBar::Release()
{
}

void ProgressBar::Update()
{
	GameObject::Update();

	//���� ��Ʈ ����
	this->_mainRect = Figure::RectMake(_position.x, _position.y, _progressBarBackIMG->GetWidth(), _progressBarBackIMG->GetHeight());

	//�÷��̾� Ŭ���� �����ؼ� �÷��̾� �Լ� ��������
	Player* _player = (Player*)_ObjectManager->FindObject(ObjectType::Object, "Will");


	//��ȭ�� HP�� ���� ���
	SetGauge(_player->GetPlayerCurrentHp(), _player->GetPlayerMaxHp());

	//���α׷��� �� ���� �Լ�
	ProgressBarState();

	//������Ʈ ��Ʈ
	this->UpdateMainRect();
}

void ProgressBar::Render()
{
	//HP�� �׵θ� �̹���
	_progressBarBackIMG->SetSize(Vector2(_progressBarBackIMG->GetFrameSize(0).x * 1.2f, 45.f));
	_progressBarBackIMG->FrameRender(_mainRect.left, _mainRect.top, 0, 0, Pivot::LEFT_TOP, false);
	
	//HP�� HP(ü��) �̹���
	_progressBarFrontIMG->SetSize(Vector2(_hpWidth *  1.2f, 45.f));
	_progressBarFrontIMG->FrameRender(_mainRect.left, _mainRect.top, _imgFrameX, _imgFrameY, Pivot::LEFT_TOP, false);

	//��Ʈ �̹���
	_heartIMG->SetSize(Vector2(48, 48));
	_heartIMG->Render(102, 13, Pivot::LEFT_TOP, false);

}

bool ProgressBar::SetGauge(int currentHp, int maxHp)
{
	//�÷��̾� Ŭ���� �����ؼ� �÷��̾� �Լ� ��������
	Player* _player = (Player*)_ObjectManager->FindObject(ObjectType::Object, "Will");

	//���� saveHp�� currentHp�� �ٸ���
	//FLOAT_EQUAL�� 
	if (FLOAT_EQUAL(_saveHp, _player->GetPlayerCurrentHp()) == false)
	{
		//saveHp�� ��´�.
		_saveHp -= 25.0f * _TimeManager->DeltaTime();
		_barState = ProgressState::DamageState;

		if (_saveHp <= _player->GetPlayerCurrentHp())
		{
			_saveHp = _player->GetPlayerCurrentHp();
			_barState = ProgressState::DamageEndState;
		}
			
		//ü�� �� ���� : ü�� �� ���� * ���α׷��� �� �̹��� ���̸�ŭ
		this->_hpWidth = ((float)_saveHp / (float)maxHp) * (float)_progressBarFrontIMG->GetWidth();

		//ü�� �ٰ� 0���� ���ų� �������� 0���� �ʱ�ȭ
		if (_hpWidth <= 0)
		{
			_hpWidth = 0;
		}
		return true;
	}
	return false;
}

//���α׷��� �� ����
void ProgressBar::ProgressBarState()
{
	switch (_barState)
	{
	//���� ���� - ���α׷��� ��
	case ProgressBar::ProgressState::DamageState:
		_imgFrameY = 2;
		break;
	//���� ���� ���� - ���α׷��� ��
	case ProgressBar::ProgressState::DamageEndState:
		//������ ī��Ʈ�� �ð� ����
		_frameCount += 35.f * _TimeManager->DeltaTime();
		
		//������ ī��Ʈ�� 1�ʺ��� ���ų� ��������
		if (_frameCount >= 1.f)
		{
			//�̹��� y ������ ����
			_imgFrameY++;
			//������ ī��Ʈ �ʱ�ȭ
			_frameCount = 0.f;

			//������ Y�� 4���� Ŀ����
			if (_imgFrameY > 4)
			{
				//������ Y�� 1�� �ʱ�ȭ
				_imgFrameY = 1;
				_barState = ProgressState::DefaultState;
			}
		}
		break;
	//����Ʈ ���� - ���α׷��� ��
	case ProgressBar::ProgressState::DefaultState:
		_imgFrameY = 1;
		break;
	case ProgressBar::ProgressState::End:

		break;
	default:
		break;
	}
}