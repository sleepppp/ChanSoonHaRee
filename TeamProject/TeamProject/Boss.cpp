#include "stdafx.h"
#include "Boss.h"
#include "Image.h"
#include "Animation.h"
#include "Player.h"
#include "Rock.h"
#include "Plankton.h"
Boss::Boss()
{
	//������ ������ ������ �⺻���� ��ݵ�
	_name = "Boss";
	this->_imagePosition = Vector2(1070, 340);	//��ǥ
	this->_size = Vector2(700, 700);		//ũ��
	this->_pivot = Pivot::CENTER;			//�߽���ġ
	this->_hp = 800;						//ü��
	this->_speed = 300.0f;					//�ӵ�
	this->_damage = 25;						//���ݷ�
	this->_distance = 0.f;					//�����Ÿ� (���߿� �����Ű� �ڵ常¥����)
	this->_angle = 0.f;						//�ޱ۰� (�����Ÿ��� ����)
	this->_imageRc = Figure::RectMakeCenter(_imagePosition, _imageSize); //��Ʈ����.
	this->CreateAnimatiom();
	this->_bossCollisionSize = Vector2(335, 300);
	this->_mainRect = Figure::RectMakeCenter(Vector2(_imagePosition.x - 35, _imagePosition.y + 70), _bossCollisionSize);
	//------------1�� ������ ���� ������-----------------//
	this->_shadowPosition = Vector2(_imagePosition.x, _imagePosition.y);
	this->_shadowSize = Vector2(50, 50);
	this->_shadowImage = _ImageManager->FindImage("shadow");
	this->_handPosition = Vector2(_shadowPosition.x, _shadowPosition.y - 400);
	this->_handSize = Vector2(150, 150);
	this->_handImage = _ImageManager->FindImage("hand");
	this->_timeCount = 0.f;
	this->_ChasingCount = 0;
	this->_drapCount = 0;
	this->_handFrame = 0;

	this->_shadowScale = 0.f;
	CreateHandAnimation();
	//----------------3�� ������ ���� ������------------//
	this->_slimePosition = Vector2(_imagePosition.x - 100, _imagePosition.y - 20);
	this->_slimeSize = Vector2(20, 20);
	this->_slimeRc = Figure::RectMakeCenter(_slimePosition, _slimeSize);

	//--------------���°� �ʱ�ȭ------------------//
	//�׸��ڵ� �ƹ��� ���� ������ �ȵǴϱ� �⺻���·� �־��ְ�
	_shadow = ShadowState::Stop;
	this->ChangeShadowState(ShadowState::Idle);
	//���� �׸��ڸ� x������ �i�ư��� �ֵ��Ⱥ��̴ϱ� ü�̻̽��·� �ΰ�
	_hand = HandState::Up;
	this->ChangeHandState(HandState::Chasing);

	//�ʱ� ���°��� ������ �������� �ʾƾ� �ϴϱ� ������ �ִ� ���¸� ������ش�.
	_state = StateType::Create;
	this->ChangeState(StateType::Fist_Shoot_First);
}


Boss::~Boss()
{
}

void Boss::Init()
{
	//�÷��̾��� �̸����� �ҷ��ͼ� ���� ���� �ְ� ����� �ش�.
	this->_player = (Player*)_ObjectManager->FindObject(ObjectType::Object, "Will");
}

void Boss::Release()
{
	AniImgIter iter = _aniImgList.begin();
	for (; iter != _aniImgList.end(); ++iter)
	{
		SafeDelete(iter->second);
	}
	_aniImgList.clear();

	_handIter iter1 = _handList.begin();
	for(; iter1 != _handList.end(); ++iter1)
	{
		SafeDelete(iter1->second);
	}
	_handList.clear();
}

void Boss::Update()
{
	//���Ǻ��� ó���� �κ��� ���⿡��
	UpdateState();
	//------------�ճ����� ��ų----------//
	HandShootHand();
	HandShootShadow();

	cout << _hp << endl;
	if (_Input->GetKeyDown('Q'))
	{
		_hp -= 800;
	}
	_aniImage->_animation->UpdateFrame();
}

