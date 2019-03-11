#include "stdafx.h"
#include "Player.h"

#include "Image.h"
#include "Animation.h"
#include "Timer.h"
#include "Enemy.h"
#include "MoveItem.h"
#include "Inventory.h"
#include "Arrow.h"
#include "Effect.h"


//���ʹ� ������ ������ ���� ����(�� 1��)	ok
//���ʹ� ������ �� ���� �Լ�				ok
//������ ���İ� ������							ok		
//���� ����, ����
//�ѹ��� Į �ֵθ���
//�ι� ������ �ι� �ֵθ���
//�ֵθ��� ���� ����� ��Ʈ�� �ѹ��� �������� �����Ѵ�.

//0310:���� ����(����) �̹������� �������� ��¦ Ƣ�� ������ �ξ�� ����
//�밢�� �Ѹ� �Ϸ�
//Į ����� �ֵθ��� ����ؼ� �����

using namespace Figure;

//�� �������� TItleScene���� TitleObject�� TitleFlowObject.cpp
//23,27�� Dungeon_map_02 ������ ������ 

Player::Player(Vector2 pos)
{
	//�̹��� �߰�, �Ŵ������� FInd �Ͽ� ã�ƿ�
	_ImageManager->AddFrameImage("Will", L"../Resources/Player/will_dungeon.png", 10, 13);
	this->_imgMove = _ImageManager->FindImage("Will");
	_ImageManager->AddFrameImage("Will_Sword", L"../Resources/Player/will_sword.png", 11, 4);
	this->_imgAtkSword = _ImageManager->FindImage("Will_Sword");
	_ImageManager->AddFrameImage("Will_Bow", L"../Resources/Player/will_bow.png", 9, 4);
	this->_imgAtkBow = _ImageManager->FindImage("Will_Bow");


	//�⺻ ���� �ʱ�ȭ
	this->_name = "Will";
	this->_size = Vector2(120, 120);
	this->_position = Vector2(627, 120);
	this->_position = pos;	//���ΰ� �Է� ���ϸ� ���νſ��� ���� �Է��Ѵ��
	this->_isActive = true;
	this->_pivot = Pivot::CENTER;
	this->_speed = 400.0f;
	this->UpdateMainRect();
	this->_maxHp = 100;
	this->_currentHp = 50;
	this->_isMoveStop = false;			//�������� ���߱� ���� bool��
	this->_isChangeSword = false;		//���ݽ� �̹��� ���� ������ ���� bool��
	this->_isChangeBow = false;			//Ȱ ���ݽ� �̹��� ���� ������ ���� bool��
	this->_isStandardMove = true;
	this->_damage = 20;					//�÷��̾� �⺻ ���� ������

	this->_frameIdle = 0.1f;			//���ǵ� ������ ���� ����
	this->_frameRun = 0.1f;				//���ǵ� ������ ���� ����
	this->_frameBow = 0.08f;
	this->_swordWidth= 40;
	this->_swordHeight= 20;

	this->_isAttacked = false;
	this->_isChangeWeapon = false;		//false�� Į, true�� Ȱ
	_blink = 0;
	this->_alpha = 1.0f;

	this->_isDelay = 0.f;
	this->_count = 0;
	//���� �浹�� ��Ʈ ��ġ �ʱ�ȭ
	this->_collisionRect = RectMakeCenter(_position, Vector2(60.f, 60.f));	
	//���º� �ִϸ��̼� ���� �����Ͽ� �ʿ� ��Ƶд�.
	this->CreateAnimation();

	// ó�� ���� ���¸� ���� ����
	this->ChangeState(State::DownIdle);

	//ȭ�� Ŭ����
	//_arrow = new Arrow(_pos, state);
	
}
Player::~Player() {}

/********************************************************************************/
//## Init ##
/********************************************************************************/
void Player::Init()
{	
	//AddCallbackMessage("InventoryOpen", [this](TagMessage message) {this->InventoryOnOff(); });
	AddCallbackMessage("InventoryClose", [this](TagMessage message) {this->InventoryOnOff(); });
}

/********************************************************************************/
//## Release ##
/********************************************************************************/
void Player::Release()
{
	AnimationIter iter = _animationList.begin();
	for (; iter != _animationList.end(); ++iter)
	{
		SafeDelete(iter->second);
	}
	_animationList.clear();
}

