#include "stdafx.h"
#include "UIWeaponAndBag.h"


UIWeaponAndBag::UIWeaponAndBag()
{
}


UIWeaponAndBag::~UIWeaponAndBag()
{
}

void UIWeaponAndBag::Init()
{
	//상시 UI 무기 스왑
	this->_uIWeaponSwapIMG = _ImageManager->AddFrameImage("UI_WeaponSwap", L"../Resources/UI/UI_WeaponSwap.png", 4, 1, false);

	//상시 UI 가방
	this->_uIBagIMG = _ImageManager->AddImage("UI_Bag", L"../Resources/UI/UI_Bag.png", false);

	//클래스 이름
	this->_name = "UIWeaponAndBag";
	this->_mainRect = Figure::RectMake(1057, 160, 40, 40);
	
	this->_FrameX = 0;
	this->_FrameY = 0;

	
}

void UIWeaponAndBag::Release()
{

}

void UIWeaponAndBag::Update()
{
	if (_Input->GetKeyDown(VK_F4))
	{
		GameObject* object = _ObjectManager->FindObject(ObjectType::UI, "Inventory");
		if (object)
		{
			if (object->GetActive() == false)
			{
				object->SetActive(true);
			}
		}
	}
	
}

void UIWeaponAndBag::Render()
{
	//UI 무기 스왑 프레임 이미지 렌더
	if (_uIWeaponSwapIMG != nullptr) 
	{
		//SetSize에 uiWeaponSwapIMG의 프레임을 담는다.
		_uIWeaponSwapIMG->SetSize(_uIWeaponSwapIMG->GetFrameSize(0));
		_uIWeaponSwapIMG->FrameRender(922, 19, _FrameX, _FrameY, Pivot::LEFT_TOP, false);
	}

	//UI 가방 이미지 렌더
	if (_uIBagIMG != nullptr)
	{
		_uIBagIMG->Render(1018, 140, Pivot::LEFT_TOP, false);
	}

	if (_isDebug)
	{
		_DXRenderer->DrawRectangle(_mainRect, DefaultBrush::white, false, 2.0f);
	}
}
