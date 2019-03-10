#include "stdafx.h"
#include "Boss.h"
#include "Image.h"
#include "Animation.h"
#include "Player.h"


Boss::Boss()
{
	//������ ������ ������ �⺻���� ��ݵ�
	_name = "Boss";
	this->_imagePosition = Vector2(1070, 340);	//��ǥ
	this->_size = Vector2(700, 700);		//ũ��
	this->_pivot = Pivot::CENTER;			//�߽���ġ
	this->_hp = 800;						//ü��
	this->_mainSpeed = this->_speed = 300.0f;					//�ӵ�
	this->_demage = 0;						//���ݷ�
	this->_distance = 0.f;					//�����Ÿ� (���߿� �����Ű� �ڵ常¥����)
	this->_angle = 0.f;						//�ޱ۰� (�����Ÿ��� ����)
	this->_imageRc = Figure::RectMakeCenter(_imagePosition, _imageSize); //��Ʈ����.
	this->CreateAnimatiom();
	
	//------------1�� ������ ���� ������-----------------//
	this->_shadowPosition = Vector2(_imagePosition.x, _imagePosition.y);
	this->_shadowSize = Vector2(50, 50);
	this->_shadowImage = _ImageManager->AddImage("shadow", L"../Resources/Enemy/Boss/Shadow.png", true);
	this->_fistPosition = Vector2(_shadowPosition.x, _shadowPosition.y - 400);
	this->_fistSize = Vector2(150, 150);
	this->_handImgae = _ImageManager->AddFrameImage("fist", L"../Resources/Enemy/Boss/hand.png", 19, 1, true);
	this->_timeCount = 0.f;
	this->_shadowCollisionCount = 0;
	this->_handAttackCount = 0;
	this->_isShadowChasing = false;
	this->_isArmChasing = false;

	//�ʱ� ���°��� ������ �������� �ʾƾ� �ϴϱ� ������ �ִ� ���¸� ������ش�.
	_state = StateType::Create;
	this->ChangeState(StateType::Idle);
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
}

void Boss::Update()
{
	//���Ǻ��� ó���� �κ��� ���⿡��
	UpdateState();

	_aniImage->_animation->UpdateFrame();
}