/********************************************************************************/
//## Update ##
/********************************************************************************/
void Player::Update()
{	

	//�̵��� ������ ����
	Vector2 moveValue(0, 0);
	
	if (_isMoveStop == false)
	{
		if (_Input->GetKeyDown('I'))
		{
			GameObject* _inventory = (Inventory*)_ObjectManager->FindObject(ObjectType::UI, "Inventory");
			_isMoveStop = true;
			_inventory->SetActive(true);	
		}

		//���� ����(Į<->Ȱ)
		if (_Input->GetKeyDown('Z'))
		{
			_isChangeBow = !_isChangeBow;
			
			//�׽�Ʈ��
			if (_isChangeBow)cout << "Bow" << endl;
			else  if (!_isChangeBow)cout << "Sword" << endl;
		}

		//&&&&&&���� ���� OK
		//���¿� ���� �ٸ��� ������Ʈ
		switch (_state)
		{
		case Player::State::LeftIdle:
			if (_Input->GetKey('A')) this->ChangeState(State::LeftRun);
			else if (_Input->GetKey('D')) this->ChangeState(State::RightRun);
			else if (_Input->GetKey('W')) this->ChangeState(State::UpRun);
			else if (_Input->GetKey('S')) this->ChangeState(State::DownRun);
			else if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::LeftRoll);
			else if (!_isChangeBow && _Input->GetKey('J')) this->ChangeState(State::LeftSword1);
			else if (_isChangeBow && _Input->GetKey('J')) this->ChangeState(State::LeftBow);
			//else if(_Input->GetKeyDown('Z'))
			break;

		case Player::State::RightIdle:
			if (_Input->GetKey('A')) this->ChangeState(State::LeftRun);
			else if (_Input->GetKey('D')) this->ChangeState(State::RightRun);
			else if (_Input->GetKey('W')) this->ChangeState(State::UpRun);
			else if (_Input->GetKey('S')) this->ChangeState(State::DownRun);
			else if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::RightRoll);
			else if (!_isChangeBow && _Input->GetKey('J')) this->ChangeState(State::RightSword1);
			else if (_isChangeBow && _Input->GetKey('J')) this->ChangeState(State::RightBow);
			break;

		case Player::State::UpIdle:
			if (_Input->GetKey('A')) this->ChangeState(State::LeftRun);
			else if (_Input->GetKey('D')) this->ChangeState(State::RightRun);
			else if (_Input->GetKey('W')) this->ChangeState(State::UpRun);
			else if (_Input->GetKey('S')) this->ChangeState(State::DownRun);
			else if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::UpRoll);
			else if (!_isChangeBow&&_Input->GetKey('J')) this->ChangeState(State::UpSword1);
			else if (_isChangeBow&& _Input->GetKey('J')) this->ChangeState(State::UpBow);
			break;

		case Player::State::DownIdle:
			if (_Input->GetKey('A')) this->ChangeState(State::LeftRun);
			else if (_Input->GetKey('D')) this->ChangeState(State::RightRun);
			else if (_Input->GetKey('W')) this->ChangeState(State::UpRun);
			else if (_Input->GetKey('S')) this->ChangeState(State::DownRun);
			else if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::DownRoll);
			else if (!_isChangeBow&&_Input->GetKey('J')) this->ChangeState(State::DownSword1);
			else if (_isChangeBow&&_Input->GetKey('J')) this->ChangeState(State::DownBow);
			break;

		case Player::State::LeftRun:
			if (_Input->GetKey('A')) moveValue += Vector2(-1.0f, 0.0f);		//�޴�����
			if (_Input->GetKeyUp('A')) this->ChangeState(State::LeftIdle); //�޶���

			//�밢�� ����		
			if (_Input->GetKey('W'))										//�밢�� �� ������
			{
				ChangeAnimation(Player::State::UpRun);
				moveValue += Vector2(0.0f, -1.0f);
			}
			else if (_Input->GetKey('S'))									//�밢�� �Ʒ� ������
			{
				moveValue += Vector2(0.0f, 1.0f);
				ChangeAnimation(Player::State::DownRun);
			}

			if (_Input->GetKeyUp('W'))			//�밢�� �� ����
			{
				ChangeAnimation(Player::State::LeftRun);
			}
			else if (_Input->GetKeyUp('S'))			//�밢�� �Ʒ� ����
			{
				this->ChangeState(State::LeftRun);
			}

			if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::LeftRoll);
			if (!_isChangeBow&&_Input->GetKey('J')) this->ChangeState(State::LeftSword1);
			else if(_isChangeBow&&_Input->GetKey('J')) this->ChangeState(State::LeftBow);
			break;

		case Player::State::RightRun:
			if (_Input->GetKey('D')) moveValue += Vector2(1.0f, 0.0f);
			if (_Input->GetKeyUp('D')) this->ChangeState(State::RightIdle);
			
			//�밢�� ����
			if (_Input->GetKey('W'))	//�밢�� ��
			{
				ChangeAnimation(Player::State::UpRun);
				moveValue += Vector2(0.0f, -1.0f);
			}
			else if (_Input->GetKey('S'))	//�밢�� �Ʒ�
			{
				moveValue += Vector2(0.0f, 1.0f);
				ChangeAnimation(Player::State::DownRun);
			}

			if (_Input->GetKeyUp('W'))
			{
				ChangeAnimation(Player::State::RightRun);
			}
			else if (_Input->GetKeyUp('S'))
			{
				ChangeAnimation(Player::State::RightRun);
			}
			if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::RightRoll);
			if (!_isChangeBow&&_Input->GetKey('J')) this->ChangeState(State::RightSword1);
			else if (_isChangeBow&&_Input->GetKey('J')) this->ChangeState(State::RightBow);
			break;

		case Player::State::UpRun:
			if (_Input->GetKey('W')) moveValue += Vector2(0.0f, -1.0f);
			if (_Input->GetKeyUp('W')) this->ChangeState(State::UpIdle);

			if (_Input->GetKey('A')) moveValue += Vector2(-1.0f, 0.0f);
			else if (_Input->GetKey('D')) moveValue += Vector2(1.0f, 0.0f);

			if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::UpRoll);
			if (!_isChangeBow&&_Input->GetKey('J')) this->ChangeState(State::UpSword1);
			else if (_isChangeBow&&_Input->GetKey('J')) this->ChangeState(State::UpBow);
			break;

		case Player::State::DownRun:
			if (_Input->GetKey('S')) moveValue += Vector2(0.0f, 1.0f);
			if (_Input->GetKeyUp('S')) this->ChangeState(State::DownIdle);

			if (_Input->GetKey('A')) moveValue += Vector2(-1.0f, 0.0f);
			else if (_Input->GetKey('D')) moveValue += Vector2(1.0f, 0.0f);

			if (_Input->GetKeyDown(VK_SPACE)) this->ChangeState(State::DownRoll);
			if (!_isChangeBow&&_Input->GetKey('J')) this->ChangeState(State::DownSword1);
			else if (_isChangeBow&&_Input->GetKey('J')) this->ChangeState(State::DownBow);
			break;

			//=====================================================================================
		case Player::State::LeftRoll:
			moveValue += Vector2(-2.0f, 0.0f);

			//�밢�� ����		
			if (_Input->GetKey('W'))										//�밢�� �� ������
			{
				moveValue += Vector2(0.0f, -2.0f);
			}
			else if (_Input->GetKey('S'))										//�밢�� �� ������
			{
				moveValue += Vector2(0.0f, 2.0f);
			}
			break;

		case Player::State::RightRoll:
			moveValue += Vector2(2.0f, 0.0f);

			//�밢�� ����		
			if (_Input->GetKey('W'))										//�밢�� �� ������
			{
				moveValue += Vector2(0.0f, -2.0f);
			}
			else if (_Input->GetKey('S'))										//�밢�� �� ������
			{
				moveValue += Vector2(0.0f, 2.0f);
			}
			break;

		case Player::State::UpRoll:
			moveValue += Vector2(0.0f, -2.0f);

			//�밢�� ����		
			if (_Input->GetKey('A'))										//�밢�� �� ������
			{
				moveValue += Vector2(-2.0f, 0.0f);
			}
			else if (_Input->GetKey('D'))										//�밢�� �� ������
			{
				moveValue += Vector2(2.0f, 0.0f);
			}
			break;

		case Player::State::DownRoll:
			moveValue += Vector2(0.0f, 2.0f);

			//�밢�� ����		
			if (_Input->GetKey('A'))										//�밢�� �� ������
			{
				moveValue += Vector2(-2.0f, 0.0f);
			}
			else if (_Input->GetKey('D'))										//�밢�� �� ������
			{
				moveValue += Vector2(2.0f, 0.0f);
			}


			break;
			//=====================================================================================
		case Player::State::LeftSword1:			
			this->Attack();
			break;

		case Player::State::RightSword1:			
			this->Attack();
			break;

		case Player::State::UpSword1:			
			this->Attack();
			break;

		case Player::State::DownSword1:			
			this->Attack();
			break;
			//=====================================================================================
		case Player::State::LeftSword2:
			this->Attack();
			break;

		case Player::State::RightSword2:
			this->Attack();
			break;

		case Player::State::UpSword2:
			this->Attack();
			break;

		case Player::State::DownSword2:
			this->Attack();
			break;

		case Player::State::LeftBow:		
			this->Enable();
			break;

		case Player::State::RightBow:
			//_ObjectManager->FindObject(ObjectType::Object, new Arrow(Vector2(_position), Arrow::State::Right));
			break;

		case Player::State::UpBow:
			//_ObjectManager->FindObject(ObjectType::Object, new Arrow(Vector2(_position), Arrow::State::Up));
			break;
			
		case Player::State::DownBow:
			//_ObjectManager->FindObject(ObjectType::Object, new Arrow(Vector2(_position), Arrow::State::Down));




		default:
			break;
		}

		//�̵� �� �浹���� �Լ� ȣ����
		this->Move(moveValue);
	}

	//�������� ������Ʈ ���ش�.
	_mainAnimation->UpdateFrame();
	
	//���� ���� ���� ó�� �Լ�
	this->AtkDelay2();

}

