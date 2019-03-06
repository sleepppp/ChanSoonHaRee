#include "stdafx.h"
#include "Boss.h"
#include "Image.h"
#include "Animation.h"
#include "Player.h"


Boss::Boss()
{
	//������ ������ ������ �⺻���� ��ݵ�
	this->_position = Vector2(600, 100);	//��ǥ
	this->_size = Vector2(200, 200);		//ũ��
	this->_pivot = Pivot::CENTER;			//�߽���ġ
	this->_hp = 700;						//ü��
	this->_speed = 10.0f;					//�ӵ�
	this->_demage = 0;						//���ݷ�
	this->_distance = 0.f;					//�����Ÿ� (���߿� �����Ű� �ڵ常¥����)
	this->_angle = 0.f;						//�ޱ۰� (�����Ÿ��� ����)
	this->UpdateMainRect();					//��Ʈ����.
	//�ʱ� ���°��� ������ �������� �ʾƾ� �ϴϱ� ������ �ִ� ���¸� ������ش�.
	this->ChangeState(StateType::Idle);
}


Boss::~Boss()
{
}


void Boss::Init()
{

	//�÷��̾��� �̸����� �ҷ��ͼ� ���� ���� �ְ� ����� �ش�.
	this->_player = (Player*)_ObjectManager->FindObject(ObjectType::Object, "player");	
}

void Boss::Release()
{
}

void Boss::Update()
{
	switch (_state)
	{
	case Boss::StateType::Idle:
		if (_distance > _size.x)
			StateType::Create;
		break;
	case Boss::StateType::Create:
		//if(/*������ �̹����� ī��Ʈ ���� �ȴٸ�*/)
			//�������� ������ ������ �ϳ��� �ٲ��.
		break;
	case Boss::StateType::Dead:
		break;
	case Boss::StateType::Rock_Shoot:
		break;
	case Boss::StateType::Hand_Shoot:
		break;
	case Boss::StateType::Fist_Shoot:
		break;
	case Boss::StateType::End:
		break;
	default:
		break;
	}
}

void Boss::Render()
{
}

//���¿� ���� �ٲ��� �̳Ѱ��� ������ �ش�.
void Boss::ChangeState(StateType state)
{
	//�ٲ� ���°��� �������°��̶�� �ٲ�� �ȵǴϱ� �Լ��� ���������� �ϰ�
	if (_state == state)
		return;
	//���������� �ʾҴٸ� �ٲ� �Ŵϱ� ���¸� ������ �ش�.
	_state = state;
	
	//���¿� ���� �ִϸ��̼ǵ� �ٲ��ش�.
	this->ChangeAnimation(state);

	switch (_state)
	{
	case Boss::StateType::Idle:
		break;
	case Boss::StateType::Create:
		break;
	case Boss::StateType::Dead:
		break;
	case Boss::StateType::Rock_Shoot:
		break;
	case Boss::StateType::Hand_Shoot:
		break;
	case Boss::StateType::Fist_Shoot:
		break;
	case Boss::StateType::End:
		break;
	default:
		break;
	}
}
//�ٲ� ���¿� ���� �ִϸ��̼ǵ� �缳�� ���ش�.
void Boss::ChangeAnimation(StateType state)
{
	// ���� ���°��� ���Ϳ� ���!
	StateAnimationIter iter = _stateAnimationList.find(state);
	//���������� �����ʰ� ���°��� ���� ���͸� ã�Ҵٸ�!
	if (iter != _stateAnimationList.end())
	{
		//�� Ű���� ������ ������Ѷ�!
		_mainAnimation = iter->second;
		//�������� ����
		_mainAnimation->Stop();
		//���ο�� ����!
		_mainAnimation->Play();
	}

}
//�ִϸ��̼� ������ų ����� ���۰���
void Boss::CreateAnimation()
{
	//�̹����� ��� ���߿� �־����

	//�⺻ �������� �ʴ� �����϶�
	Animation* Idle = new Animation;
	//�÷��̾ �ν��ϰ� �����ϱ� ���ؼ� �����ǰ�������
	Animation* Create = new Animation;
	//�÷��̾�� ���¾� ���� ��
	Animation* Dead = new Animation;
	//�÷��̾ �����ϱ� ���ؼ� ���� ������
	Animation* Rock_Shoot = new Animation;
	//�÷��̾ �����ϱ� ���� ���� ������
	Animation* Hand_Shoot = new Animation;
	//�÷��̾ �����ϱ� ���� �g�c�ϸ� ������
	Animation* Fist_Shoot = new Animation;
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