void Boss::Render()
{
	_aniImage->_bossImage->SetSize(_size);
	_aniImage->_bossImage->FrameRender((int)_imagePosition.x, (int)_imagePosition.y, _aniImage->_animation->GetNowFrameX(),
		_aniImage->_animation->GetNowFrameY(), _pivot, true);

	_shadowImage->SetSize(_shadowImage->GetFrameSize(0));
	_shadowImage->SetAlpha(0.3f);
	_shadowImage->SetScale(0.7f);
	_shadowImage->Render(_shadowPosition.x, _shadowPosition.y, Pivot::CENTER, true);

	if (_isDebug == true)
	{
		_DXRenderer->DrawRectangle(_shadowRc, DefaultBrush::yello, true);
		_DXRenderer->DrawRectangle(_fistRc, DefaultBrush::yello, true);
		_DXRenderer->DrawRectangle(_imageRc, DefaultBrush::blue, true);
		_DXRenderer->DrawEllipse(Vector2(_imagePosition.x, _imagePosition.y), _size.x * 0.7f, DefaultBrush::blue, true);
	}
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
		break;
	case Boss::StateType::Hand_Shoot_First:
		break;
	case Boss::StateType::Hand_Shoot_Second:
		break;
	case Boss::StateType::Hand_Shoot_Last:
		break;
	case Boss::StateType::Rock_Shoot_First:
		break;
	case Boss::StateType::Rock_Shoot_Second:
		break;
	case Boss::StateType::Rock_Shoot_Last:
		break;
	case Boss::StateType::Fist_Shoot_First:
		break;
	case Boss::StateType::Fist_Shoot_Second:
		break;
	case Boss::StateType::Fist_Shoot_Last:
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

		break;
	case Boss::StateType::Hand_Shoot_First:
		//���� ����ǰ��ִ��������� ������ �������̶��
		if (_aniImage->_animation->GetNowFrameX() == 18)
		{
			//���� ������ ���ۺκ����� �Ѱܶ�.
			ChangeState(StateType::Hand_Shoot_Second);
		}
		this->Dead();

		break;
	case Boss::StateType::Hand_Shoot_Second:

		HandShoot();

		if (_handAttackCount == 5)
		{
			ChangeState(StateType::Hand_Shoot_Last);
		}
		this->Dead();
		break;
	case Boss::StateType::Hand_Shoot_Last:

		if (_aniImage->_animation->GetNowFrameX() == 10)
		{
			ChangeState(StateType::Fist_Shoot_First);
		}

		this->Dead();
		break;
	case Boss::StateType::Rock_Shoot_First:
		break;
	case Boss::StateType::Rock_Shoot_Second:
		break;
	case Boss::StateType::Rock_Shoot_Last:
		break;
	case Boss::StateType::Fist_Shoot_First:
		break;
	case Boss::StateType::Fist_Shoot_Second:
		break;
	case Boss::StateType::Fist_Shoot_Last:
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
	idle->_bossImage = _ImageManager->AddFrameImage("idle", L"../resources/Enemy/Boss/CreateBoss.png", 32, 1, true);
	idle->_animation->SetStartEndFrame(0, 0, 0, 0, false);
	idle->_animation->SetIsLoop(false);
	idle->_animation->SetFrameUpdateTime(1.f);
	_aniImgList.insert(make_pair(StateType::Idle, idle));

	//�÷��̾ ���ʹ̰� �ν��ϰ� ���ݸ���� ������ ���� �ڱ� �ڽ��� �ƿ�� �ִ�&�̹���
	AniAndImage* create = new AniAndImage;
	create->_animation = new Animation;
	create->_bossImage = _ImageManager->AddFrameImage("create", L"../resources/Enemy/Boss/CreateBoss.png", 32, 1, true);
	create->_animation->SetStartEndFrame(0, 0, 31, 0, false);
	create->_animation->SetIsLoop(false);
	create->_animation->SetFrameUpdateTime(0.2f);
	_aniImgList.insert(make_pair(StateType::Create, create));

	//������ ������ ������ �ִ�&�̹���
	AniAndImage* dead = new AniAndImage;
	dead->_animation = new Animation;
	dead->_bossImage = _ImageManager->AddFrameImage("dead", L"../Resources/Enemy/Boss/deadBoss.png", 82, 1, true);
	dead->_animation->SetStartEndFrame(0, 0, 81, 0, false);
	dead->_animation->SetIsLoop(false);
	dead->_animation->SetFrameUpdateTime(0.2f);
	_aniImgList.insert(make_pair(StateType::Dead, dead));
	
	//������ 1��° �������� �ճ����� �����ϱ��� ���� ���� ������ �ִ�&�̹���
	AniAndImage* hand_Shoot_First = new AniAndImage;
	hand_Shoot_First->_animation = new Animation;
	hand_Shoot_First->_bossImage = _ImageManager->AddFrameImage("hand_Shoot_First", L"../Resources/Enemy/Boss/Hand_Shoot_First.png", 20, 1, true);
	hand_Shoot_First->_animation->SetStartEndFrame(0, 0, 19, 0, false);
	hand_Shoot_First->_animation->SetIsLoop(false);
	hand_Shoot_First->_animation->SetFrameUpdateTime(0.2f);
	_aniImgList.insert(make_pair(StateType::Hand_Shoot_First, hand_Shoot_First));

	//������ 1��° �������� �ճ����� �����ϱ��� ���� �̹� ���ư��� ������ ���� �ִ�&�̹���
	AniAndImage* hand_Shoot_Second = new AniAndImage;
	hand_Shoot_Second->_animation = new Animation;
	hand_Shoot_Second->_bossImage = _ImageManager->AddFrameImage("hand_Shoot_second", L"../Resources/Enemy/Boss/Hand_Shoot_Second.png", 30, 1, true);
	hand_Shoot_Second->_animation->SetStartEndFrame(0, 0, 29, 0, false);
	hand_Shoot_Second->_animation->SetIsLoop(true);
	hand_Shoot_Second->_animation->SetFrameUpdateTime(0.2f);
	_aniImgList.insert(make_pair(StateType::Hand_Shoot_Second, hand_Shoot_Second));

	//������ 1��° �������� �ճ����� �����ϱ��� ���� ���ƿ��� �ִ�&�̹���
	AniAndImage* hand_Shoot_Last = new AniAndImage;
	hand_Shoot_Last->_animation = new Animation;
	hand_Shoot_Last->_bossImage = _ImageManager->AddFrameImage("hand_Shoot_Last", L"../Resources/Enemy/Boss/Hand_Shoot_Last.png", 11, 1, true);
	hand_Shoot_Last->_animation->SetStartEndFrame(0, 0, 10, 0, false);
	hand_Shoot_Last->_animation->SetIsLoop(false);
	hand_Shoot_Last->_animation->SetFrameUpdateTime(0.2f);
	_aniImgList.insert(make_pair(StateType::Hand_Shoot_Last, hand_Shoot_Last));
}