/********************************************************************************/
//## Render ##
/********************************************************************************/
void Player::Render()
{
	//�̹��� ������ ����
	_imgMove->SetSize(_size);
	_imgAtkSword->SetSize(_size);
	_imgAtkBow->SetSize(_size);
	//���İ��� �޾ƿ������� ����
	_imgMove->SetAlpha(_alpha);

	//������: �ΰ��� �̹����� ��Ȳ�� �°� �����ư��鼭 ����ϵ��� ������ �ش�.
	//���� ��ü�� �ϴ� ���¿��� �⺻ ���� ����ؾ� �ϹǷ� ���� ��ư �������� �����ϵ��� �ٸ� ������ �� ��
	
	if (_isStandardMove == true)
	{
		_imgMove->FrameRender((int)_position.x, _position.y, _mainAnimation->GetNowFrameX(), _mainAnimation->GetNowFrameY(), Pivot::CENTER, true);
	}
	else if (_isChangeSword == true)
	{		
		_imgAtkSword->FrameRender((int)_position.x, _position.y, _mainAnimation->GetNowFrameX(), _mainAnimation->GetNowFrameY(), Pivot::CENTER, true);
	}	
	else if (_isChangeBow == true)
	{
		_imgAtkBow->FrameRender((int)_position.x, _position.y, _mainAnimation->GetNowFrameX(), _mainAnimation->GetNowFrameY(), Pivot::CENTER, true);
		//_arrow->Render();
	}
	
	//����� ����� ����� ��Ʈ�� ������ (F1)
	if (_isDebug)
	{
		_DXRenderer->DrawRectangle(_mainRect, DefaultBrush::red, true);
		_DXRenderer->DrawRectangle(_collisionRect, DefaultBrush::red, true);
		//���ݸ��(�̹���)�� true�̰� ���������� false�϶��� �׸���
		
		if (_isChangeSword && !_isAttacked)_DXRenderer->DrawRectangle(_swordRect, DefaultBrush::green, true);
		//_DXRenderer->DrawRectangle(_obColliRect, DefaultBrush::green, true);
	}
}

