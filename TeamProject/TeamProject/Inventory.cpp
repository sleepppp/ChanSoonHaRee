#include "stdafx.h"
#include "Inventory.h"
#include "StringHelper.h"
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
	this->_inventoryImage = _ImageManager->AddImage("InventoryWindow", L"../Resources/UI/newInventory.png", false);

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

	//�ߺ��Ǵ� ������ ���� üũ��
	this->_itemCount = 0;

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

		//�÷��̾� ���� ������ ����
		//X,Y ũ��� 57, 57
		slot->size = Vector2(57, 57);

		//�÷��̾� ���� ��Ʈ ����
		slot->slotRect = Figure::RectMake(_mainRect.left +  95 + (57 + 10) * i, _mainRect.top + 58, slot->size.x, slot->size.y);

		//�÷��̾� ���� ������ ī��Ʈ �ʱ�ȭ
		slot->itemCount = 0;

		//���� �������� ���� �ʾ����Ƿ� ���� isEmpty�� true
		slot->isEmpty = true;
		
		//��Ʈ�� 5�� �����ǰ� �÷��̾� �κ��丮 ���Ե� 5�� ���� �ʿ��ϱ� ������
		//push_back�� new ������ slot�� ��´�.
		_playerSlotList.push_back(slot);
	}

	//���� ���� ��Ʈ ����
	//���� ������ 15ĭ
	for (UINT i = 0; i < 3; ++i) 
	{
		for (UINT j = 0; j < 5; ++j) 
		{
			//�κ��丮 ���� new ����
			InventorySlot* bagSlot = new InventorySlot;

			//���� ���� ������ ����
			bagSlot->size = Vector2(57, 57);

			//���� ���� ��Ʈ 15ĭ ����
			bagSlot->slotRect = Figure::RectMake(_mainRect.left + 95 + (57 + 10) * j, _mainRect.top + 144 + (58 + 10) * i, bagSlot->size.x, bagSlot->size.y);

			//���� ������ ó���� ������Ƿ� isEmpty�� true
			bagSlot->isEmpty = true;

			//���� ���� ������ ī��Ʈ �ʱ�ȭ
			bagSlot->itemCount = 0;

			//������ ������ ���� ���� ����Ʈ�� push_back���
			_bagSlotList.push_back(bagSlot);
		}
	}

	//���� ���� ��Ʈ ����
	//���� ������ 2ĭ
	for (UINT i = 0; i < 2; ++i) 
	{
		//�κ��丮 ���� new ����
		InventorySlot* weaponSlot = new InventorySlot;

		//���� ���� ������ ����
		weaponSlot->size = Vector2(57, 57);

		//���� ���� ��Ʈ 2ĭ ����
		weaponSlot->slotRect = Figure::RectMake(_mainRect.left + 680 + (57 + 50)* i, _mainRect.top + 50, weaponSlot->size.x, weaponSlot->size.y);

		//���� ������ ó���� ������Ƿ� isEmpty�� true
		weaponSlot->isEmpty = true;

		//������ ���� ������ ���� ���� ����Ʈ�� push_back���
		_weponSlotList.push_back(weaponSlot);
	}

	//���(��) ���� ��Ʈ ����
	//��� ������ 3ĭ
	for (UINT i = 0; i < 3; ++i) 
	{
		//�κ��丮 ���� new ����
		InventorySlot* equipSlot = new InventorySlot;

		//��� ���� ������ ����
		equipSlot->size = Vector2(57, 57);

		//��� ���� ��Ʈ ���η� 3ĭ ����
		equipSlot->slotRect = Figure::RectMake(_mainRect.left + 600 + 57, _mainRect.top + 144 + (58 + 10) * i, equipSlot->size.x, equipSlot->size.y);

		//��� ������ ó���� ������Ƿ� isEmpty�� true
		equipSlot->isEmpty = true;

		//������ ��� ������ ��� ���� ����Ʈ�� push_back���
		_equipSlotList.push_back(equipSlot);
	}

	//���� ���� ��Ʈ ����
	//���� ������ 1ĭ
	//�κ��丮 ���� new����
	InventorySlot* potionSlot = new InventorySlot;

	potionSlot->size = Vector2(57, 57);

	//���� ���� ��Ʈ 1ĭ ����
	potionSlot->slotRect = Figure::RectMake(_mainRect.left + 667 + 57, _mainRect.top + 200 + 58, potionSlot->size.x, potionSlot->size.y);
	//���� ������ ó���� ������Ƿ� isEmpty�� true
	potionSlot->isEmpty = true;
	//������ ���� ������ ���� ���� ����Ʈ�� push_back���
	_potionSlotList.push_back(potionSlot);

	//�κ��丮 Ÿ�� �̹��� �߰�
	this->_invenTargetImg = _ImageManager->AddImage("InventoryTarget", L"../Resources/UI/invenSlot.png", false);

	//�κ� Ÿ�� �������� �׻� ������ �÷��̾� ���� ù��° ĭ���� ����
	_invenTargetPosition = _playerSlotList[0]->slotRect.left, _playerSlotList[0]->slotRect.top;

	//�κ��丮 �ε���
	_invenIndex = 0;

	//�κ� ���� ���� �������� bool
	_isInvenSlot = false;

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

	//���� ���� ������ ��ŭ(size) SafeDelete ���ֱ�
	for (UINT i = 0; i < _bagSlotList.size(); ++i) 
	{
		SafeDelete(_bagSlotList[i]);
	}
}


