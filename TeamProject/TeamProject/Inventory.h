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

private:
	class Image* _inventoryImage;				//�κ��丮 �̹��� ���� ����
	vector<InventorySlot*> _playerSlotList;		//���� >> �÷��̾� ���� ����Ʈ ���� ����
	vector<InventorySlot*> _bagSlotList;		//���� >> ���� ���� ����Ʈ ���� ����
	InventoryState _state;						//�κ��丮 ���� ���� ����
public:
	Inventory();
	~Inventory();

	void Init();
	void Release();
	void Update();
	void Render();

	bool AddItem(string name);					//��ȯ�� bool ��, �κ��丮�� ������ �߰��ϱ� ���� �Լ�, ���ڷ� ������ �̸��� ����

	void Enable()override;						//�κ��丮 �ѱ� �Լ�
};