/********************************************************************************/
//## ChangeState ##
//���¸� �ٲ� ���� _state=state; ���ٴ� ���� �Լ��� ���ؼ� �����ϸ� 
//����� �� �ڵ� ������ ��������.
/********************************************************************************/
void Player::ChangeState(State state)
{
	//'I'��ư�� ������ �������� �ʰ� ����
	if (_isMoveStop == true) return;

	//�� ���¿� �����ϴٸ� �����Ű�� �ʰ� ����������
	if (_state == state) return;

	//�� ���¿� �������� �ʴٸ� �����Ѵ�.
	_state = state;
	//���°� �ٲ�鼭 �ִϸ��̼ǵ� �����Ѵ�
	this->ChangeAnimation(state);


	//���°� �ٲ�� ���� ó���� ..������ ���� ����
	switch (_state)
	{
	case Player::State::LeftIdle:
		_isChangeSword = false;		
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
	case Player::State::RightIdle:
		_isChangeSword = false;
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
	case Player::State::UpIdle:
		_isChangeSword = false;
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
	case Player::State::DownIdle:
		_isChangeSword = false;
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
	case Player::State::LeftRun:
		_isChangeSword = false;
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
	case Player::State::RightRun:
		_isChangeSword = false;
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
	case Player::State::UpRun:
		_isChangeSword = false;
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
	case Player::State::DownRun:
		_isChangeSword = false;
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
	case Player::State::LeftRoll:
		_isChangeSword = false;
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
	case Player::State::RightRoll:
		_isChangeSword = false;
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
	case Player::State::UpRoll:
		_isChangeSword = false;
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
	case Player::State::DownRoll:
		_isChangeSword = false;
		//_isChangeBow = false;
		_isStandardMove = true;
		break;
		//======================================================
	case Player::State::LeftSword1:
		_isChangeSword = true;		
		//_isChangeBow = false;
		_isAttacked = false;
		_isStandardMove = false;
		//if(_isChangeSword)this->_swordRect = RectMakeCenter(_position.x - 40, _position.y, _swordWidth, _swordHeight); //Į ��Ʈ
		if (_isChangeSword)this->_swordRect = RectMakeCenter(_position.x - 40, _position.y, _swordWidth, _swordHeight); //Į ��Ʈ
		break;
	case Player::State::RightSword1:
		_isChangeSword = true;
		//_isChangeBow = false;
		_isAttacked = false;	
		_isStandardMove = false;
		if (_isChangeSword)this->_swordRect = RectMakeCenter(_position.x + 40, _position.y, _swordWidth, _swordHeight); //Į ��Ʈ 
		break;
	case Player::State::UpSword1:
		_isChangeSword = true;	
		//_isChangeBow = false;
		_isAttacked = false;	
		_isStandardMove = false;
		if (_isChangeSword)this->_swordRect = RectMakeCenter(_position.x, _position.y - 40, _swordHeight, _swordWidth); //Į ��Ʈ
		break;
	case Player::State::DownSword1:
		_isChangeSword = true;
		//_isChangeBow = false;
		_isAttacked = false;
		_isStandardMove = false;
		if (_isChangeSword)this->_swordRect = RectMakeCenter(_position.x, _position.y + 40, _swordHeight, _swordWidth); //Į ��Ʈ
		break;
		//======================================================
	case Player::State::LeftSword2:
		_isChangeSword = true;
		//_isChangeBow = false;
		_isAttacked = false;
		_isStandardMove = false;
		if (_isChangeSword)this->_swordRect = RectMakeCenter(_position.x - 40, _position.y, _swordWidth, _swordHeight); //Į ��Ʈ
		break;
	case Player::State::RightSword2:
		_isChangeSword = true;
		//_isChangeBow = false;
		_isAttacked = false;
		_isStandardMove = false;
		if (_isChangeSword)this->_swordRect = RectMakeCenter(_position.x + 40, _position.y, _swordWidth, _swordHeight);  //Į ��Ʈ
		break;
	case Player::State::UpSword2:
		_isChangeSword = true;
		//_isChangeBow = false;
		_isAttacked = false;
		_isStandardMove = false;
		if (_isChangeSword)this->_swordRect = RectMakeCenter(_position.x, _position.y - 40, _swordHeight, _swordWidth);  //Į ��Ʈ
		break;
	case Player::State::DownSword2:
		_isChangeSword = true;
		//_isChangeBow = false;
		_isAttacked = false;
		_isStandardMove = false;
		if (_isChangeSword)this->_swordRect = RectMakeCenter(_position.x, _position.y + 40, _swordHeight, _swordWidth);  //Į ��Ʈ
		break;
		//======================================================
	case Player::State::LeftBow:
		_isChangeSword = false;
		//_isChangeBow = true;
		_isStandardMove = false;
		_ObjectManager->AddObject(ObjectType::Object, new Arrow(Vector2(_position), Arrow::State::Left));
		break;

	case Player::State::RightBow:
		_isChangeSword = false;
		//_isChangeBow = true;
		_isStandardMove = false;
		_ObjectManager->AddObject(ObjectType::Object, new Arrow(Vector2(_position), Arrow::State::Right));
		break;

	case Player::State::UpBow:
		_isChangeSword = false;
		//_isChangeBow = true;
		_isStandardMove = false;
		_ObjectManager->AddObject(ObjectType::Object, new Arrow(Vector2(_position), Arrow::State::Up));
		break;

	case Player::State::DownBow:
		_isChangeSword = false;
		//_isChangeBow = true;
		_isStandardMove = false;
		_ObjectManager->AddObject(ObjectType::Object, new Arrow(Vector2(_position), Arrow::State::Down));
		break;

	default:		
		break;
	}
}



