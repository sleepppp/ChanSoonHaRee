#pragma once
#include "GameObject.h"

//구조체 -> 인벤토리 아이템 데이터 선언  ## 아이템 
struct InvenItemData
{
	class Image* image;		//아이템 이미지
	int itemIndex;			//아이템 인덱스
	string itemDescription;	//아이템 설명
	int itemAtk;			//아이템 공격력
	int itemDef;			//아이템 방어력
	int itemSpd;			//아이템 이동속도
	int itemHp;				//아이템 체력
	InvenItemData()			//생성자에서 맴버 이니셜라이즈로 이미지 nullptr 초기화 하기
		:image(nullptr) {}
};

//인벤토리 슬롯 클래스 추가로 만들기
//인벤토리에 보이는 슬롯 처리를 따로 구분하기 위함
class InventorySlot
{
private:
	friend class Inventory;	//프렌드 클래스 인벤토리 선언 --> 서로 접근 가능하게끔 프렌드 클래스 선언
	InvenItemData data;		//인벤토리 아이템 데이터 구조체 변수 선언 data
	bool isEmpty;			//아이템 슬롯이 비어있는 확인하기 위한 bool 변수 isEmpty
	RECT slotRect;			//슬롯 그림에 렉트를 생성하기 위한 렉트 변수 slotRect
};

//인벤토리 클래스 ---> GameObject를 상속받음
class Inventory :public GameObject
{
	//이넘 클래스 ItemType 선언
	//아이템 종류에 따라 처리하기 위함
	enum class ItemType 
	{
		Normal = 0,
		Equip,
		End
	};
	//이넘 클래스 InventoryState 선언
	//인벤토리 상태에 따라 처리하기 위함
	enum class InventoryState
	{
		OpenSlide,								//인벤 열기
		CloseSlide,								//인벤 닫기
		Idle									//인벤 유지
	};

private:
	class Image* _inventoryImage;				//인벤토리 이미지 변수 선언
	vector<InventorySlot*> _playerSlotList;		//벡터 >> 플레이어 슬롯 리스트 변수 선언
	vector<InventorySlot*> _bagSlotList;		//벡터 >> 가방 슬롯 리스트 변수 선언
	InventoryState _state;						//인벤토리 상태 변수 선언
public:
	Inventory();
	~Inventory();

	void Init();
	void Release();
	void Update();
	void Render();

	bool AddItem(string name);					//반환형 bool 값, 인벤토리에 아이템 추가하기 위한 함수, 인자로 아이템 이름을 받음

	void Enable()override;						//인벤토리 켜기 함수
};

