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
	//이름
	this->_name = "Inventory";

	//이미지 추가
	//LSTRING /.. 은 이전 폴더로 이동 /로 타고 타고 넘어갈 수 있다. png 파일도 사용 가능
	//false는 픽셀 충돌 할 건지 말 건지 체크용
	this->_inventoryImage = _ImageManager->AddImage("InventoryWindow", L"../Resources/UI/inventory.png", false);

	//인벤토리 위치 잡기
	//X 포지션은 화면 가로 중앙
	//Y 포지션은 화면 맨 밑 + 이미지 높이만큼    why? 인벤토리는 처음에는 숨겨져 있기 때문.
	this->_position = Vector2(WinSizeX / 2, WinSizeY +_inventoryImage->GetHeight());

	//인벤토리 크기 잡기
	//X 크기는 인벤토리 이미지 가로 길이만큼     (int)는 형변환
	//Y 크기는 인벤토리 이미지 세로 길이만큼     (int)는 형변환
	this->_size = Vector2((int)_inventoryImage->GetWidth(), (int)_inventoryImage->GetHeight());

	//인벤토리 생성할 지점
	//중앙(CENTER)에 생성 
	this->_pivot = Pivot::CENTER;

	//업데이트 렉트 처리
	this->UpdateMainRect();
	//233 185

	//플레이어 슬롯 렉트 생성
	//플레이어 슬롯은 5칸
	for (UINT i = 0; i < 5; ++i)
	{
		//인벤토리 슬롯 클래스 포인터 slot = 인벤토리 클래스 NEW 선언
		InventorySlot* slot = new InventorySlot;
		
		//슬롯 -> 슬롯 렉트 = left top 기준으로 렉트 생성. 
		//X시작 좌표는 메인 렉트.left + 95 + (57 + 10) * i 만큼 간격으로 5번 생성, 즉 5개의 렉트 생성
		//Y시작 좌표는 메인 렉트.top + 58
		//X,Y 크기는 57, 57
		slot->slotRect = Figure::RectMake(_mainRect.left +  95 + (57 + 10) * i, _mainRect.top + 58, 57, 57);

		//아직 아이템이 들어가지 않았으므로 슬롯 isEmpty는 true
		slot->isEmpty = true;
		
		//렉트가 5개 생성되고 플레이어 인벤토리 슬롯도 5개 생성 필요하기 때문에
		//push_back에 new 선언한 slot을 담는다.
		_playerSlotList.push_back(slot);
	}

	//인벤토리 상태 초기화
	_state = InventoryState::OpenSlide;
}

//인벤토리 Release
void Inventory::Release()
{
	//플레이어 슬롯 생성한 만큼(size) SafeDelete해주기
	for (UINT i = 0; i < _playerSlotList.size(); ++i)
	{
		SafeDelete(_playerSlotList[i]);
	}
}


//인벤토리 Update
void Inventory::Update()
{	
	//스윗치문 _state : 인벤토리 상태 처리
	switch (_state)
	{
	//인벤토리 열기
	case Inventory::InventoryState::OpenSlide:
		//인벤토리 포지션 y 위로 800.0f 만큼 이동하기
		_position.y -= 800.0f * _TimeManager->DeltaTime();


		//### 인벤토리가 계속 올라가는 걸 방지하기 위함 ###
		//만일 포지션 y가 화면 중앙이거나 더 작으면  
		if (_position.y <= WinSizeY / 2)
		{
			//포지션 y를 화면 중앙에 고정시키고
			_position.y = WinSizeY / 2;
			//인벤토리 상태 유지하기
			_state = InventoryState::Idle;
		}
		this->UpdateMainRect();

		//플레이어 인벤토리 슬롯 위치 잡기
		for (UINT i = 0; i < 5; ++i)
		{
			_playerSlotList[i]->slotRect = Figure::RectMake(_mainRect.left + 95 + (57 + 10) * i, _mainRect.top + 58, 57, 57);
		}
		break;
	//인벤토리 닫기
	case Inventory::InventoryState::CloseSlide:
		//인벤토리 포지션 y 아래로 800.0f 만큼 이동하기
		_position.y += 800.0f * _TimeManager->DeltaTime();
		
		//### 인벤토리가 계속 내려가는 걸 방지하기 위함 ###
		//만일 포지션 y가 화면 중앙이거나 더 작으면  
		if (_position.y <= WinSizeY / 2)
		{
			//포지션 y를 화면 중앙에 고정시키고
			_position.y = WinSizeY / 2;
			//액티브 false 처리 (안 보이게)
			this->SetActive(false);
		}
		this->UpdateMainRect();

		//플레이어 인벤토리 슬롯 위치 잡기
		for (UINT i = 0; i < 5; ++i)
		{
			_playerSlotList[i]->slotRect = Figure::RectMake(_mainRect.left + 95 + (57 + 10) * i, _mainRect.top + 58, 57, 57);
		}
		break;
	//인벤토리 상태 유지
	case Inventory::InventoryState::Idle:
		//만일 f1 누르면 인벤토리 닫기
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
	//만일 인벤토리 이미지에 값이 없지 않으면 (=값이 있으면) 렌더하기
	if (_inventoryImage != nullptr)
		_inventoryImage->Render(_mainRect.left, _mainRect.top, Pivot::LEFT_TOP, false);

	_DXRenderer->DrawRectangle(_mainRect, DefaultBrush::red, false);

	// 
	for (UINT i = 0; i < _playerSlotList.size(); ++i)
	{
		_DXRenderer->DrawRectangle(_playerSlotList[i]->slotRect, DefaultBrush::red, false);

		//슬롯에 아이템이 들어왔다면
		if(_playerSlotList[i]->data.image)
		{
			//아이템 이미지 크기를 슬롯 렉트에 맞춰서 슬롯 렉트에 담기
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
				_playerSlotList[i]->data.itemDescription = "이 아이템은 나뭇가지다~";
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