void Boss::Render()
{
	
	if (_state != StateType::Dead)
	{
		_shadowScale = 1.4f - (_distance * 0.007f);
		if (_shadowScale < 0.5f)
		{
			_shadowScale = 0.5f;
		}
		if (_shadowScale > 0.8f)
		{
			_shadowScale = 0.8f;
		}

		_shadowImage->SetSize(_shadowImage->GetFrameSize(0));
		_shadowImage->SetAlpha(0.3f);
		_shadowImage->SetScale(_shadowScale);

		if (_shadow == ShadowState::Chasing || _shadow == ShadowState::Stop)
		{
			_shadowImage->Render(_shadowPosition.x, _shadowPosition.y, Pivot::CENTER, true);
		}

		if (_handAni != nullptr)
		{
			_handImage->SetSize(_handSize);
			_handImage->FrameRender((int)_handPosition.x, (int)_handPosition.y, _handAni->GetNowFrameX(), _handAni->GetNowFrameY(), Pivot::CENTER, true);
		}
	}
	_aniImage->_bossImage->SetSize(_size);
		_aniImage->_bossImage->FrameRender((int)_imagePosition.x, (int)_imagePosition.y, _aniImage->_animation->GetNowFrameX(), _aniImage->_animation->GetNowFrameY(), _pivot, true);

	if (_isDebug == true)
	{
	
		_DXRenderer->DrawRectangle(_shadowRc, DefaultBrush::yello, true);
		_DXRenderer->DrawRectangle(_handRc, DefaultBrush::yello, true);
		if (_hand == HandState::Stay)
		{
			_DXRenderer->DrawRectangle(_handRc, DefaultBrush::red, true);
		}
		_DXRenderer->DrawRectangle(_imageRc, DefaultBrush::blue, true);
		_DXRenderer->DrawEllipse(Vector2(_imagePosition.x, _imagePosition.y), _size.x * 0.7f, DefaultBrush::blue, true);
		_DXRenderer->DrawRectangle(_mainRect, DefaultBrush::blue, true);
		_DXRenderer->DrawRectangle(_slimeRc, DefaultBrush::green, true);
	}

	GameObject::Render();
}


void Boss::ChangeState(StateType state)
{
	//���� ���¿� �ٲ� ���°� ���ٸ� �� �Լ��� ����������.
	if (_state == state)
		return;
	//�װ� �ƴ϶�� ���¸� �ٲ��.
	_state = state;
	//���¿� ���� �ִϸ��̼ǵ� �ٲ����.
	this->ChangeAnimation(state);

	switch (_state)
	{
	case Boss::StateType::Idle:
		break;
	case Boss::StateType::Create:
		break;
	case Boss::StateType::Dead:
		//_imagePosition.y = 380.f;
		break;
	case Boss::StateType::Dead2:
		
		break;
	case Boss::StateType::Hand_Shoot_First:
		break;
	case Boss::StateType::Hand_Shoot_Second:
		this->ChangeShadowState(ShadowState::Chasing);
		break;
	case Boss::StateType::Hand_Shoot_Last:
		break;
	case Boss::StateType::Rock_Shoot_First:
		break;
	case Boss::StateType::Rock_Shoot_Second:
		RockPattom();
		break;
	case Boss::StateType::Rock_Shoot_Last:
		break;
	case Boss::StateType::Fist_Shoot_First:
		break;
	case Boss::StateType::Fist_Shoot_Second:
		break;
	case Boss::StateType::Fist_Shoot_Last:
		//for (int i = 0; i < 10; ++i)
		//{
		//	float x = _imagePosition.x + cosf(Math::PI + ((Math::PI / 10) * i) * 300);
		//	float y = _imagePosition.y + -sinf(Math::PI + ((Math::PI / 6) * i) * 300);
		//	_ObjectManager->AddObject(ObjectType::Object, new Plankton(Vector2(x, y)));
		//}
		break;
	case Boss::StateType::End:
		break;
	default:
		break;
	}
}

