#include "stdafx.h"
#include "BossEffect.h"
#include "Animation.h"


BossEffect::BossEffect()
{
	//���� ��ũ�� �̹���
	_bossScrollIMG = _ImageManager->FindImage("bossScrollEffect");
	
	//���� ��ũ�� �ִϸ��̼� new ����
	_bossScrollAnimation = new Animation;

	//���� ������ x,y�� �� ������ x,y
	_bossScrollAnimation->SetStartEndFrame(0, 0, _bossScrollIMG->GetMaxFrameX() - 1, 0, false);

	//���� ����
	_bossScrollAnimation->SetIsLoop(false);

	//������ ���� �ð�
	_bossScrollAnimation->SetFrameUpdateTime(0.15f);
	//������ ����
	_bossScrollAnimation->Play();

	//���� �� ���� �ʱ�ȭ
	_alpha = 1.0f;
}


BossEffect::~BossEffect()
{
}

void BossEffect::Init()
{
}

void BossEffect::Release()
{
}

void BossEffect::Update()
{

	//�ִϸ��̼� ������Ʈ ������
	_bossScrollAnimation->UpdateFrame();
}

void BossEffect::Render()
{
	//������
	_bossScrollIMG->SetSize(_bossScrollIMG->GetFrameSize(0));
	//������ ����
	//_bossScrollIMG->FrameRender(929, 929, _bossScrollAnimation->GetNowFrameX(), 0, Pivot::CENTER, false);
	_bossScrollIMG->FrameRender(WinSizeX/2, WinSizeY/2 + 130, _bossScrollAnimation->GetNowFrameX(), 0, Pivot::CENTER, false);
	
	//��ũ�� �ִϸ��̼��� 16 �������̸� ���� �� ����
	if (_bossScrollAnimation->GetNowFrameX() == 16) 
	{
		//���� �� -0.01�� ���߱�
		_alpha -= 0.01f;

		//0���� �������� 0���� ��� �ʱ�ȭ
		if (_alpha <= 0.f) 
		{
			_alpha = 0;
		}
	}
	//���� �� ����
	_bossScrollIMG->SetAlpha(_alpha);

	//������ ����
	_bossScrollIMG->SetScale(1.5f);
}