//�κ��丮 Update
void Inventory::Update()
{	
	//�κ��丮 ���� �Լ� ���
	InvenState();
	
	//Ÿ�� �Լ� ���
	InvenTarget();

}

void Inventory::Render()
{
	//���� �κ��丮 �̹����� ���� ���� ������ (=���� ������) �����ϱ�
	if (_inventoryImage != nullptr)
		_inventoryImage->Render(_mainRect.left, _mainRect.top, Pivot::LEFT_TOP, false);

	//���� �κ��丮 Ÿ�� �̹��� ���� ���� ������(=���� ������) �����ϱ�
	if (_invenTargetImg != nullptr) 
	{
		//ĳ���� ���� �κ��丮 ����, PlayerTarget
		if (_targetState == InvenTargetState::PlayerTarget) 
		{
			_invenTargetImg->SetSize(_playerSlotList[_invenIndex]->GetSize());
			_invenTargetImg->Render(_playerSlotList[_invenIndex]->slotRect.left, _playerSlotList[_invenIndex]->slotRect.top, Pivot::LEFT_TOP, false);
		}
		
		//���� ���� �κ��丮 ����, BagTarget
		if (_targetState == InvenTargetState::BagTarget)
		{
			_invenTargetImg->SetSize(_bagSlotList[_invenIndex]->GetSize());
			_invenTargetImg->Render(_bagSlotList[_invenIndex]->slotRect.left, _bagSlotList[_invenIndex]->slotRect.top, Pivot::LEFT_TOP, false);
		}

		//���� ���� �κ��丮 ����, WeaponTarget
		if (_targetState == InvenTargetState::WeaponTarget) 
		{
			_invenTargetImg->SetSize(_weponSlotList[_invenIndex]->GetSize());
			_invenTargetImg->Render(_weponSlotList[_invenIndex]->slotRect.left, _weponSlotList[_invenIndex]->slotRect.top, Pivot::LEFT_TOP, false);
		}

		//���(��) ���� �κ��丮 ����, EquipTarget
		if (_targetState == InvenTargetState::EquipTarget) 
		{
			_invenTargetImg->SetSize(_equipSlotList[_invenIndex]->GetSize());
			_invenTargetImg->Render(_equipSlotList[_invenIndex]->slotRect.left, _equipSlotList[_invenIndex]->slotRect.top, Pivot::LEFT_TOP, false);
		}

		//���� ���� �κ��丮 ����
		if (_targetState == InvenTargetState::PotionTarget) 
		{
			_invenTargetImg->SetSize(_playerSlotList[_invenIndex]->GetSize());
			_invenTargetImg->Render(_potionSlotList[_invenIndex]->slotRect.left, _potionSlotList[_invenIndex]->slotRect.top, Pivot::LEFT_TOP, false);
		}
	}
	//��Ʈ ��� F1
	if (_isDebug)
	{
		_DXRenderer->DrawRectangle(_mainRect, DefaultBrush::red, false);
	}

	//�÷��̾� ���� �����ŭ 
	for (UINT i = 0; i < _playerSlotList.size(); ++i)
	{
		//��Ʈ ��� F1
		if (_isDebug)
			_DXRenderer->DrawRectangle(_playerSlotList[i]->slotRect, DefaultBrush::red, false);

		//���Կ� �������� ���Դٸ�
		if(_playerSlotList[i]->data.image)
		{
			//������ �̹��� ũ�⸦ ���� ��Ʈ�� ���缭 ���� ��Ʈ�� ���
			Vector2 size = Vector2(_playerSlotList[i]->slotRect.right - _playerSlotList[i]->slotRect.left,
				_playerSlotList[i]->slotRect.bottom - _playerSlotList[i]->slotRect.top);

			_playerSlotList[i]->data.image->SetSize(size);

			_playerSlotList[i]->data.image->Render(_playerSlotList[i]->slotRect.left, _playerSlotList[i]->slotRect.top, Pivot::LEFT_TOP, false);
		}

		//�÷��̾� ���� ����Ʈ ������ ī��Ʈ�� 1���� ũ��
		if (_playerSlotList[i]->itemCount > 1) 
		{
			//�ؽ�Ʈ ����
			_DXRenderer->RenderText(_playerSlotList[i]->slotRect.right - _playerSlotList[i]->size.x / 2.8f,
				_playerSlotList[i]->slotRect.bottom - _playerSlotList[i]->size.y / 3.0f,
				StringHelper::StringToWString(to_string(_playerSlotList[i]->itemCount)),RGB(13,13,13),1.0f,18);
		}
		
	}

	//���� ���� �����ŭ
	for (UINT i = 0; i < _bagSlotList.size(); ++i) 
	{
		//��Ʈ ��� F1
		if (_isDebug)
			_DXRenderer->DrawRectangle(_bagSlotList[i]->slotRect, DefaultBrush::blue, false);

		//���� ���� �׸���
		if (_bagSlotList[i]->data.image) 
		{
			//���� �����ʿ��� ���� ����, ���� �ؿ��� �� ���� �ؼ� ���� ��Ʈ ������ ���ϱ�
			Vector2 size = Vector2(_bagSlotList[i]->slotRect.right - _bagSlotList[i]->slotRect.left,
				_bagSlotList[i]->slotRect.bottom - _bagSlotList[i]->slotRect.top);

			//���� ����� data.image�� SetSize�� ����ֱ�
			_bagSlotList[i]->data.image->SetSize(size);

			//���� sizeũ�⿡ ���� data.image �������ֱ�
			_bagSlotList[i]->data.image->Render(_bagSlotList[i]->slotRect.left, _bagSlotList[i]->slotRect.top, Pivot::LEFT_TOP, false);
		}

		//���� ���� ����Ʈ ������ ī��Ʈ�� 1���� ũ��
		if (_bagSlotList[i]->itemCount > 1)
		{
			//�ؽ�Ʈ ����
			_DXRenderer->RenderText(_bagSlotList[i]->slotRect.right - _bagSlotList[i]->size.x / 2.8f,
				_bagSlotList[i]->slotRect.bottom - _bagSlotList[i]->size.y / 3.0f,
				StringHelper::StringToWString(to_string(_bagSlotList[i]->itemCount)), RGB(13, 13, 13), 1.0f, 18);
		}
	}

	//���� ���� �����ŭ
	for (UINT i = 0; i < _weponSlotList.size(); ++i) 
	{
		//��Ʈ ��� F1
		if (_isDebug) 
		{
			_DXRenderer->DrawRectangle(_weponSlotList[i]->slotRect, DefaultBrush::green, false);
		}

		//���� ���� �׸���
		if (_weponSlotList[i]->data.image) 
		{
			//���� ��Ʈ ������ ���ϱ�
			Vector2 size = Vector2(_weponSlotList[i]->slotRect.right - _weponSlotList[i]->slotRect.left,
				_weponSlotList[i]->slotRect.bottom - _weponSlotList[i]->slotRect.top);

			//���� ����� data.image�� SetSize�� ����ֱ�
			_weponSlotList[i]->data.image->SetSize(size);

			//���� size ũ�⿡ ���� data.image �������ֱ�
			_weponSlotList[i]->data.image->Render(_weponSlotList[i]->slotRect.left, _weponSlotList[i]->slotRect.top, Pivot::LEFT_TOP, false);
		}
	}

	//��� ���� �����ŭ
	for (UINT i = 0; i < _equipSlotList.size(); ++i) 
	{
		//��Ʈ ��� F1
		if (_isDebug) 
		{
			_DXRenderer->DrawRectangle(_equipSlotList[i]->slotRect, DefaultBrush::yello, false);
		}

		//��� ���� �׸���
		if (_equipSlotList[i]->data.image) 
		{
			//���� ��Ʈ ������ ���ϱ�
			Vector2 size = Vector2(_equipSlotList[i]->slotRect.right - _equipSlotList[i]->slotRect.left,
				_equipSlotList[i]->slotRect.bottom - _equipSlotList[i]->slotRect.top);

			//���� ����� data.image�� SetSize�� ���
			_equipSlotList[i]->data.image->SetSize(size);

			//���� size ũ�⿡ ���� data.image �������ֱ�
			_equipSlotList[i]->data.image->Render(_equipSlotList[i]->slotRect.left, _equipSlotList[i]->slotRect.top, Pivot::LEFT_TOP, false);
		}
	}

	//���� ���� �����ŭ
	for (UINT i = 0; i < _potionSlotList.size(); ++i)
	{
		//��Ʈ ��� F1
		if (_isDebug)
		{
			_DXRenderer->DrawRectangle(_potionSlotList[i]->slotRect, DefaultBrush::gray, false);
		}

		//��� ���� �׸���
		if (_potionSlotList[i]->data.image)
		{
			//���� ��Ʈ ������ ���ϱ�
			Vector2 size = Vector2(_potionSlotList[i]->slotRect.right - _potionSlotList[i]->slotRect.left,
				_potionSlotList[i]->slotRect.bottom - _potionSlotList[i]->slotRect.top);

			//���� ����� data.image�� SetSize�� ���
			_potionSlotList[i]->data.image->SetSize(size);

			//���� size ũ�⿡ ���� data.image �������ֱ�
			_potionSlotList[i]->data.image->Render(_potionSlotList[i]->slotRect.left, _potionSlotList[i]->slotRect.top, Pivot::LEFT_TOP, false);
		}
	}


	/*********************************
		  �÷��̾� ���� ���� ��������
	**********************************/
	//GameObject* _player = _ObjectManager->FindObject(ObjectType::Object, "Will");
}