void Boss::UpdateState()
{
	switch (_state)
	{
	case Boss::StateType::Idle:
		//�÷��̾�� �������� �Ÿ��� ���� ������ X * 3 ���� �۾����ٸ� �������ιٲ��.
		if (_size.x * 0.7f > this->Distance(_imagePosition))
		{
			this->ChangeState(StateType::Create);
		}
		break;
	case Boss::StateType::Create:
		//���� ����ǰ��ִ��������� ������ �������̶��
		if (_aniImage->_animation->GetNowFrameX() == 31)
		{
			//�ճ����� ������ �������� �Ѱܶ�.
			ChangeState(StateType::Hand_Shoot_First);
		}
		break;
	case Boss::StateType::Dead:
		ChangeHandState(HandState::End);
		ChangeShadowState(ShadowState::End);
		break;
	case Boss::StateType::Hand_Shoot_First:
		//���� ����ǰ��ִ��������� ������ �������̶��
		if (_aniImage->_animation->GetNowFrameX() == 18)
		{
			//���� ������ ���ۺκ����� �Ѱܶ�.
			this->ChangeState(StateType::Hand_Shoot_Second);
		}
		this->Dead();

		break;
	case Boss::StateType::Hand_Shoot_Second:

		this->Dead();
		break;
	case Boss::StateType::Hand_Shoot_Last:

		ChangeHandState(HandState::End);
		ChangeShadowState(ShadowState::End);

		if (_aniImage->_animation->GetNowFrameX() == 10)
		{
			this->ChangeState(StateType::Rock_Shoot_First);
		}

		this->Dead();
		break;
	case Boss::StateType::Rock_Shoot_First:
		if (_aniImage->_animation->GetNowFrameX() == 15)
		{
			_Camera->Shake(3.8f, 0.9f);
			this->ChangeState(StateType::Rock_Shoot_Second);
		}
		this->Dead();
		break;
	case Boss::StateType::Rock_Shoot_Second:
		if (_aniImage->_animation->GetNowFrameX() == 25)
		{
			this->ChangeState(StateType::Rock_Shoot_Last);
		}
		this->Dead();
		break;
	case Boss::StateType::Rock_Shoot_Last:
		if (_aniImage->_animation->GetNowFrameX() == 31)
		{
			this->ChangeState(StateType::Fist_Shoot_First);
		}
		this->Dead();
		break;
	case Boss::StateType::Fist_Shoot_First:
		if (_aniImage->_animation->GetNowFrameX() == 16)
		{
			this->ChangeState(StateType::Fist_Shoot_Second);
		}
		this->Dead();
		break;
	case Boss::StateType::Fist_Shoot_Second:
		if (_aniImage->_animation->GetNowFrameX() == 21)
		{
			this->ChangeState(StateType::Fist_Shoot_Last);
		}
		this->Dead();
		break;
	case Boss::StateType::Fist_Shoot_Last:
		if (_aniImage->_animation->GetNowFrameX() == 15)
		{
			this->ChangeState(StateType::Hand_Shoot_First);
		}
		this->Dead();
		break;
	case Boss::StateType::End:
		break;
	default:
		break;
	}
}

void Boss::ChangeAnimation(StateType state)
{
	AniImgIter iter = _aniImgList.find(state);

	if (iter != _aniImgList.end())
	{
		_aniImage = iter->second;
		_aniImage->_animation->Stop();
		_aniImage->_animation->Play();
	}
}

