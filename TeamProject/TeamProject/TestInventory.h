#pragma once
#include "GameObject.h"
class TestInventory : public GameObject
{
	enum class State
	{
		OpenSlide,CloseSlide,Idle
	};
private:
	vector<class TestInventorySlot*> _slotList;	//���Ե�
	class Image* _windowImage;					//�κ��丮 â �̹���
	class Image* _targetImage;					//Ÿ�� ���� ����Ű�� �̹���
	int _targetIndex;							//Ÿ�� ���� �ε���
	State _state;								//�κ��丮 ���� 
public:
	TestInventory();
	~TestInventory();

	void Init()override; 
	void Release()override; 
	void Update()override; 
	void Render()override; 

	bool AddItem(string name);

private:
	void MoveIndex(int i);
	void UpdateSlotPosition();
	TestInventorySlot* FindSlot(string name);
};