//������ ������ ���� �߰� 
bool Inventory::AddItem(string name)
{
	//���� ������ �̸��� brench�̸�
	if (name == "brench")
	{
		//�÷��̾� ���� �����ŭ
		for (UINT i = 0; i < _playerSlotList.size(); ++i)
		{
			//�÷��̾� ���� �ش� ĭ�� ���������
			if (_playerSlotList[i]->isEmpty == true)
			{
				//�÷��̾� ���� ������ ī��Ʈ ����
				_playerSlotList[i]->itemCount++;

				//���� ������ ī��Ʈ�� 0���� ũ�ٸ�
				if (_playerSlotList[i]->itemCount > 0)
				{
					//�ش� ������ �̹��� ã��
					_playerSlotList[i]->data.image = _ImageManager->FindImage("item_brench");
					_playerSlotList[i]->data.itemDescription = "�������� ���� ���̴� ��������";
					_playerSlotList[i]->data.itemIndex = i;
					_playerSlotList[i]->data.itemAtk = 0;
					_playerSlotList[i]->data.itemDef = 0;

					if (_playerSlotList[i]->itemCount >= 10)
					{
						_playerSlotList[i]->isEmpty = false;
					}
				}	
				return true;
			}
		}

		for (UINT i = 0; i < _bagSlotList.size(); ++i) 
		{
			//���� ����
			if (_bagSlotList[i]->isEmpty == true)
			{
				//���� ���� ������ ī��Ʈ ����
				_bagSlotList[i]->itemCount++;

				if (_bagSlotList[i]->itemCount > 0) 
				{
					_bagSlotList[i]->data.image = _ImageManager->FindImage("item_brench");
					_bagSlotList[i]->data.itemDescription = "�������� ���� ���̴� ��������";
					_bagSlotList[i]->data.itemIndex = i;
					_bagSlotList[i]->data.itemAtk = 0;
					_bagSlotList[i]->data.itemDef = 0;

					if (_bagSlotList[i]->itemCount >= 10) 
					{
						_bagSlotList[i]->isEmpty = false;
					}
				}
				return true;
			}
		}
	}
	else if (name == "asdas")
	{

	}

	return false;
}

