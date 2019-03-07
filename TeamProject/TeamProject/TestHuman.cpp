#include "stdafx.h"
#include "TestHuman.h"


TestHuman::TestHuman(Vector2 pos)
{
	_name = "TestHuman";
	_position = pos;
	_size = Vector2(100, 100);
	this->UpdateMainRect();
	_isMove = false;
	_hp = 5;


	this->AddCallbackMessage("Attack", [this](TagMessage message) { this->Damage(message.intData); });
	//���ٽ����� �����Լ�(����) ���� �����ͼ� message�� ����ϴ�
	//�������� �Լ� message���� intData�� ȣ��

	//this -> AddCallbackMessage("Attack", [this](TagMessage message) { this->Damage(message.intData); });
	
}

TestHuman::~TestHuman()
{
}

void TestHuman::Update()
{
	GameObject::Update();

	if (_isMove)
	{
		_position.x += 300.f * _TimeManager->DeltaTime();
		this->UpdateMainRect();
	}
}

void TestHuman::Render()
{
	_DXRenderer->DrawRectangle(_mainRect, D2D1::ColorF::GreenYellow, 1.f, true);
}
