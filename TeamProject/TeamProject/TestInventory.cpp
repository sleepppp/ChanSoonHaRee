#include "stdafx.h"
#include "TestInventory.h"

#include "TestInventorySlot.h"
#include "TestItem.h"


TestInventory::TestInventory()
	:GameObject("TestInventory",Vector2(WinSizeX / 2,0),Vector2(),Pivot::CENTER)
{
	_state = State::OpenSlide;
	_targetIndex = 0;
}


TestInventory::~TestInventory()
{
}
/***********************************************************
## Init ##
 ***********************************************************/
void TestInventory::Init()
{
	_ImageManager->AddImage("item_potion", PathResources(L"UI/item_potion.png"));
	_ImageManager->AddImage("item_liquidItem", PathResources(L"UI/item_liquidItem.png"));

	this->_windowImage = _ImageManager->AddImage("InventoryWindow", L"../Resources/UI/inventory.png", false);
	this->_targetImage = _ImageManager->AddImage("InventoryTarget", L"../Resources/UI/invenSlot.png", false);

	this->_position = Vector2(WinSizeX / 2, WinSizeY + _windowImage->GetHeight() / 2);
	this->_size = Vector2((int)_windowImage->GetWidth(), (int)_windowImage->GetHeight());
	this->UpdateMainRect();

	for (UINT i = 0; i < 5; ++i)
	{
		TestInventorySlot* slot = new TestInventorySlot(Vector2(95 + (57 + 10) * i, 58), Vector2(57, 57));
		slot->UpdatePosition(Vector2(_mainRect.left, _mainRect.top));
		_slotList.push_back(slot);
	}

	for (UINT i = 0; i < 3; ++i)
	{
		for (UINT j = 0; j < 5; ++j)
		{
			TestInventorySlot* slot = new TestInventorySlot(Vector2((int)(95 + (57 + 10) * j),(int)(144 + (58 + 10) * i)), Vector2(57, 57));
			slot->UpdatePosition(Vector2(_mainRect.left, _mainRect.top));
			_slotList.push_back(slot);
		}
	}	


	this->MoveIndex(0);
}
/***********************************************************
## Release ##
 ***********************************************************/
void TestInventory::Release()
{
	for (UINT i = 0; i < _slotList.size(); ++i)
		SafeDelete(_slotList[i]);
	_slotList.clear();
}
/***********************************************************
## Update ##
 ***********************************************************/
void TestInventory::Update()
{
	switch (_state)
	{
	case TestInventory::State::OpenSlide:
		_position.y -= 800.0f * _TimeManager->DeltaTime();
		if (_position.y <= CastingFloat(WinSizeY / 2))
		{
			_position.y = CastingFloat(WinSizeY / 2);
			_state = State::Idle;
		}
		this->UpdateMainRect();
		this->UpdateSlotPosition();
		break;
	case TestInventory::State::CloseSlide:
		_position.y += 800.0f * _TimeManager->DeltaTime();
		this->UpdateMainRect();
		this->UpdateSlotPosition();
		if (_position.y >= CastingFloat(WinSizeY + _windowImage->GetHeight() / 2))
		{
			_position.y = CastingFloat(WinSizeY + _windowImage->GetHeight() / 2);
			_state = State::OpenSlide;
			_isActive = false;
			this->UpdateMainRect();
			this->UpdateSlotPosition();

		}
		break;
	case TestInventory::State::Idle:
		if (_Input->GetKeyDown(VK_RETURN))
			_state = State::CloseSlide;
		if (_Input->GetKeyDown('D'))
			this->MoveIndex(_targetIndex + 1);
		if (_Input->GetKeyDown('A'))
			this->MoveIndex(_targetIndex -1);
		if (_Input->GetKeyDown('W'))
			this->MoveIndex(_targetIndex - 5);
		if (_Input->GetKeyDown('S'))
			this->MoveIndex(_targetIndex + 5);
		
		break;
	default:
		break;
	};

	//�׽�Ʈ �� ������ �߰�
	if (_Input->GetKeyDown('L'))
		this->AddItem("item_potion");
	if (_Input->GetKeyDown('K'))
		this->AddItem("item_liquidItem");
}
/***********************************************************
## Render ##
 ***********************************************************/