//�κ��丮 ���� ó���� ���� switch��
void Inventory::InvenState()
{
	//����ġ�� _state : �κ��丮 ���� ó��
	switch (_state)
	{
		//�κ��丮 ����
	case Inventory::InventoryState::OpenSlide:
		//�κ��丮 ������ y ���� 800.0f ��ŭ �̵��ϱ�
		_position.y -= 1600.0f * _TimeManager->DeltaTime();


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

		//���� �κ��丮 ���� ��ġ ���
		for (UINT i = 0, index = 0; i < 3; ++i)
		{
			for (UINT j = 0; j < 5; ++j)
			{
				_bagSlotList[index]->slotRect = Figure::RectMake(_mainRect.left + 95 + (57 + 10) * j, _mainRect.top + 144 + (58 + 10) * i, 57, 57);
				index++;
			}
		}

		//���� �κ��丮 ���� ��ġ ���
		for (UINT i = 0; i < 2; ++i)
		{
			_weponSlotList[i]->slotRect = Figure::RectMake(_mainRect.left + 596 + (73 + 95) * i, _mainRect.top + 57, 57, 57);
		}

		//���(��) �κ��丮 ���� ��ġ ���
		for (UINT i = 0; i < 3; ++i) 
		{
			_equipSlotList[i]->slotRect = Figure::RectMake(_mainRect.left + 460 + 57, _mainRect.top + 144 + (58 + 10) * i, 57, 57);
		}

		//���� �κ��丮 ���� ��ġ ���
		for (UINT i = 0; i < 1; ++i)
		{
			_potionSlotList[i]->slotRect = Figure::RectMake(_mainRect.left + 460 + 57, _mainRect.top + 299 + 58, 57, 57);
		}
		break;

		//�κ��丮 �ݱ�
	case Inventory::InventoryState::CloseSlide:
		//�κ��丮 ������ y �Ʒ��� 800.0f ��ŭ �̵��ϱ�
		_position.y += 1600.0f * _TimeManager->DeltaTime();

		//### �κ��丮�� ��� �������� �� �����ϱ� ���� ###
		//���� ������ y�� ȭ�� �߾��̰ų� �� ������  
		if (_position.y <= WinSizeY / 2)
		{
			//������ y�� ȭ�� �߾ӿ� ������Ű��
			_position.y = WinSizeY / 2;
		}

		//���� ������ y�� ȭ�� ������ ������ �������
		if (_position.y > WinSizeY + 1000)
		{
			//��Ƽ�� false ó�� (�� ���̰�)
			this->SetActive(false);
		}

		//��Ʈ ������Ʈ
		this->UpdateMainRect();

		//�÷��̾� �κ��丮 ���� ��ġ ���
		for (UINT i = 0; i < 5; ++i)
		{
			_playerSlotList[i]->slotRect = Figure::RectMake(_mainRect.left + 95 + (57 + 10) * i, _mainRect.top + 58, 57, 57);
		}
		
		//���� �κ��丮 ���� ��ġ ���
		for (UINT i = 0, index = 0; i < 3; ++i)
		{
			for (UINT j = 0; j < 5; ++j)
			{
				_bagSlotList[index]->slotRect = Figure::RectMake(_mainRect.left + 95 + (57 + 10) * j, _mainRect.top + 144 + (58 + 10) * i, 57, 57);
				index++;
			}
		}

		//���� �κ��丮 ���� ��ġ ���
		for (UINT i = 0; i < 2; ++i)
		{
			_weponSlotList[i]->slotRect = Figure::RectMake(_mainRect.left + 596 + (73 + 95) * i, _mainRect.top + 57, 57, 57);
		}

		//���(��) �κ��丮 ���� ��ġ ���
		for (UINT i = 0; i < 3; ++i)
		{
			_equipSlotList[i]->slotRect = Figure::RectMake(_mainRect.left + 460 + 57, _mainRect.top + 144 + (58 + 10) * i, 57, 57);
		}

		//���� �κ��丮 ���� ��ġ ���
		for (UINT i = 0; i < 1; ++i)
		{
			_potionSlotList[i]->slotRect = Figure::RectMake(_mainRect.left + 460 + 57, _mainRect.top + 299 + 58, 57, 57);
		}

		break;
		//�κ��丮 ���� ����
	case Inventory::InventoryState::Idle:
		//���� f4 ������ �κ��丮 �ݱ�
		if (_Input->GetKeyDown(VK_F4))
		{
			_state = InventoryState::CloseSlide;
		}

		break;
	default:
		break;
	}
}