/********************************************************************************/
//## Move ##
//Vector2 direction:����
/********************************************************************************/
void Player::Move(Vector2 direction)
{
	//�̵����� �ʾҴٸ� Float EQUAL�� �Ҽ������������� Ȯ���Ͽ� �̵��� ���� �ʾҴٸ� returnó���Ͽ� ����������.
	if (FLOAT_EQUAL(direction.x,0.f) && FLOAT_EQUAL(direction.y,0.f))
		return;

	//�� ��ǥ�� ����*���ǵ�*��ŸŸ��
	this->_position += direction.Normalize()*_speed*_TimeManager->DeltaTime();
	//�̵������� ���� �浹 ��Ʈ ��ġ�� �����Ѵ�.
	_collisionRect = RectMakeCenter(_position, Vector2(60.0f, 60.0f));
	
	//mainRect�� ��ġ�� ����
	this->UpdateMainRect();	
	
	//=======================================
	//������Ʈ�� �浹(InterRect�Լ� ���)
	//=======================================
	const vector <class GameObject*>* object;
	object = _ObjectManager->GetObjectListPointer(ObjectType::Object);
	
	//��� ������Ʈ��  for������ �浹 �˻縦 ���ش�.
	//enemy���� �浹�� ����
	//enemy�� ���� ȣ���ϸ�(!=) �浹 �˻縦 �Ѵ�.
	for (int i = 0; i < object->size(); i++)
	{
		//�÷��̾� �ڽ��� �����ϱ� ���� ���ǹ�
		if(object->at(i)->GetName()!=this->_name)
		{
			//���ʹ� Ŭ���� ����ȯ���� ������Ʈ i�� �ҷ��´�.
			Enemy* enemy = dynamic_cast<Enemy*>(object->at(i));
			//������ Ŭ���� ����ȯ���� ������Ʈ i�� �ҷ��´�.
			MoveItem* item = dynamic_cast<MoveItem*>(object->at(i));
				
			//�� ��ȯ�� ���� �� ���빰�� �ƴ� ��쿡�� ����Ѵ�.
			if (enemy == nullptr && item == nullptr)
			{
				//���� �Լ� InterRee�� �÷��̾� �浹�� �Լ��� ��ü ������Ʈ�� �浹 �˻��Ѵ�.
				if (this->InterRee(&_collisionRect, &object->at(i)->GetCollisionRect()))
				{
					//�浹�� ĳ���� �÷��̾ �ݴ�� �о��ָ鼭 ���ڸ��� �ӹ���ó�� �Ѵ�.
					_position.x = (_collisionRect.right - _collisionRect.left) / 2 + _collisionRect.left;
					_position.y = (_collisionRect.bottom - _collisionRect.top) / 2 + _collisionRect.top;
					_mainRect = RectMakeCenter(_position.x, _position.y, _size.x, _size.y);
				}
			}
		}
	}	
	//���ʹ̿��� �浹	
	//this->SendCallbackMessage(TagMessage("PlayerHP",0.0f, this->_currentHp));
	
	//Enemy* enemy = dynamic_cast<Enemy*>(object[i]);
	//Enemy Ŭ������ ����Ű�� enemy�� ��´�.
	//dynamic_case���̳��� ĳ��(��Ӱ����� ��� ����ȯ(ex: (float)hp ), ������ null���� ��ȯ���༭ ��!)
	//<Enemy*> ������ Ÿ�Կ�... ���ʹ̸� ����Ű�� Ŭ������ ��ҳ�?
	//�ش� ������Ʈ �迭[i]�� ȣ��
}

/********************************************************************************/
//## ChangeAnimation ##
//���¿� ���� �ִϸ��̼��� �ٲ��ش�. (Ű���� State state)
/********************************************************************************/
void Player::ChangeAnimation(State state)
{
	//�ݺ��ڸ� ���� �ʿ��� �ش� Ű���� �ִϸ��̼��� ã�´�.
	AnimationIter iter = _animationList.find(state);

	//���� ���� �ƴϸ� ã�� ���̴� �� �ִϸ��̼��� �ٲ� �ִϸ��̼����� ��ü�Ѵ�.
	if (iter != _animationList.end())
	{
		if (iter->second != _mainAnimation)
		{
			_mainAnimation = iter->second;
			_mainAnimation->Stop();
			_mainAnimation->Play();
		}
	}
}