void Boss::CreateAnimatiom()
{
	//�÷��̾ ���ʹ��� �����ݰ� �ۿ� ������� ����Ǵ� �ִϸ��̼ǰ� �̹���
	AniAndImage* idle = new AniAndImage;
	idle->_animation = new Animation;
	idle->_bossImage = _ImageManager->FindImage("create");
	idle->_animation->SetStartEndFrame(0, 0, 0, 0, false);
	idle->_animation->SetIsLoop(false);
	idle->_animation->SetFrameUpdateTime(1.f);
	_aniImgList.insert(make_pair(StateType::Idle, idle));

	//�÷��̾ ���ʹ̰� �ν��ϰ� ���ݸ���� ������ ���� �ڱ� �ڽ��� �ƿ�� �ִ�&�̹���
	AniAndImage* create = new AniAndImage;
	create->_animation = new Animation;
	create->_bossImage = _ImageManager->FindImage("create");
	create->_animation->SetStartEndFrame(0, 0, 31, 0, false);
	create->_animation->SetIsLoop(false);
	create->_animation->SetFrameUpdateTime(0.15f);
	_aniImgList.insert(make_pair(StateType::Create, create));

	//������ ������ ������ �ִ�&�̹���
	AniAndImage* dead1 = new AniAndImage;
	dead1->_animation = new Animation;
	dead1->_bossImage = _ImageManager->FindImage("dead1");
	dead1->_animation->SetStartEndFrame(0, 0, 40, 0, false);
	dead1->_animation->SetIsLoop(false);
	dead1->_animation->SetFrameUpdateTime(0.15f);
	dead1->_animation->SetCallbackFunc([this]() {this->NextAnimation(); });
	_aniImgList.insert(make_pair(StateType::Dead, dead1));
	
	//������ ������ ������ �ִ�& �̹���2
	AniAndImage* dead2 = new AniAndImage;
	dead2->_animation = new Animation;
	dead2->_bossImage = _ImageManager->FindImage("dead2");
	dead2->_animation->SetStartEndFrame(0, 0, 40, 0, false);
	dead2->_animation->SetIsLoop(false);
	dead2->_animation->SetFrameUpdateTime(0.15f);
	_aniImgList.insert(make_pair(StateType::Dead2, dead2));

	//������ 1��° �������� �ճ����� �����ϱ��� ���� ���� ������ �ִ�&�̹���
	AniAndImage* hand_Shoot_First = new AniAndImage;
	hand_Shoot_First->_animation = new Animation;
	hand_Shoot_First->_bossImage = _ImageManager->FindImage("hand_Shoot_First");
	hand_Shoot_First->_animation->SetStartEndFrame(0, 0, 19, 0, false);
	hand_Shoot_First->_animation->SetIsLoop(false);
	hand_Shoot_First->_animation->SetFrameUpdateTime(0.15f);
	_aniImgList.insert(make_pair(StateType::Hand_Shoot_First, hand_Shoot_First));

	//������ 1��° �������� �ճ����� �����ϱ��� ���� �̹� ���ư��� ������ ���� �ִ�&�̹���
	AniAndImage* hand_Shoot_Second = new AniAndImage;
	hand_Shoot_Second->_animation = new Animation;
	hand_Shoot_Second->_bossImage = _ImageManager->FindImage("hand_Shoot_second");
	hand_Shoot_Second->_animation->SetStartEndFrame(0, 0, 29, 0, false);
	hand_Shoot_Second->_animation->SetIsLoop(true);
	hand_Shoot_Second->_animation->SetFrameUpdateTime(0.15f);
	_aniImgList.insert(make_pair(StateType::Hand_Shoot_Second, hand_Shoot_Second));

	//������ 1��° �������� �ճ����� �����ϱ��� ���� ���ƿ��� �ִ�&�̹���
	AniAndImage* hand_Shoot_Last = new AniAndImage;
	hand_Shoot_Last->_animation = new Animation;
	hand_Shoot_Last->_bossImage = _ImageManager->FindImage("hand_Shoot_Last");
	hand_Shoot_Last->_animation->SetStartEndFrame(0, 0, 10, 0, false);
	hand_Shoot_Last->_animation->SetIsLoop(false);
	hand_Shoot_Last->_animation->SetFrameUpdateTime(0.15f);
	_aniImgList.insert(make_pair(StateType::Hand_Shoot_Last, hand_Shoot_Last));

	//������ 2��° ��ų ���� ������ºκ�.
	AniAndImage* Rock_Shoot_First = new AniAndImage;
	Rock_Shoot_First->_animation = new Animation;
	Rock_Shoot_First->_bossImage = _ImageManager->FindImage("Rock_Shoot");
	Rock_Shoot_First->_animation->SetStartEndFrame(0, 0, 15, 0, false);
	Rock_Shoot_First->_animation->SetIsLoop(false);
	Rock_Shoot_First->_animation->SetFrameUpdateTime(0.15f);
	_aniImgList.insert(make_pair(StateType::Rock_Shoot_First, Rock_Shoot_First));
	//������ 2��° ��ų ���̶������°� ��ٸ��鼭 ����ϴºκ�.
	AniAndImage* Rock_Shoot_Second = new AniAndImage;
	Rock_Shoot_Second->_animation = new Animation;
	Rock_Shoot_Second->_bossImage = _ImageManager->FindImage("Rock_Shoot");
	Rock_Shoot_Second->_animation->SetStartEndFrame(15, 0, 25, 0, false);
	Rock_Shoot_Second->_animation->SetIsLoop(false);
	Rock_Shoot_Second->_animation->SetFrameUpdateTime(0.15f);
	_aniImgList.insert(make_pair(StateType::Rock_Shoot_Second, Rock_Shoot_Second));
	//������ 2��° ��ų ���� ������� �⺻���·� ���ƿ��� �κ�.
	AniAndImage* Rock_Shoot_Last = new AniAndImage;
	Rock_Shoot_Last->_animation = new Animation;
	Rock_Shoot_Last->_bossImage = _ImageManager->FindImage("Rock_Shoot");
	Rock_Shoot_Last->_animation->SetStartEndFrame(25, 0, 31, 0, false);
	Rock_Shoot_Last->_animation->SetIsLoop(false);
	Rock_Shoot_Last->_animation->SetFrameUpdateTime(0.15f);
	_aniImgList.insert(make_pair(StateType::Rock_Shoot_Last, Rock_Shoot_Last));

	//������ 3��° ��ų �÷��̾ �����ϱ� ���� �غ����.
	AniAndImage* Fist_Shoot_First = new AniAndImage;
	Fist_Shoot_First->_animation = new Animation;
	Fist_Shoot_First->_bossImage = _ImageManager->FindImage("FistShoot");
	Fist_Shoot_First->_animation->SetStartEndFrame(0, 0, 16, 0, false);
	Fist_Shoot_First->_animation->SetIsLoop(false);
	Fist_Shoot_First->_animation->SetFrameUpdateTime(0.15f);
	_aniImgList.insert(make_pair(StateType::Fist_Shoot_First, Fist_Shoot_First));
	//������ �÷��̾ ���� ���� �����ϰ� �ִ� ����.
	AniAndImage* Fist_Shoot_Second = new AniAndImage;
	Fist_Shoot_Second->_animation = new Animation;
	Fist_Shoot_Second->_bossImage = _ImageManager->FindImage("FistShoot");
	Fist_Shoot_Second->_animation->SetStartEndFrame(0, 1, 21, 1, false);
	Fist_Shoot_Second->_animation->SetIsLoop(false);
	Fist_Shoot_Second->_animation->SetFrameUpdateTime(0.15f);
	_aniImgList.insert(make_pair(StateType::Fist_Shoot_Second, Fist_Shoot_Second));
	//������ �÷��̾ ���� ���� ��� �ֵθ��� ������� ���ƿ��� �ϴ� ����.
	AniAndImage* Fist_Shoot_Last = new AniAndImage;
	Fist_Shoot_Last->_animation = new Animation;
	Fist_Shoot_Last->_bossImage = _ImageManager->FindImage("FistShoot");
	Fist_Shoot_Last->_animation->SetStartEndFrame(0, 2, 15, 2, false);
	Fist_Shoot_Last->_animation->SetIsLoop(false);
	Fist_Shoot_Last->_animation->SetFrameUpdateTime(0.15f);
	_aniImgList.insert(make_pair(StateType::Fist_Shoot_Last, Fist_Shoot_Last));

}
//������ �״��̹����� Ŀ�� �ɰ�.
void Boss::NextAnimation()
{
	if (_state == StateType::Dead)
	{
		ChangeAnimation(StateType::Dead2);
		_imagePosition.y = 435.f;
	}

}

