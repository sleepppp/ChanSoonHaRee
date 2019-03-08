#pragma once
#include "GameObject.h"

//����ü -> �κ��丮 ������ ������ ����  ## ������ 
struct InvenItemData
{
	class Image* image;		//������ �̹���
	int itemIndex;			//������ �ε���
	string itemDescription;	//������ ����
	int itemAtk;			//������ ���ݷ�
	int itemDef;			//������ ����
	int itemSpd;			//������ �̵��ӵ�
	int itemHp;				//������ ü��
	InvenItemData()			//�����ڿ��� �ɹ� �̴ϼȶ������ �̹��� nullptr �ʱ�ȭ �ϱ�
		:image(nullptr) {}
};

//�κ��丮 ���� Ŭ���� �߰��� �����
//�κ��丮�� ���̴� ���� ó���� ���� �����ϱ� ����
class InventorySlot
{
private:
	friend class Inventory;	//������ Ŭ���� �κ��丮 ���� --> ���� ���� �����ϰԲ� ������ Ŭ���� ����
	InvenItemData data;		//�κ��丮 ������ ������ ����ü ���� ���� data
	bool isEmpty;			//������ ������ ����ִ� Ȯ���ϱ� ���� bool ���� isEmpty
	RECT slotRect;			//���� �׸��� ��Ʈ�� �����ϱ� ���� ��Ʈ ���� slotRect
	Vector2 size;			//���� ������
	int itemCount;
public:
	//������ �� ��� �Լ�
	Vector2 GetSize() { return size; }
};

//�κ��丮 Ŭ���� ---> GameObject�� ��ӹ���
class Inventory :public GameObject
{
	//�̳� Ŭ���� ItemType ����
	//������ ������ ���� ó���ϱ� ����
	enum class ItemType 
	{
		Normal = 0,
		Equip,
		End
	};
	//�̳� Ŭ���� InventoryState ����
	//�κ��丮 ���¿� ���� ó���ϱ� ����
	enum class InventoryState
	{
		OpenSlide,								//�κ� ����
		CloseSlide,								//�κ� �ݱ�
		Idle									//�κ� ����
	};
	
	enum class InvenTargetState 
	{
		PlayerTarget = 0,						//�÷��̾� Ÿ�� ����
		BagTarget,								//���� Ÿ�� ����
		WeaponTarget,							//���� Ÿ�� ����
		EquipTarget,							//���(��) Ÿ�� ����
		PotionTarget							//���� Ÿ�� ����
	};


private:
	class Image* _invenTargetImg;				//�κ��丮 ���� �̹���
	Vector2 _invenTargetPosition;				//�κ� Ÿ�� ������
	int _invenIndex;							//�κ� �ε���

	int _itemCount;								//������ ī��Ʈ (������ ���� ���ѿ�)


	bool _isInvenSlot;							//�κ� ���� �������� bool

	class Image* _inventoryImage;				//�κ��丮 �̹��� ���� ����
	vector<InventorySlot*> _playerSlotList;		//���� >> �÷��̾� ���� ����Ʈ ���� ����
	vector<InventorySlot*> _bagSlotList;		//���� >> ���� ���� ����Ʈ ���� ����
	vector<InventorySlot*> _weponSlotList;		//���� >> ���� ���� ����Ʈ ���� ����		
	vector<InventorySlot*> _equipSlotList;		//���� >> ��� ���� ����Ʈ ���� ����
	vector<InventorySlot*> _potionSlotList;		//���� >> ���� ���� ����Ʈ ���� ����

	InventoryState _state;						//�κ��丮 ���� ���� ����
	InvenTargetState _targetState;				//�κ��丮 Ÿ�� ���� ���� ����


	//�÷��̾� ���� ǥ��
	class Image* _invenPlayer;					//�κ��丮�� �÷��̾� ���� ǥ��

public:
	Inventory();
	~Inventory();

	void Init();
	void Release();
	void Update();
	void Render();

	bool AddItem(string name);					//��ȯ�� bool ��, �κ��丮�� ������ �߰��ϱ� ���� �Լ�, ���ڷ� ������ �̸��� ����

	void InvenState();							//�κ��丮 ���� �Լ�
	void InvenTarget();							//Ÿ�� ���� ������ ���� �Լ�

	void Enable()override;						//�κ��丮 �ѱ� �Լ�

	void KeyMove();								//���� Ű �Լ�
};