/********************************************************************************/
//## CreateAnimation ##
//�ִϸ��̼� ���� �̸� ���� �� �ʱ�ȭ ���� �� �ʿ� ��Ƽ� ����
/********************************************************************************/
void Player::CreateAnimation()
{
	Animation* leftIdle = new Animation;							//���º��� �ϳ��� new�� �͵������
	leftIdle->SetStartEndFrame(0, 9, 9, 9, false);					//�ѵ����� ����x,y,��x,y �������ÿ�
	leftIdle->SetIsLoop(true);										//���������� true, fa��se
	leftIdle->SetFrameUpdateTime(_frameIdle);						//�����Ӵ� �ð��� �־��ָ� �ʹ̴�
	_animationList.insert(make_pair(State::LeftIdle, leftIdle));	//�� �� ��������� inset�� �ʿ� �� ������

	Animation* rightIdle = new Animation;
	rightIdle->SetStartEndFrame(0, 8, 9, 8, false);
	rightIdle->SetIsLoop(true);
	rightIdle->SetFrameUpdateTime(_frameIdle);
	_animationList.insert(make_pair(State::RightIdle, rightIdle));

	Animation* upIdle = new Animation;
	upIdle->SetStartEndFrame(0, 10, 9, 10, false);
	upIdle->SetIsLoop(true);
	upIdle->SetFrameUpdateTime(_frameIdle);
	_animationList.insert(make_pair(State::UpIdle, upIdle));

	Animation* downIdle = new Animation;
	downIdle->SetStartEndFrame(0, 11, 9, 11, false);
	downIdle->SetIsLoop(true);
	downIdle->SetFrameUpdateTime(_frameIdle);
	_animationList.insert(make_pair(State::DownIdle, downIdle));

	Animation* leftRun = new Animation;
	leftRun->SetStartEndFrame(0, 3, 7, 3, false);
	leftRun->SetIsLoop(true);
	leftRun->SetFrameUpdateTime(_frameRun);
	_animationList.insert(make_pair(State::LeftRun, leftRun));

	Animation* rightRun = new Animation;
	rightRun->SetStartEndFrame(0, 2, 7, 2, false);
	rightRun->SetIsLoop(true);
	rightRun->SetFrameUpdateTime(_frameRun);
	_animationList.insert(make_pair(State::RightRun, rightRun));

	Animation* upRun = new Animation;
	upRun->SetStartEndFrame(0, 0, 7, 0, false);
	upRun->SetIsLoop(true);
	upRun->SetFrameUpdateTime(_frameRun);
	_animationList.insert(make_pair(State::UpRun, upRun));

	Animation* downRun = new Animation;
	downRun->SetStartEndFrame(0, 1, 7, 1, false);
	downRun->SetIsLoop(true);
	downRun->SetFrameUpdateTime(_frameRun);
	_animationList.insert(make_pair(State::DownRun, downRun));

	Animation* leftRoll = new Animation;
	leftRoll->SetStartEndFrame(0, 5, 7, 5, false);
	leftRoll->SetIsLoop(false);
	leftRoll->SetFrameUpdateTime(_frameRun);	
	leftRoll->SetCallbackFunc([this]() {this->EndAnimation(); });	
	_animationList.insert(make_pair(State::LeftRoll, leftRoll));

	Animation* rightRoll = new Animation;
	rightRoll->SetStartEndFrame(0, 4, 7, 4, false);
	rightRoll->SetIsLoop(false);
	rightRoll->SetFrameUpdateTime(_frameRun);
	rightRoll->SetCallbackFunc([this]() {this->EndAnimation(); });	//���ٽ� �Լ� ȣ��
	_animationList.insert(make_pair(State::RightRoll, rightRoll));

	Animation* upRoll = new Animation;
	upRoll->SetStartEndFrame(0, 6, 7, 6, false);
	upRoll->SetIsLoop(false);
	upRoll->SetFrameUpdateTime(_frameRun);
	upRoll->SetCallbackFunc([this]() {this->EndAnimation(); });		//�������� �� ���� �����Ѵ�
	_animationList.insert(make_pair(State::UpRoll, upRoll));

	Animation* downRoll = new Animation;
	downRoll->SetStartEndFrame(0, 7, 7, 7, false);
	downRoll->SetIsLoop(false);
	downRoll->SetFrameUpdateTime(_frameRun);
	downRoll->SetCallbackFunc([this]() {this->EndAnimation(); });	//�� ����� public�� ����� �ָ� ������!
	_animationList.insert(make_pair(State::DownRoll, downRoll)); 
	//======================================================================
	Animation* leftSword1 = new Animation;
	leftSword1->SetStartEndFrame(0, 3, 4, 3, false);
	leftSword1->SetIsLoop(false);
	leftSword1->SetFrameUpdateTime(_frameRun);
	leftSword1->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::LeftSword1, leftSword1));

	Animation* rightSword1 = new Animation;
	rightSword1->SetStartEndFrame(0, 2, 4, 2, false);
	rightSword1->SetIsLoop(false);
	rightSword1->SetFrameUpdateTime(_frameRun);
	rightSword1->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::RightSword1, rightSword1));

	Animation* upSword1 = new Animation;
	upSword1->SetStartEndFrame(0, 0, 4, 0, false);
	upSword1->SetIsLoop(false);
	upSword1->SetFrameUpdateTime(_frameRun);
	upSword1->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::UpSword1, upSword1));

	Animation* downSword1 = new Animation;	
	downSword1->SetStartEndFrame(0, 1, 4, 1, false);
	downSword1->SetIsLoop(false);
	downSword1->SetFrameUpdateTime(_frameRun);
	downSword1->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::DownSword1, downSword1));
	//=======================================================================
	Animation* leftSword2 = new Animation;
	leftSword2->SetStartEndFrame(5, 3, 10, 3, false);
	leftSword2->SetIsLoop(false);
	leftSword2->SetFrameUpdateTime(_frameRun);
	leftSword2->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::LeftSword2, leftSword2));

	Animation* rightSword2 = new Animation;
	rightSword2->SetStartEndFrame(5, 2, 10, 2, false);
	rightSword2->SetIsLoop(false);
	rightSword2->SetFrameUpdateTime(_frameRun);
	rightSword2->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::RightSword2, rightSword2));

	Animation* upSword2 = new Animation;
	upSword2->SetStartEndFrame(5, 0, 10, 0, false);
	upSword2->SetIsLoop(false);
	upSword2->SetFrameUpdateTime(_frameRun);
	upSword2->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::UpSword2, upSword2));

	Animation* downSword2 = new Animation;
	downSword2->SetStartEndFrame(5, 1, 10, 1, false);
	downSword2->SetIsLoop(false);
	downSword2->SetFrameUpdateTime(_frameRun);
	downSword2->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::DownSword2, downSword2));
	//=====================================================================================
	Animation* leftBow = new Animation;
	leftBow->SetStartEndFrame(0, 3, 8, 3, false);
	leftBow->SetIsLoop(false);
	leftBow->SetFrameUpdateTime(_frameBow);
	leftBow->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::LeftBow, leftBow));

	Animation* rightBow = new Animation;
	rightBow->SetStartEndFrame(0, 2, 8, 2, false);
	rightBow->SetIsLoop(false);
	rightBow->SetFrameUpdateTime(_frameBow);
	rightBow->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::RightBow, rightBow));

	Animation* upBow = new Animation;
	upBow->SetStartEndFrame(0, 0, 8, 0, false);
	upBow->SetIsLoop(false);
	upBow->SetFrameUpdateTime(_frameBow);
	upBow->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::UpBow, upBow));

	Animation* downBow = new Animation;
	downBow->SetStartEndFrame(0, 1, 8, 1, false);
	downBow->SetIsLoop(false);
	downBow->SetFrameUpdateTime(_frameBow);
	downBow->SetCallbackFunc([this]() {this->EndAnimation(); });
	_animationList.insert(make_pair(State::DownBow, downBow));

}

