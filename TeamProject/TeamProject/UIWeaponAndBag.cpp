#include "stdafx.h"
#include "UIWeaponAndBag.h"
#include "Animation.h"

UIWeaponAndBag::UIWeaponAndBag()
{
	//��� UI ���� ����
	this->_uIWeaponSwapIMG = _ImageManager->FindImage("UI_WeaponSwap");

	//��� UI ����
	this->_uIBagIMG = _ImageManager->FindImage("UI_Bag");

	//Ŭ���� �̸�
	this->_name = "UIWeaponAndBag";
	this->_mainRect = Figure::RectMake(1057, 160, 40, 40);

	//�ִϸ��̼� new
	_uIswapAnimation = new Animation;

	//���� ���� �ʱ�ȭ
	_isSwap = false;

	//���� ������ x,y�� �� ������ x,y
	_uIswapAnimation->SetStartEndFrame(0, 0, _uIWeaponSwapIMG->GetMaxFrameX() - 1,0, false);
	//���� ����
	_uIswapAnimation->SetIsLoop(false);
	//������ ���� �ð�
	_uIswapAnimation->SetFrameUpdateTime(0.1f);

	//���� ī��Ʈ �ʱ�ȭ
	_swapCount = 0;
}


UIWeaponAndBag::~UIWeaponAndBag()
{
}

void UIWeaponAndBag::Init()
{	
}

void UIWeaponAndBag::Release()
{

}

void UIWeaponAndBag::Update()
{
	//�κ��丮
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

	//���� ���� ZŰ
	if (_Input->GetKeyDown('Z'))
	{
		//������ false�� ���
		//�ҵ� -> Ȱ ��ȯ
		if (_isSwap == false) 
		{
			_uIswapAnimation->Stop();
			//���� ������ x,y�� �� ������ x,y
			_uIswapAnimation->SetStartEndFrame(0, 0, _uIWeaponSwapIMG->GetMaxFrameX() -1 , 0, false);

			//�ִϸ��̼� ����
			_uIswapAnimation->Play();

			//���� ���� ����
			_isSwap = true;
		}

		//������ true�� ���
		//Ȱ -> �ҵ� ��ȯ
		else if (_isSwap == true) 
		{
			_uIswapAnimation->Stop();
			//���� ������ x,y�� �� ������ x,y
			_uIswapAnimation->SetStartEndFrame(0, 1, _uIWeaponSwapIMG->GetMaxFrameX() - 1, 1, false);

			//�ִϸ��̼� ����
			_uIswapAnimation->Play();

			//���� ���� ����
			_isSwap = false;
		}
	}
	//������ ������Ʈ
	_uIswapAnimation->UpdateFrame();

}

void UIWeaponAndBag::Render()
{
	//UI ���� ���� ������ �̹��� ����
	if (_uIWeaponSwapIMG != nullptr) 
	{
		//SetSize�� uiWeaponSwapIMG�� �������� ��´�.
		_uIWeaponSwapIMG->SetSize(_uIWeaponSwapIMG->GetFrameSize(0));


		_uIWeaponSwapIMG->FrameRender(922, 19, _uIswapAnimation->GetNowFrameX(), _uIswapAnimation->GetNowFrameY(), Pivot::LEFT_TOP, false);
	}

	//UI ���� �̹��� ����
	if (_uIBagIMG != nullptr)
	{
		_uIBagIMG->Render(1018, 140, Pivot::LEFT_TOP, false);
	}

	if (_isDebug)
	{
		_DXRenderer->DrawRectangle(_mainRect, DefaultBrush::white, false, 2.0f);
	}
}