//������ �ҷ����� �Լ�.
void Boss::Dead()
{
	//��ų������ ���߿� ü���� 0�̳� 0���϶��
	if (_hp <= 0)
	{
		//�״»��·� �Ѱܶ�.
		ChangeState(StateType::Dead);
	}
}

void Boss::HandShoot()
{
	//���� �÷��̾ �i�� �����.
	if (_shadowCollisionCount < 5)
	{
		_isShadowChasing = true;
		_isArmChasing = false;
	}

	//���� �÷��̾ �i������ �ޱ۰� ���ǵ�.
	if (_isShadowChasing == true)
	{
		//�ޱ۰��� ���� �߰��Ѵ�.
		_shadowPosition.x += cosf(Angle(_shadowPosition)) * _speed * _TimeManager->DeltaTime();
		_shadowPosition.y += -sinf(Angle(_shadowPosition)) * _speed * _TimeManager->DeltaTime();
		_shadowRc = Figure::RectMakeCenter(Vector2(_shadowPosition.x, _shadowPosition.y), Vector2(_shadowSize.x, _shadowSize.y));
	}

	//���� X������ �i ���� ����.
	if (_isArmChasing == false)
	{
		float angle = Math::GetAngle(_fistPosition.x, _fistPosition.y, _shadowPosition.x, _shadowPosition.y);
		_fistPosition.x += cosf(angle) * _speed * _TimeManager->DeltaTime();
		_fistRc = Figure::RectMakeCenter(Vector2(_fistPosition.x, _fistPosition.y), Vector2(_fistSize.x, _fistSize.y));
	}

	//���� Y������ �������� ���� ����.
	if (_isArmChasing == true)
	{
		float angle = Math::GetAngle(_fistPosition.x, _fistPosition.y, _shadowPosition.x, _shadowPosition.y);
		_fistPosition.y += -sinf(angle) * _speed * _TimeManager->DeltaTime();
		_fistRc = Figure::RectMakeCenter(Vector2(_fistPosition.x, _fistPosition.y), Vector2(_fistSize.x, _fistSize.y));
	}

	RECT tempRc;
	//���� �÷��̾�� �׸��ڰ� �浹�ߴٸ�
	if (IntersectRect(&tempRc, &_shadowRc, &_player->GetCollisionRect()))
	{
		//�浹�� �ð��� ���
		_timeCount += _TimeManager->DeltaTime();
		if (_timeCount > 1.f)
		{
			_timeCount = 0.f;
			_shadowCollisionCount++;
		}
	}
	//������ �ð��� ������ �������Ѽ� X�����θ��i�ƿ��� ���� �������� ����ϴ�. 
	if (_shadowCollisionCount > 5)
	{
		_isShadowChasing = false;
		_isArmChasing = true;
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