//�ش� ���� ���� �� ������ ���� 
void Player::EndAnimation()
{
	switch (_state)
	{
	case Player::State::LeftIdle:
		break;
	case Player::State::RightIdle:
		break;
	case Player::State::UpIdle:
		break;
	case Player::State::DownIdle:
		break;
	case Player::State::LeftRun:
		break;
	case Player::State::RightRun:
		break;
	case Player::State::UpRun:
		break;
	case Player::State::DownRun:
		break;
	case Player::State::LeftRoll:
		if(_Input->GetKey('A')) this->ChangeState(State::LeftRun);
		else					this->ChangeState(State::LeftIdle);		
		break;
	case Player::State::RightRoll:
		if (_Input->GetKey('D')) this->ChangeState(State::RightRun);
		else					this->ChangeState(State::RightIdle);
		break;
	case Player::State::UpRoll:
		if (_Input->GetKey('W')) this->ChangeState(State::UpRun);
		else					this->ChangeState(State::UpIdle);
		break;
	case Player::State::DownRoll:
		if (_Input->GetKey('S')) this->ChangeState(State::DownRun);
		else					this->ChangeState(State::DownIdle);
		break;
		//================================================================
	case Player::State::LeftSword1:
		if (_Input->GetKey('J')) this->ChangeState(State::LeftSword2);
		else if (_Input->GetKeyDown('J')) this->ChangeState(State::LeftSword2);
		else if (_Input->GetKey('A')) this->ChangeState(State::LeftRun);
		else					this->ChangeState(State::LeftIdle);
		break;
	case Player::State::RightSword1:
		if (_Input->GetKey('J')) this->ChangeState(State::RightSword2);
		else if (_Input->GetKey('D')) this->ChangeState(State::RightRun);
		else					this->ChangeState(State::RightIdle);
		break;
	case Player::State::UpSword1:
		if (_Input->GetKey('J')) this->ChangeState(State::UpSword2);
		else if (_Input->GetKey('W')) this->ChangeState(State::UpRun);
		else					this->ChangeState(State::UpIdle);
		break;
	case Player::State::DownSword1:
		if (_Input->GetKey('J')) this->ChangeAnimation(State::DownSword2);
		else if (_Input->GetKey('S')) this->ChangeState(State::DownRun);
		else					this->ChangeState(State::DownIdle);
		break;
		//================================================================
	case Player::State::LeftSword2:
		if (_Input->GetKey('J')) this->ChangeAnimation(State::LeftSword1);
		else if (_Input->GetKey('A')) this->ChangeState(State::LeftRun);
		else					this->ChangeState(State::LeftIdle);
		break;
	case Player::State::RightSword2:
		if (_Input->GetKey('J')) this->ChangeAnimation(State::RightSword1);
		else if (_Input->GetKey('D')) this->ChangeState(State::RightRun);
		else					this->ChangeState(State::RightIdle);
		break;
	case Player::State::UpSword2:
		if (_Input->GetKey('J')) this->ChangeAnimation(State::UpSword1);
		else if (_Input->GetKey('W')) this->ChangeState(State::UpRun);
		else					this->ChangeState(State::UpIdle);
		break;
	case Player::State::DownSword2:
		if (_Input->GetKey('J')) this->ChangeAnimation(State::DownSword1);
		else if (_Input->GetKey('S')) this->ChangeState(State::DownRun);
		else					this->ChangeState(State::DownIdle);		
		break;
		//==============================================================
	case Player::State::LeftBow:
		if (_Input->GetKeyDown('J')) this->ChangeState(State::LeftBow);
		//else if (_Input->GetKey('A')) this->ChangeAnimation(State::LeftRun);
		else							this->ChangeState(State::LeftIdle);
		break;

	case Player::State::RightBow:
		if (_Input->GetKeyDown('J')) this->ChangeState(State::RightBow);
		//else if (_Input->GetKey('S')) this->ChangeAnimation(State::RightRun);
		else
		{
			this->ChangeState(State::RightIdle);
		}

		break;

	case Player::State::UpBow:
		if (_Input->GetKeyDown('J')) this->ChangeState(State::UpBow);
		//else if (_Input->GetKey('S')) this->ChangeAnimation(State::UpRun);
		else						this->ChangeState(State::UpIdle);
		break;

	case Player::State::DownBow:
		if (_Input->GetKeyDown('J')) this->ChangeState(State::DownBow);
		else
		{
			this->ChangeState(State::DownIdle);
		}
		break;

	default:
		break;
	}
}

