#include "stdafx.h"
#include "Boss.h"
#include "Image.h"
#include "Animation.h"
#include "Player.h"


Boss::Boss()
{
	//보스의 몸통을 생성할 기본적인 골격들
	_name = "Boss";
	this->_imagePosition = Vector2(1070, 340);	//좌표
	this->_size = Vector2(700, 700);		//크기
	this->_pivot = Pivot::CENTER;			//중심위치
	this->_hp = 800;						//체력
	this->_speed = 300.0f;					//속도
	this->_damage = 0;						//공격력
	this->_distance = 0.f;					//직선거리 (나중에 넣을거고 코드만짜려고)
	this->_angle = 0.f;						//앵글값 (직선거리와 같음)
	this->_imageRc = Figure::RectMakeCenter(_imagePosition, _imageSize); //렉트생성.
	this->CreateAnimatiom();
	
	//------------1번 공격을 위한 변수들-----------------//
	this->_shadowPosition = Vector2(_imagePosition.x, _imagePosition.y);
	this->_shadowSize = Vector2(50, 50);
	this->_shadowImage = _ImageManager->AddImage("shadow", L"../Resources/Enemy/Boss/Shadow.png", true);
	this->_handPosition = Vector2(_shadowPosition.x, _shadowPosition.y - 400);
	this->_handSize = Vector2(150, 150);
	this->_handImage = _ImageManager->AddFrameImage("hand", L"../Resources/Enemy/Boss/hand.png", 19, 1, true);
	this->_timeCount = 0.f;
	this->_ChasingCount = 0;
	this->_drapCount = 0;
	this->_handFrame = 0;
	//초기 상태값은 보스가 움직이지 않아야 하니까 가만히 있는 상태를 만들어준다.
	_state = StateType::Create;
	this->ChangeState(StateType::Idle);
}


Boss::~Boss()
{
}

void Boss::Init()
{
	//플레이어의 이름으로 불러와서 내가 쓸수 있게 만들어 준다.
	this->_player = (Player*)_ObjectManager->FindObject(ObjectType::Object, "Will");	
}

void Boss::Release()
{
}

void Boss::Update()
{
	//조건별로 처리할 부분은 여기에서
	UpdateState();
	HandShoot();
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

	_handImage->SetSize(_handImage->GetFrameSize(0));
	_handImage->SetScale(1.f);
	_handImage->FrameRender((int)_handPosition.x, (int)_handPosition.y, _handFrame, 0, Pivot::CENTER, true);
	if (_isDebug == true)
	{
		_DXRenderer->DrawRectangle(_shadowRc, DefaultBrush::yello, true);
		_DXRenderer->DrawRectangle(_handRc, DefaultBrush::yello, true);
		_DXRenderer->DrawRectangle(_imageRc, DefaultBrush::blue, true);
		_DXRenderer->DrawEllipse(Vector2(_imagePosition.x, _imagePosition.y), _size.x * 0.7f, DefaultBrush::blue, true);
	}
}

