#include "stdafx.h"
#include "UIMoneyPoket.h"


UIMoneyPoket::UIMoneyPoket()
{
}


UIMoneyPoket::~UIMoneyPoket()
{
}

void UIMoneyPoket::Init()
{
	//�� �ָӴ� �̹��� ����
	_moneyPoketIMG = _ImageManager->AddImage("moneyPoket", L"../Resources/UI/moneyBag.png", false);

}

void UIMoneyPoket::Release()
{
}

void UIMoneyPoket::Update()
{
}

void UIMoneyPoket::Render()
{
	//�� �ָӴ� �̹���
	_moneyPoketIMG->SetSize(Vector2(64, 65));
	_moneyPoketIMG->Render(19, 18, Pivot::LEFT_TOP, false);
}