void Boss::RockPattom()
{
	for (int j = 0; j < 5; ++j)
	{
		//�������� ����.
		float timeCount = 1.f + (0.2f * j);

		for (int i = 0; i < 7; ++i)
		{
			float x = (_imagePosition.x) + cosf(Math::PI + (Math::PI / 6) * i) * (300 + (100 * j));
			float y = (_imagePosition.y - 1000) + (-sinf(Math::PI + (Math::PI / 6) * i)) * (300 + (100 * j));
			_ObjectManager->AddObject(ObjectType::Object, new Rock(Vector2(x, y), timeCount));
		}
	}

}
//�ǰݽ� �̹���
void Boss::AttackedDamage(int damage)
{
	_hp -= damage;
	if (_hp <= 0)
	{
		ChangeState(StateType::Dead);
	}
	else
	{

	}
}
//������ �ҷ����� �Լ�.
void Boss::Dead()
{
	//��ų������ ���߿� ü���� 0�̳� 0���϶��
	if (_hp <= 0)
	{
		//�״»��·� �Ѱܶ�.
		this->ChangeState(StateType::Dead);
	}
}


//�����Ÿ� ���� ���ϴ� ����.
float Boss::Distance(Vector2 position)
{
	//�����Ÿ��� ���ϰ�
	float distance = Math::GetDistance(position.x, position.y, _player->GetPosition().x, _player->GetPosition().y);
	//��ȯ��
	return distance;
}

//�ޱ۰����ϴ� ����.
float Boss::Angle(Vector2 position)
{
	//�ޱ۰��� ���ϰ�
	float angle = Math::GetAngle(position.x, position.y, _player->GetPosition().x, _player->GetPosition().y);
	//��ȯ��
	return angle;
}