void Boss::ChangeState(StateType state)
{	
	//현제 상태와 바꿀 상태가 같다면 이 함수를 빠져나가라.
	if (_state == state)
		return;
	//그게 아니라면 상태를 바꿔라.
	_state = state;
	//상태와 같이 애니메이션도 바꿔줘라.
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
		//플레이어와 보스와의 거리가 보스 사이즈 X * 3 보다 작아진다면 생성으로바꿔라.
		if (_size.x * 0.7f > this->Distance(_imagePosition))
		{
			this->ChangeState(StateType::Create);
		}
		break;
	case Boss::StateType::Create:
		//현재 진행되고있는프레임이 마지막 프레임이라면
		if (_aniImage->_animation->GetNowFrameX() == 31)
		{
			//손날리는 공격의 시작으로 넘겨라.
			ChangeState(StateType::Hand_Shoot_First);
		}
		break;
	case Boss::StateType::Dead:

		break;
	case Boss::StateType::Hand_Shoot_First:
		//현재 진행되고있는프레임이 마지막 프레임이라면
		if (_aniImage->_animation->GetNowFrameX() == 18)
		{
			//실제 공격의 시작부분으로 넘겨라.
			ChangeState(StateType::Hand_Shoot_Second);
		}
		this->Dead();

		break;
	case Boss::StateType::Hand_Shoot_Second:

		_shadow = ShadowState::Chasing;

		this->Dead();
		break;
	case Boss::StateType::Hand_Shoot_Last:

		if (_aniImage->_animation->GetNowFrameX() == 10)
		{
			ChangeState(StateType::Hand_Shoot_First);
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
	//플레이어가 에너미의 인지반경 밖에 있을경우 실행되는 애니메이션과 이미지
	AniAndImage* idle = new AniAndImage;
	idle->_animation = new Animation;
	idle->_bossImage = _ImageManager->AddFrameImage("idle", L"../resources/Enemy/Boss/CreateBoss.png", 32, 1, true);
	idle->_animation->SetStartEndFrame(0, 0, 0, 0, false);
	idle->_animation->SetIsLoop(false);
	idle->_animation->SetFrameUpdateTime(1.f);
	_aniImgList.insert(make_pair(StateType::Idle, idle));

	//플레이어를 에너미가 인식하고 공격모션이 나오기 전에 자기 자신을 꺠우는 애니&이미지
	AniAndImage* create = new AniAndImage;
	create->_animation = new Animation;
	create->_bossImage = _ImageManager->AddFrameImage("create", L"../resources/Enemy/Boss/CreateBoss.png", 32, 1, true);
	create->_animation->SetStartEndFrame(0, 0, 31, 0, false);
	create->_animation->SetIsLoop(false);
	create->_animation->SetFrameUpdateTime(0.2f);
	_aniImgList.insert(make_pair(StateType::Create, create));

	//보스가 죽을때 나오는 애니&이미지
	AniAndImage* dead = new AniAndImage;
	dead->_animation = new Animation;
	dead->_bossImage = _ImageManager->AddFrameImage("dead", L"../Resources/Enemy/Boss/deadBoss.png", 82, 1, true);
	dead->_animation->SetStartEndFrame(0, 0, 81, 0, false);
	dead->_animation->SetIsLoop(false);
	dead->_animation->SetFrameUpdateTime(0.2f);
	_aniImgList.insert(make_pair(StateType::Dead, dead));
	
	//보스의 1번째 공격패턴 손날려서 공격하기의 전조 손을 날리는 애니&이미지
	AniAndImage* hand_Shoot_First = new AniAndImage;
	hand_Shoot_First->_animation = new Animation;
	hand_Shoot_First->_bossImage = _ImageManager->AddFrameImage("hand_Shoot_First", L"../Resources/Enemy/Boss/Hand_Shoot_First.png", 20, 1, true);
	hand_Shoot_First->_animation->SetStartEndFrame(0, 0, 19, 0, false);
	hand_Shoot_First->_animation->SetIsLoop(false);
	hand_Shoot_First->_animation->SetFrameUpdateTime(0.2f);
	_aniImgList.insert(make_pair(StateType::Hand_Shoot_First, hand_Shoot_First));

	//보스의 1번째 공격패턴 손날려서 공격하기의 손은 이미 날아가고 난뒤의 몸의 애니&이미지
	AniAndImage* hand_Shoot_Second = new AniAndImage;
	hand_Shoot_Second->_animation = new Animation;
	hand_Shoot_Second->_bossImage = _ImageManager->AddFrameImage("hand_Shoot_second", L"../Resources/Enemy/Boss/Hand_Shoot_Second.png", 30, 1, true);
	hand_Shoot_Second->_animation->SetStartEndFrame(0, 0, 29, 0, false);
	hand_Shoot_Second->_animation->SetIsLoop(true);
	hand_Shoot_Second->_animation->SetFrameUpdateTime(0.2f);
	_aniImgList.insert(make_pair(StateType::Hand_Shoot_Second, hand_Shoot_Second));

	//보스의 1번째 공격패턴 손날려서 공격하기의 손이 돌아오는 애니&이미지
	AniAndImage* hand_Shoot_Last = new AniAndImage;
	hand_Shoot_Last->_animation = new Animation;
	hand_Shoot_Last->_bossImage = _ImageManager->AddFrameImage("hand_Shoot_Last", L"../Resources/Enemy/Boss/Hand_Shoot_Last.png", 11, 1, true);
	hand_Shoot_Last->_animation->SetStartEndFrame(0, 0, 10, 0, false);
	hand_Shoot_Last->_animation->SetIsLoop(false);
	hand_Shoot_Last->_animation->SetFrameUpdateTime(0.2f);
	_aniImgList.insert(make_pair(StateType::Hand_Shoot_Last, hand_Shoot_Last));
}

//죽을때 불러와질 함수.
void Boss::Dead()
{
	//스킬을쓰는 도중에 체력이 0이나 0이하라면
	if (_hp <= 0)
	{
		//죽는상태로 넘겨라.
		ChangeState(StateType::Dead);
	}
}

void Boss::HandShoot()
{
	switch (_shadow)
	{
		float angle;
		//그림자가 플레이어를 쫒을때
	case ShadowState::Chasing:
		angle = Math::GetAngle(_shadowPosition.x, _shadowPosition.y, _player->GetPosition().x, _player->GetPosition().y);
		_shadowPosition.x += cosf(angle) * _speed * _TimeManager->DeltaTime();
		_shadowPosition.y += -sinf(angle) * _speed * _TimeManager->DeltaTime();
		//손은 그림자를 쫒아라.
		_hand = HandState::Chasing;
		//그림자가 플레이어와 충돌하는 동안.
		RECT temp;
		if (IntersectRect(&temp, &_shadowRc, &_player->GetCollisionRect()))
		{
			//타임카운트가 들어가고
			_timeCount += _TimeManager->DeltaTime();
		}
		//일정 타임카운트가 넘어가면
		if (_timeCount > 0.5)
		{
			_timeCount = 0.f;
			//체이싱카운트가들어가고
			_ChasingCount++;
		}
		//5보다 커진다면
		if (_ChasingCount >= 5)
		{
			//그림자를 멈춰라.
			_shadow = ShadowState::Stop;
		}
		break;
	case ShadowState::Stop:
		//그림자가 멈추면 손이 내려와라.
		_hand = HandState::Down;

		break;
	case ShadowState::End:
		break;
	default:
		break;
	}

	switch (_hand)
	{
		float angle;
		float distance;
	case HandState::Up:
		//그림자와 손과의 거리
		distance = Math::GetDistance(_handPosition.x, _handPosition.y, _shadowPosition.x, _shadowPosition.y);

		//손과 그림자의 앵글값.
		angle = Math::GetAngle(_shadowPosition.x, _shadowPosition.y, _handPosition.x, _handPosition.y);
		//거리가 500보다 작으면
		if (distance <= 500)
		{
			_timeCount += _TimeManager->DeltaTime();
			if (_timeCount > 0.5f)
			{
				_handFrame++;
			}
			if (_handFrame >= 18)
			{
				_handFrame = 18;
			}

			//위로 올라가라.
			_handPosition.y += -sinf(angle) * (_speed * 0.7) * _TimeManager->DeltaTime();
		}
		//어느정도 올라갔으면
		if (distance >= 500)
		{
			//몇번떨어졌는지 알기위해 카운트를 더해주고
			this->_drapCount++;

			_handFrame = 0;

			//다시 쫒아라.
			_shadow = ShadowState::Chasing;
		}
		if (_drapCount == 5)
		{
			ChangeState(StateType::Hand_Shoot_Last);
		}
		break;
	case HandState::Down:
		//손과 그림자의 앵글값.
		angle = Math::GetAngle(_handPosition.x, _handPosition.y, _shadowPosition.x, _shadowPosition.y);

		//그림자와 손의 Y축이 같지 않다면
		if (_handPosition.y != _shadowPosition.y)
		{
			_timeCount += _TimeManager->DeltaTime();
			if (_timeCount > 0.5f)
			{
				_handFrame++;
			}
			if (_handFrame >= 2)
			{
				_handFrame = 2;
			}

			//그림자의 Y축으로 이동해라.
			_handPosition.y += -sinf(angle) * (_speed * 3) * _TimeManager->DeltaTime();
		}
		//막약 같다면 
		if (_handPosition.y == _shadowPosition.y)
		{
			//이동해라.
			_hand = HandState::Stay;
		}
		break;
	case HandState::Stay:

		//땅에 일정시간 있어야 하니 카운트를 추가한다.
		_timeCount += _TimeManager->DeltaTime();
		if (_timeCount > 0.5f)
		{
			//일정 카운트마다 손의 프레임을 더해주고
			_handFrame++;
		}
		//손을 비비는 프레임이 끝나면
		if (_handFrame >= 15)
		{
			//일단 손의 프레임을 고정하고
			_handFrame = 15;
			//손의 상태를 올라가는 상태로 바꿔준다.
			_hand = HandState::Up;
		}
		break;
	case HandState::Chasing:
		//손의 X축은 언제나 그림자의 X축을 따라다닌다.
		angle = Math::GetAngle(_handPosition.x, _handPosition.y, _shadowPosition.x, _shadowPosition.y);
		_handPosition.x = _shadowPosition.x;
		break;
	case HandState::End:
		break;
	default:
		break;
	}
}

//직선거리 길이 구하는 공식.
float Boss::Distance(Vector2 position)
{
	//직선거리를 구하고
	float distance = Math::GetDistance(position.x, position.y, _player->GetPosition().x, _player->GetPosition().y);
	//반환해
	return distance;
}

//앵글값구하는 공식.
float Boss::Angle(Vector2 position)
{
	//앵글값을 구하고
	float angle = Math::GetAngle(position.x, position.y, _player->GetPosition().x, _player->GetPosition().y);
	//반환해
	return angle;
}