//�κ��丮 Ÿ�� ������ ���� switch��
void Inventory::InvenTarget()
{
	switch (_targetState)
	{
	case Inventory::InvenTargetState::PlayerTarget:

		//Ű �̵� �Լ�
		KeyMove();

		break;
	case Inventory::InvenTargetState::BagTarget:
		//Ű �̵� �Լ�
		KeyMove();


		break;
	case Inventory::InvenTargetState::WeaponTarget:
		//Ű �̵� �Լ�
		KeyMove();

		break;
	case Inventory::InvenTargetState::EquipTarget:
		//Ű �̵� �Լ�
		KeyMove();

		break;

	case Inventory::InvenTargetState::PotionTarget:
		//Ű �̵� �Լ�
		KeyMove();

		break;
	default:
		break;
	}
}

void Inventory::Enable()
{
	this->_state = InventoryState::OpenSlide;

	vector<GameObject*> pObjectList = _ObjectManager->GetObjectList(ObjectType::Object);
	for (UINT i = 0; i < pObjectList.size(); ++i)
	{
		pObjectList[i]->SendCallbackMessage(TagMessage("InventoryOpen"));
	}
}

void Inventory::KeyMove()
{
	//�κ��丮 Ÿ�� �������� �̵�
	if (_Input->GetKeyDown('A'))
	{
		--_invenIndex;

		/****************************
				�÷��̾� Ÿ��
		*****************************/
		//���� �κ� Ÿ���� �÷��̾��� ���
		if (_targetState == InvenTargetState::PlayerTarget) 
		{
			//���� �ε����� -1�̸� �������� �̵���Ű��.  �� �������� �̵� �� ĭ�� ������, �ݴ��� ĭ���� �̵�
			if (_invenIndex == -1) 
			{
				//0���� �������� ���� ĭ���� ����
				_targetState = InvenTargetState::WeaponTarget;
				_invenIndex = 1;
			}
		}
		/****************************
				  ���� Ÿ��
		*****************************/
		else if (_targetState == InvenTargetState::BagTarget)
		{
			//���� �ε����� -1�̸� �������� �̵���Ű��. �� �������� �̵� �� ĭ�� ������, �ݴ��� ĭ���� �̵�
			if (_invenIndex == -1)
			{
				//0���� �������� ��� ĭ���� ����
				_targetState = InvenTargetState::EquipTarget;
				_invenIndex = 0;
			}

			//���� �ε����� 4�̸� �������� �̵���Ű��. �� ���� ĳ���� ��� �κ��� �߰��Ǹ� �� ĭ���� ���� ����
			else if (_invenIndex == 4) 
			{
				_targetState = InvenTargetState::EquipTarget;
				_invenIndex = 1;
			}
			//���� �ε����� 9�̸� �������� �̵���Ű��. �� ���� ĳ���� ��� �κ��� �߰��Ǹ� �� ĭ���� ���� ����
			else if (_invenIndex == 9) 
			{
				_targetState = InvenTargetState::EquipTarget;
				_invenIndex = 2;
			}
		}
		/****************************
				  ���� Ÿ��
		*****************************/
		else if (_targetState == InvenTargetState::WeaponTarget) 
		{
			//���� �ε����� -1�̸� ���� ĳ���� ĭ���� �̵���Ű��.
			if (_invenIndex == -1) 
			{
				//0���� �������� ĳ���� ĭ���� ����
				_targetState = InvenTargetState::PlayerTarget;
				_invenIndex = 4;
			}
		}

		/****************************
			   ���(��) Ÿ��
		*****************************/
		else if (_targetState == InvenTargetState::EquipTarget)
		{
			//���� �ε����� -1�̸� ���� ĭ���� �̵���Ű��.
			if (_invenIndex == -1)
			{
				//0���� �������� ���� ĭ���� ����
				_targetState = InvenTargetState::BagTarget;
				_invenIndex = 4;
			}

			//���� �ε����� 0�̸� ���� ĭ���� �̵���Ű��.
			else if (_invenIndex == 0)
			{
				_targetState = InvenTargetState::BagTarget;
				_invenIndex = 9;
			}

			//���� �ε����� 1�̸� ���� ĭ���� �̵���Ű��.
			else if (_invenIndex == 1)
			{
				_targetState = InvenTargetState::BagTarget;
				_invenIndex = 14;
			}
		}

		/****************************
			      ���� Ÿ��
		*****************************/
		else if (_targetState == InvenTargetState::PotionTarget) 
		{
			//���� �ε����� -1�̸� ���� ĭ���� �̵���Ű��.
			if (_invenIndex == -1)
			{
				//0���� �������� ���� ĭ���� ����
				_targetState = InvenTargetState::BagTarget;
				_invenIndex = 14;
			}
		}
	}

	//�κ��丮 Ÿ�� ���������� �̵�
	if (_Input->GetKeyDown('D'))
	{
		++_invenIndex;

		/****************************
				�÷��̾� Ÿ��
		*****************************/
		//���� �κ� Ÿ���� �÷��̾��� ���
		if (_targetState == InvenTargetState::PlayerTarget)
		{
			//���� �ε����� 5 �̸� ���� Ÿ������ �̵�
			if (_invenIndex == 5)
			{
				_targetState = InvenTargetState::WeaponTarget;
				_invenIndex = 0;
			}
		}
		/****************************
				  ���� Ÿ��
		*****************************/
		else if (_targetState == InvenTargetState::BagTarget)
		{
			//���� �ε����� 5�� ���, Ÿ�� ���´� ��� Ÿ������ �Ѿ��
			if (_invenIndex == 5)
			{
				_targetState = InvenTargetState::EquipTarget;
				_invenIndex = 0;
			}

			//���� �ε����� 10�� ���, Ÿ�� ���´� ��� Ÿ������ �Ѿ��
			else if (_invenIndex == 10)
			{
				_targetState = InvenTargetState::EquipTarget;
				_invenIndex = 1;
				cout << "in" << endl;
			}

			//���� �ε����� 15�� ���, Ÿ�� ���´� ��� Ÿ������ �Ѿ��
			else if (_invenIndex == 15)
			{
				_targetState = InvenTargetState::EquipTarget;
				_invenIndex = 2;
			}
		}
		/****************************
				  ���� Ÿ��
		*****************************/
		else if (_targetState == InvenTargetState::WeaponTarget)
		{
			//���� �ε����� 2�� ���, ĳ���� ĭ���� �̵���Ű��.
			if (_invenIndex == 2) 
			{
				//1���� Ŀ���� ĳ���� ĭ���� ����
				_targetState = InvenTargetState::PlayerTarget;
				_invenIndex = 0;
			}
		}

		/****************************
			   ���(��) Ÿ��
		*****************************/
		else if (_targetState == InvenTargetState::EquipTarget)
		{
			//���� �ε����� 1�� ��� ���� ĭ���� �̵��ϱ� 
			if (_invenIndex == 1)
			{
				_targetState = InvenTargetState::BagTarget;
				_invenIndex = 0;
			}

			//���� �ε����� 2�� ��� ���� ĭ���� �̵��ϱ� 
			else if (_invenIndex == 2)
			{
				_targetState = InvenTargetState::BagTarget;
				_invenIndex = 5;
			}

			//���� �ε����� 2�� ��� ���� ĭ���� �̵��ϱ� 
			else if (_invenIndex == 3)
			{
				_targetState = InvenTargetState::BagTarget;
				_invenIndex = 10;
			}
		}

		/****************************
			      ���� Ÿ��
		*****************************/
		else if (_targetState == InvenTargetState::PotionTarget)
		{
			//���� �ε����� 1�� ���, ���� ĭ���� �̵���Ű��.
			if (_invenIndex == 1)
			{
				_targetState = InvenTargetState::BagTarget;
				_invenIndex = 10;
			}
		}
	}

	//�κ��丮 Ÿ�� ���� �̵�
	if (_Input->GetKeyDown('W'))
	{
		_invenIndex -= 5;

		/****************************
				�÷��̾� Ÿ��
		*****************************/
		//���� �κ� Ÿ���� �÷��̾��� ���
		if (_targetState == InvenTargetState::PlayerTarget)
		{
			//���� �ε����� -5�̸� ���� �̵���Ű��. �� �ִ� ���̿��� ���� ������ �ݴ��� �Ʒ� ĭ���� �̵�
			if (_invenIndex == -5)	//-5
			{
				_targetState = InvenTargetState::BagTarget;
				_invenIndex = 10;
			}

			//���� �ε����� -4�̸� ���� �̵���Ű��. �� �ִ� ���̿��� ���� ������ �ݴ��� �Ʒ� ĭ���� �̵�
			if (_invenIndex == -4)	//
			{
				_targetState = InvenTargetState::BagTarget;
				_invenIndex = 11;
			}

			//���� �ε����� -3�̸� ���� �̵���Ű��. �� �ִ� ���̿��� ���� ������ �ݴ��� �Ʒ� ĭ���� �̵�
			if (_invenIndex == -3)	//-3
			{
				_targetState = InvenTargetState::BagTarget;
				_invenIndex = 12;
			}

			//���� �ε����� -2�̸� ���� �̵���Ű��. �� �ִ� ���̿��� ���� ������ �ݴ��� �Ʒ� ĭ���� �̵�
			if (_invenIndex == -2)		//-2
			{
				_targetState = InvenTargetState::BagTarget;
				_invenIndex = 13;
			}

			//���� �ε����� -1�̸� ���� �̵���Ű��. �� �ִ� ���̿��� ���� ������ �ݴ��� �Ʒ� ĭ���� �̵�
			if (_invenIndex == -1)		//-1
			{
				_targetState = InvenTargetState::BagTarget;
				_invenIndex = 14;
			}
		}
		/****************************
				  ���� Ÿ��
		*****************************/
		else if (_targetState == InvenTargetState::BagTarget)
		{
			//���� �ε����� -5�̸� ���� �̵���Ű��
			if (_invenIndex == -5)
			{
				_targetState = InvenTargetState::PlayerTarget;
				_invenIndex = 0;
			}

			//���� �ε����� -4�̸� ���� �̵���Ű��
			if (_invenIndex == -4)
			{
				_targetState = InvenTargetState::PlayerTarget;
				_invenIndex = 1;
			}

			//���� �ε����� -3�̸� ���� �̵���Ű��
			if (_invenIndex == -3)
			{
				_targetState = InvenTargetState::PlayerTarget;
				_invenIndex = 2;
			}

			//���� �ε����� -2�̸� ���� �̵���Ű��
			if (_invenIndex == -2)
			{
				_targetState = InvenTargetState::PlayerTarget;
				_invenIndex = 3;
			}

			//���� �ε����� -1�̸� ���� �̵���Ű��
			if (_invenIndex == -1)
			{
				_targetState = InvenTargetState::PlayerTarget;
				_invenIndex = 4;
			}
		}
		/****************************
				  ���� Ÿ��
		*****************************/
		else if (_targetState == InvenTargetState::WeaponTarget)
		{
			//���� �ε����� -5�̸� ���� �̵���Ű��. �� �ִ� ���̿��� ���� ������ �ݴ��� �Ʒ� ĭ���� �̵�
			if (_invenIndex == -5)
			{
				_targetState = InvenTargetState::PotionTarget;
				_invenIndex = 0;
			}

			//���� �ε����� -4�̸� ���� �̵���Ű��. �� �ִ� ���̿��� ���� ������ �ݴ��� �Ʒ� ĭ���� �̵�
			if (_invenIndex == -4)
			{
				_targetState = InvenTargetState::PotionTarget;
				_invenIndex = 0;
			}
		}

		/****************************
			   ���(��) Ÿ��
		*****************************/
		else if (_targetState == InvenTargetState::EquipTarget)
		{
			//���� �ε����� -5�̸� ���� �̵���Ű��
			if (_invenIndex == -5)
			{
				_targetState = InvenTargetState::WeaponTarget;
				_invenIndex = 0;
			}

			//���� �ε����� -4�̸� ���� �̵���Ű��
			if (_invenIndex == -4)
			{
				_targetState = InvenTargetState::EquipTarget;
				_invenIndex = 0;
			}

			//���� �ε����� -3�̸� ���� �̵���Ű��
			if (_invenIndex == -3)
			{
				_targetState = InvenTargetState::EquipTarget;
				_invenIndex = 1;
			}
		}

		/****************************
				  ���� Ÿ��
		*****************************/
		else if (_targetState == InvenTargetState::PotionTarget)
		{
			//���� �ε����� -5�̸� ���� �̵���Ű��
			if (_invenIndex == -5)
			{
				_targetState = InvenTargetState::EquipTarget;
				_invenIndex = 2;
			}
		}
	}

	//�κ��丮 Ÿ�� �Ʒ��� �̵�
	if (_Input->GetKeyDown('S'))
	{
		_invenIndex += 5;

		/****************************
				�÷��̾� Ÿ��
		*****************************/
		//���� �κ� Ÿ���� �÷��̾��� ���
		if (_targetState == InvenTargetState::PlayerTarget)
		{
			//���� �ε����� 5�̸� �Ʒ��� �̵���Ű��.
			if (_invenIndex == 5)
			{
				_targetState = InvenTargetState::BagTarget;
				_invenIndex = 0;
			}

			//���� �ε����� 6�̸� �Ʒ��� �̵���Ű��.
			if (_invenIndex == 6)
			{
				_targetState = InvenTargetState::BagTarget;
				_invenIndex = 1;
			}

			//���� �ε����� 7�̸� �Ʒ��� �̵���Ű��.
			if (_invenIndex == 7)
			{
				_targetState = InvenTargetState::BagTarget;
				_invenIndex = 2;
			}

			//���� �ε����� 8�̸� �Ʒ��� �̵���Ű��.
			if (_invenIndex == 8)
			{
				_targetState = InvenTargetState::BagTarget;
				_invenIndex = 3;
			}

			//���� �ε����� 9�̸� �Ʒ��� �̵���Ű��.
			if (_invenIndex == 9)
			{
				_targetState = InvenTargetState::BagTarget;
				_invenIndex = 4;
			}
		}
		/****************************
				  ���� Ÿ��
		*****************************/
		else if (_targetState == InvenTargetState::BagTarget)
		{
			//���� �ε����� 15�̸� �Ʒ��� �̵���Ű��. �� ���� �������� �Ʒ� ������ �ݴ��� �� ĭ���� �̵�
			if (_invenIndex == 15)
			{
				_targetState = InvenTargetState::PlayerTarget;
				_invenIndex = 0;
			}

			//���� �ε����� 16�̸� �Ʒ��� �̵���Ű��. �� ���� �������� �Ʒ� ������ �ݴ��� �� ĭ���� �̵�
			if (_invenIndex == 16)
			{
				_targetState = InvenTargetState::PlayerTarget;
				_invenIndex = 1;
			}

			//���� �ε����� 17�̸� �Ʒ��� �̵���Ű��. �� ���� �������� �Ʒ� ������ �ݴ��� �� ĭ���� �̵�
			if (_invenIndex == 17)
			{
				_targetState = InvenTargetState::PlayerTarget;
				_invenIndex = 2;
			}

			//���� �ε����� 18�̸� �Ʒ��� �̵���Ű��. �� ���� �������� �Ʒ� ������ �ݴ��� �� ĭ���� �̵�
			if (_invenIndex == 18)
			{
				_targetState = InvenTargetState::PlayerTarget;
				_invenIndex = 3;
			}

			//���� �ε����� 19�̸� �Ʒ��� �̵���Ű��. �� ���� �������� �Ʒ� ������ �ݴ��� �� ĭ���� �̵�
			if (_invenIndex == 19)
			{
				_targetState = InvenTargetState::PlayerTarget;
				_invenIndex = 4;
			}
		}
		/****************************
				  ���� Ÿ��
		*****************************/
		else if (_targetState == InvenTargetState::WeaponTarget)
		{
			//���� �ε����� 5�̸� �Ʒ��� �̵���Ű��.
			if (_invenIndex == 5)
			{
				_targetState = InvenTargetState::EquipTarget;
				_invenIndex = 0;
			}

			//���� �ε����� 6�̸� �Ʒ��� �̵���Ű��.
			if (_invenIndex == 6)
			{
				_targetState = InvenTargetState::EquipTarget;
				_invenIndex = 0;
			}
		}

		/****************************
			   ���(��) Ÿ��
		*****************************/
		else if (_targetState == InvenTargetState::EquipTarget)
		{
			//���� �ε����� 5�̸� �Ʒ��� �̵���Ű��.
			if (_invenIndex == 5)
			{
				_targetState = InvenTargetState::EquipTarget;
				_invenIndex = 1;
			}

			//���� �ε����� 6�̸� �Ʒ��� �̵���Ű��.
			if (_invenIndex == 6)
			{
				_targetState = InvenTargetState::EquipTarget;
				_invenIndex = 2;
			}

			//���� �ε����� 7�̸� �Ʒ��� �̵���Ű��.
			if (_invenIndex == 7)
			{
				_targetState = InvenTargetState::PotionTarget;
				_invenIndex = 0;
			}
		}

		/****************************
				  ���� Ÿ��
		*****************************/
		else if (_targetState == InvenTargetState::PotionTarget)
		{
			//���� �ε����� 5�̸� �Ʒ��� �̵���Ű��.  �� ���� �������� �Ʒ� ������ �ݴ��� �� ĭ���� �̵�
			if (_invenIndex == 5)
			{
				_targetState = InvenTargetState::WeaponTarget;
				_invenIndex = 0;
			}
		}
	}
}