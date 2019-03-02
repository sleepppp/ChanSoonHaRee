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


		//### �κ��丮�� ��� �ö󰡴� �� �����ϱ� ���� ###
		//���� ������ y�� ȭ�� �߾��̰ų� �� ������  
		if (_position.y <= WinSizeY / 2)
		{
			//������ y�� ȭ�� �߾ӿ� ������Ű��
			_position.y = WinSizeY / 2;
			//�κ��丮 ���� �����ϱ�
			_state = InventoryState::Idle;
		}
		this->UpdateMainRect();

		//�÷��̾� �κ��丮 ���� ��ġ ���
		for (UINT i = 0; i < 5; ++i)
		{
			_playerSlotList[i]->slotRect = Figure::RectMake(_mainRect.left + 95 + (57 + 10) * i, _mainRect.top + 58, 57, 57);
		}
		break;
	//�κ��丮 �ݱ�
	case Inventory::InventoryState::CloseSlide:
		//�κ��丮 ������ y �Ʒ��� 800.0f ��ŭ �̵��ϱ�
		_position.y += 800.0f * _TimeManager->DeltaTime();
		
		//### �κ��丮�� ��� �������� �� �����ϱ� ���� ###
		//���� ������ y�� ȭ�� �߾��̰ų� �� ������  
		if (_position.y <= WinSizeY / 2)
		{
			//������ y�� ȭ�� �߾ӿ� ������Ű��
			_position.y = WinSizeY / 2;
			//��Ƽ�� false ó�� (�� ���̰�)
			this->SetActive(false);
		}
		this->UpdateMainRect();

		//�÷��̾� �κ��丮 ���� ��ġ ���
		for (UINT i = 0; i < 5; ++i)
		{
			_playerSlotList[i]->slotRect = Figure::RectMake(_mainRect.left + 95 + (57 + 10) * i, _mainRect.top + 58, 57, 57);
		}
		break;
	//�κ��丮 ���� ����
	case Inventory::InventoryState::Idle:
		//���� f1 ������ �κ��丮 �ݱ�
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
	//���� �κ��丮 �̹����� ���� ���� ������ (=���� ������) �����ϱ�
	if (_inventoryImage != nullptr)
		_inventoryImage->Render(_mainRect.left, _mainRect.top, Pivot::LEFT_TOP, false);

	_DXRenderer->DrawRectangle(_mainRect, DefaultBrush::red, false);

	// 
	for (UINT i = 0; i < _playerSlotList.size(); ++i)
	{
		_DXRenderer->DrawRectangle(_playerSlotList[i]->slotRect, DefaultBrush::red, false);

		//���Կ� �������� ���Դٸ�
		if(_playerSlotList[i]->data.image)
		{
			//������ �̹��� ũ�⸦ ���� ��Ʈ�� ���缭 ���� ��Ʈ�� ���
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
