#include "stdafx.h"
#include "Inventory.h"

#include "Image.h"
Inventory::Inventory()
{
}


Inventory::~Inventory()
{
}

void Inventory::Init()
{
	//�̸�
	this->_name = "Inventory";

	//�̹��� �߰�
	//LSTRING /.. �� ���� ������ �̵� /�� Ÿ�� Ÿ�� �Ѿ �� �ִ�. png ���ϵ� ��� ����
	//false�� �ȼ� �浹 �� ���� �� ���� üũ��
	this->_inventoryImage = _ImageManager->AddImage("InventoryWindow", L"../Resources/UI/inventory.png", false);

	//�κ��丮 ��ġ ���
	//X �������� ȭ�� ���� �߾�
	//Y �������� ȭ�� �� �� + �̹��� ���̸�ŭ    why? �κ��丮�� ó������ ������ �ֱ� ����.
	this->_position = Vector2(WinSizeX / 2, WinSizeY +_inventoryImage->GetHeight());

	//�κ��丮 ũ�� ���
	//X ũ��� �κ��丮 �̹��� ���� ���̸�ŭ     (int)�� ����ȯ
	//Y ũ��� �κ��丮 �̹��� ���� ���̸�ŭ     (int)�� ����ȯ
	this->_size = Vector2((int)_inventoryImage->GetWidth(), (int)_inventoryImage->GetHeight());

	//�κ��丮 ������ ����
	//�߾�(CENTER)�� ���� 
	this->_pivot = Pivot::CENTER;

	//������Ʈ ��Ʈ ó��
	this->UpdateMainRect();
	//233 185

	//�÷��̾� ���� ��Ʈ ����
	//�÷��̾� ������ 5ĭ
	for (UINT i = 0; i < 5; ++i)
	{
		//�κ��丮 ���� Ŭ���� ������ slot = �κ��丮 Ŭ���� NEW ����
		InventorySlot* slot = new InventorySlot;
		
		//���� -> ���� ��Ʈ = left top �������� ��Ʈ ����. 
		//X���� ��ǥ�� ���� ��Ʈ.left + 95 + (57 + 10) * i ��ŭ �������� 5�� ����, �� 5���� ��Ʈ ����
		//Y���� ��ǥ�� ���� ��Ʈ.top + 58
		//X,Y ũ��� 57, 57
		slot->slotRect = Figure::RectMake(_mainRect.left +  95 + (57 + 10) * i, _mainRect.top + 58, 57, 57);

		//���� �������� ���� �ʾ����Ƿ� ���� isEmpty�� true
		slot->isEmpty = true;
		
		//��Ʈ�� 5�� �����ǰ� �÷��̾� �κ��丮 ���Ե� 5�� ���� �ʿ��ϱ� ������
		//push_back�� new ������ slot�� ��´�.
		_playerSlotList.push_back(slot);
	}

	//�κ��丮 ���� �ʱ�ȭ
	_state = InventoryState::OpenSlide;
}

//�κ��丮 Release
void Inventory::Release()
{
	//�÷��̾� ���� ������ ��ŭ(size) SafeDelete���ֱ�
	for (UINT i = 0; i < _playerSlotList.size(); ++i)
	{
		SafeDelete(_playerSlotList[i]);
	}
}


//�κ��丮 Update
void Inventory::Update()
{	
	//����ġ�� _state : �κ��丮 ���� ó��
	switch (_state)
	{
	//�κ��丮 ����
	case Inventory::InventoryState::OpenSlide:
		//�κ��丮 ������ y ���� 800.0f ��ŭ �̵��ϱ�
		_position.y -= 800.0f * _TimeManager->DeltaTime();

		//���� 
		if (_position.y <= WinSizeY / 2)
		{
			_position.y = WinSizeY / 2;
			_state = InventoryState::Idle;
		}
		this->UpdateMainRect();
		for (UINT i = 0; i < 5; ++i)
		{
			_playerSlotList[i]->slotRect = Figure::RectMake(_mainRect.left + 95 + (57 + 10) * i, _mainRect.top + 58, 57, 57);
		}
		break;
	case Inventory::InventoryState::CloseSlide:
		_position.y += 800.0f * _TimeManager->DeltaTime();
		if (_position.y <= WinSizeY / 2)
		{
			_position.y = WinSizeY / 2;
			this->SetActive(false);
		}
		this->UpdateMainRect();
		for (UINT i = 0; i < 5; ++i)
		{
			_playerSlotList[i]->slotRect = Figure::RectMake(_mainRect.left + 95 + (57 + 10) * i, _mainRect.top + 58, 57, 57);
		}
		break;
	case Inventory::InventoryState::Idle:
		if (_Input->GetKeyDown(VK_F1))
		{
			_state = InventoryState::CloseSlide;
		}

		break;
	default:
		break;
	}
}

void Inventory::Render()
{

	if (_inventoryImage != nullptr)
		_inventoryImage->Render(_mainRect.left, _mainRect.top, Pivot::LEFT_TOP, false);

	_DXRenderer->DrawRectangle(_mainRect, DefaultBrush::red, false);

	for (UINT i = 0; i < _playerSlotList.size(); ++i)
	{
		_DXRenderer->DrawRectangle(_playerSlotList[i]->slotRect, DefaultBrush::red, false);

		if(_playerSlotList[i]->data.image)
		{
			Vector2 size = Vector2(_playerSlotList[i]->slotRect.right - _playerSlotList[i]->slotRect.left,
				_playerSlotList[i]->slotRect.bottom - _playerSlotList[i]->slotRect.top);
			_playerSlotList[i]->data.image->SetSize(size);
			_playerSlotList[i]->data.image->Render(_playerSlotList[i]->slotRect.left,
				_playerSlotList[i]->slotRect.top, Pivot::LEFT_TOP, false);
		}
	}
}

bool Inventory::AddItem(string name)
{
	if (name == "brench")
	{
		for (UINT i = 0; i < _playerSlotList.size(); ++i)
		{
			if (_playerSlotList[i]->isEmpty == true)
			{
				_playerSlotList[i]->data.image = _ImageManager->FindImage("InventoryWindow");
				_playerSlotList[i]->data.itemDescription = "�� �������� ����������~";
				_playerSlotList[i]->data.itemIndex = i;
				_playerSlotList[i]->data.itemAtk = 0;
				_playerSlotList[i]->data.itemDef = 0;
				_playerSlotList[i]->isEmpty = false;
				return true;
			}
		
		}
	}
	else if (name == "asdas")
	{

	}

	return false;
}

void Inventory::Enable()
{
	this->_state = InventoryState::OpenSlide;
}