/********************************************************************************/
//## InterRect ##
//������Ʈ�� �浹�� ���� �Լ�
/********************************************************************************/
bool Player::InterRee(RECT* moveRc, RECT* unMoveRc)
{
	RECT temp;
	if (!IntersectRect(&temp, moveRc, unMoveRc))
	{
		return false;
		//return false�� �������� �ʰ� ������ ��. �׷��� false�� ���� ���°� ����
		//reuturn�� ������ �����°� �߿�!
	}

	int tempWidth = temp.right - temp.left;
	int tempHeight = temp.bottom - temp.top;


	//���α��̰� �� �дٸ� //���Ϸ� �ε��� ����̴�.
	if (tempWidth > tempHeight)
	{
		//�÷��̾� ��->�Ϸ� �浹
		if (moveRc->bottom == temp.bottom)
		{
			//�浹���� ���̸�ŭ �÷��̾�� �����༭ ������ ������.
			//_position.y -= tempHeight;
			moveRc->top -= tempHeight;
			moveRc->bottom -= tempHeight;
		}

		//�÷��̾� ��->������ �浹
		if (moveRc->top == temp.top)
		{
			//�浹���� ���̸�ŭ �÷��̾�� ���༭ ���� �ø���.
			//_position.y += tempHeight;
			moveRc->top += tempHeight;
			moveRc->bottom += tempHeight;
		}
	}
	//���� ���� ���̰� �� ��ٸ� //�¿�� �ε��� ����̴�
	else if (tempHeight > tempWidth)
	{
		//return false;
		//�÷��̾� ��->�·� �浹
		if (moveRc->left == temp.left)
		{
			//���� �÷��̾� ��Ʈ�� �浹�������� �����ʿ��� �ִٸ�,�������̸�ŭ �����ش�.
			//_position.x += tempWidth;
			moveRc->left += tempWidth;
			moveRc->right += tempWidth;
		}

		//�÷��̾� ��->��� �浹
		else if (moveRc->right == temp.right)
		{
			//_position.x -= tempWidth;
			moveRc->left -= tempWidth;
			moveRc->right -= tempWidth;
		}
	}
	return true;
	//return true
}

//=======================================
//�÷��̾� ��ġ ���� �Լ� (�κ��� XY�� ����)
//=======================================
POINT Player::GetPlayerIndex()
{
	POINT IndexXY = { _mainAnimation->GetNowFrameX(), _mainAnimation->GetNowFrameY() };
	return IndexXY;
}

//=======================================
//�� �����Լ�
//=======================================
void Player::Attack()
{
	if (_isAttacked == false)
	{
		const vector <class GameObject*>* object;
		object = _ObjectManager->GetObjectListPointer(ObjectType::Object);
		for (int i = 0; i < object->size(); i++)
		{
			//�÷��̾� �ڽ��� �����ϱ� ���� ���ǹ�
			if (object->at(i)->GetName() != this->_name)
			{
				Enemy* enemy = dynamic_cast<Enemy*>(object->at(i));

				//����� ���ʹ� �浹, ������ ������Ʈ�� ���� ���� ��츸 �˻�
				if (enemy != nullptr)
				{
					RECT temp;
					if (IntersectRect(&temp, &_swordRect, &object->at(i)->GetCollisionRect()))
					{
						//�浹������ false�����϶�(�� ���� �浹 ���°� �ƴϾ�����)

						//���������� �޾Ƽ� ü���� ��´�
						enemy->AttackedDemege(_damage);
						_isAttacked = true;
					}
				}
			}

			if (_isAttacked == true)
			{
				Effect::PlayEffect(EFFECT_SWORDATK, Vector2(_swordRect.left, _swordRect.top));
			}
		}
	}

}

//=======================================
//�κ��丮 on/off ��ư�� �Լ�
//=======================================
void Player::InventoryOnOff()
{
	_isMoveStop = false;
}

//=======================================
//�������� �޾Ƽ� �÷��̾� ü���� ��� �Լ�
//������ ���ʹ̿���, �� �Լ��� �޾� ü���� ���̸� ����� �÷��̾� ��ü�� �浹�� ��
//=======================================
void Player::AttackedDamage(int damage)
{
	if (_isDelay == false)
	{
		cout << "Fucking " << endl;
		this->_currentHp -= damage;
		_isDelay = true;
		_blink = 0;
	}	
}

//=======================================
//���ʹ̿� �浹��, �����ð� �ο�/�÷��̾� ������ �Լ�
//=======================================
void Player::AtkDelay2()
{	
	if (_isDelay == true)
	{
		_count += _TimeManager->DeltaTime();
		if (_count > 0.2f)
		{
			_blink++;
			_count = 0;
			_alpha = !_alpha;
			
			if (_blink == 6)
			{
				_isDelay = false;
				_alpha = 1.0f;
			}
		}
		
	}
}