#include "stdafx.h"
#include "BossProgressBar.h"
#include "Boss.h"


BossProgressBar::BossProgressBar()
{
	//���� ���α׷��� �� �̹���
	_bossProgressBarImg = _ImageManager->FindImage("bossHpBar");

	//Ŭ���� Ű �̸� ����
	this->_name = "bossProgressBar";

	//������ �ʱ�ȭ
	this->_position = Vector2(100, 600);
	//��Ʈ ����
	this->_mainRect = Figure::RectMake(_position.x, _position.y, _bossProgressBarImg->GetWidth(), _bossProgressBarImg->GetHeight());

	//�̹��� ������ �ʱ�ȭ 
	_imgFrameX = 0;
	_imgFrameY = 1;

	//���̺� hp �� currentHp;
	Boss* _boss = (Boss*)_ObjectManager->FindObject(ObjectType::Object, "Boss");
	_saveHp = _boss->GetBossMaxHp();

	//����Ʈ ����
	_bossProgressState = BossProgressState::DefaultState;

	SetGauge(_boss->GetBossCurrentHp(), _boss->GetBossMaxHp());
	this->_hpWidth = ((float)_saveHp / (float)_boss->GetBossMaxHp()) * (float)_bossProgressBarImg->GetWidth();
}


BossProgressBar::~BossProgressBar()
{
}

void BossProgressBar::Init()
{

}

void BossProgressBar::Release()
{

}

void BossProgressBar::Update()
{
	//���� ��Ʈ ����
	this->_mainRect = Figure::RectMake(_position.x, _position.y, _bossProgressBarImg->GetWidth(), _bossProgressBarImg->GetHeight());

	//�÷��̾� Ŭ���� �����ؼ� �÷��̾� �Լ� ��������
	Boss* _boss = (Boss*)_ObjectManager->FindObject(ObjectType::Object, "Boss");


	//��ȭ�� HP�� ���� ���
	SetGauge(_boss->GetBossCurrentHp(), _boss->GetBossMaxHp());

	//���α׷��� �� ���� �Լ�
	BossProgressBarState();

	//������Ʈ ��Ʈ
	this->UpdateMainRect();
}

void BossProgressBar::Render()
{
	//���� ���α׷��� �� �̹��� ũ��
	_bossProgressBarImg->SetSize(Vector2(_hpWidth * 1.6f, 45.f));
	//���� ���α׷����� �� ������ ����
	_bossProgressBarImg->FrameRender(_mainRect.left, _mainRect.top, _imgFrameX, _imgFrameY, Pivot::LEFT_TOP, false);
}

bool BossProgressBar::SetGauge(int currentHp, int maxHp)
{
	//�÷��̾� Ŭ���� �����ؼ� �÷��̾� �Լ� ��������
	Boss* _boss = (Boss*)_ObjectManager->FindObject(ObjectType::Object, "Boss");

	//���� saveHp�� currentHp�� �ٸ���
	//FLOAT_EQUAL�� 
	if (FLOAT_EQUAL(_saveHp, _boss->GetBossCurrentHp()) == false)
	{
		//saveHp�� ��´�.
		_saveHp -= 60.0f * _TimeManager->DeltaTime();
		_bossProgressState = BossProgressState::DamageState;

		if (_saveHp <= _boss->GetBossCurrentHp())
		{
			_saveHp = _boss->GetBossCurrentHp();
			_bossProgressState = BossProgressState::DamageEndState;
		}

		//ü�� �� ���� : ü�� �� ���� * ���α׷��� �� �̹��� ���̸�ŭ
		this->_hpWidth = ((float)_saveHp / (float)maxHp) * (float)_bossProgressBarImg->GetWidth();

		//ü�� �ٰ� 0���� ���ų� �������� 0���� �ʱ�ȭ
		if (_hpWidth <= 0)
		{
			_hpWidth = 0;
		}
		return true;
	}
	return false;
}

void BossProgressBar::BossProgressBarState()
{
	switch (_bossProgressState)
	{
		//���� ���� - ���α׷��� ��
	case BossProgressBar::BossProgressState::DamageState:
		_imgFrameY = 1;
		break;
		//���� ���� ���� - ���α׷��� ��
	case BossProgressBar::BossProgressState::DamageEndState:
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
				//������ Y�� 0�� �ʱ�ȭ
				_imgFrameY = 0;
				_bossProgressState = BossProgressState::DefaultState;
			}
		}
		break;
		//����Ʈ ���� - ���α׷��� ��
	case BossProgressBar::BossProgressState::DefaultState:
		_imgFrameY = 0;
		break;
	case BossProgressBar::BossProgressState::End:

		break;
	default:
		break;
	}
}