void TestInventory::Render()
{
	_windowImage->Render(CastingInt(_mainRect.left), CastingInt(_mainRect.top), Pivot::LEFT_TOP, false);
	for (UINT i = 0; i < _slotList.size(); ++i)
		_slotList[i]->Render();

	if (_slotList[_targetIndex])
	{
		_targetImage->SetSize(_slotList[_targetIndex]->GetSize());
		_targetImage->Render(_slotList[_targetIndex]->GetRect().left, _slotList[_targetIndex]->GetRect().top, Pivot::LEFT_TOP, false);
	}

	if (_isDebug)
		_DXRenderer->DrawRectangle(_mainRect, DefaultBrush::red, false);
}
/***********************************************************
## UpdateSlotPosition ##
�κ��丮 â�� �̵����� �� �� �Լ��� ȣ���ϸ� ���Ե鵵 ���� �̵������ش�.
 ***********************************************************/
void TestInventory::UpdateSlotPosition()
{
	for (UINT i = 0; i < _slotList.size(); ++i)
		_slotList[i]->UpdatePosition(Vector2(_mainRect.left, _mainRect.top));
}

/********************************************************************************
## AddItem ##
�߰��� ������ �̸��� �޾Ƽ� ���������� �κ��丮�� �������� �߰� �Ѵ�. 
���� ��� MoveItemŬ������ �����̴ٰ� �÷��̾�� �浹�ϰ� �Ǹ� �κ��丮�� �ڽ��� �̸���
�����鼭 ������ �߰��� ��û�ѵ� �κ��丮�� ������ �־ �������� �ְ� �Ǹ� �ڽ��� �����ϸ�
�ȴ�.

@@ string name : ������ �̸�
********************************************************************************/
bool TestInventory::AddItem(string name)
{
	//�߰��� �������� �̸��� itemPotion�̶��
	if (name == "item_potion")
	{
		//�ش� �������� �ʱ�ȭ
		TestItem item;
		item.SetData(name, L"�̻��� ���� . . .���� ��������", 10, _ImageManager->FindImage(name));
		//�������� �� �� �ִ� �ڸ��� �ִ��� �˻��غ���. 
		if (TestInventorySlot* slot = FindSlot(name))
		{
			//�� �� �ִ� �ڸ��� �ִٸ� �ش� ���Կ� �������� �߰��Ѵ�.
			slot->AddItem(item);
			//�������� ���������� �Ծ��ٰ� �˷��ش�.
			return true;
		}
	}
	else if (name == "item_liquidItem")
	{
		TestItem item;
		item.SetData(name, L"�˼����� ������ ���� ���� ����", 10, _ImageManager->FindImage(name));
		if (TestInventorySlot* slot = FindSlot(name))
		{
			slot->AddItem(item);
			return true;
		}
	}


	return false;
}
/***********************************************************
## MoveIndex ##
@@ int index : �κ��丮 Ÿ�� ��ũ �̵��� �ε��� 
 ***********************************************************/
void TestInventory::MoveIndex(int index)
{
	if (index < 0)
		index = _slotList.size() - 1;
	else if (index >= _slotList.size())
		index = 0;

	this->_targetIndex = index;
}

/***********************************************************
## FindSlot ##
@@ string name : ������ �̸� 

@@ return TestInventorySlot* : ã�Ҵٸ� ã�� ���� ��ȯ �ƴ϶�� null ��ȯ
 ***********************************************************/
TestInventorySlot * TestInventory::FindSlot(string name)
{
	for (UINT i = 0; i < _slotList.size(); ++i)
	{
		if (_slotList[i]->GetItemName() == name)
			return _slotList[i];
	}

	for (UINT i = 0; i < _slotList.size(); ++i)
	{
		if (_slotList[i]->GetIsEmpty() == true)
			return _slotList[i];
	}

	return nullptr;
}
