#include "stdafx.h"
#include "TestEnemy.h"
#include "TestPlayer.h"
#include "TestPlayer.h"
TestEnemy::TestEnemy(Vector2 position, Vector2 size, Pivot::Enum pivot, float speed)
{
	this->_name = "Enemy";			// ���̸���?
	this->_position = position;		//����ǥ �ּ���
	this->_size = size;				//���� ������� ũ���ΰ���?
	this->_pivot = pivot;			//���� ��� �������� �׷����� ����?
	this->_speed = speed;			//�� �ӵ��� �˷��ֿ�
	this->_isActive = true;			//�� ���� Ȱ��ȭ ���̿���
	this->_isAttacked = false;		//�� ���� ���°� ���� �ʾƿ�
	this->UpdateRect();				//���� �������� ���� �׷��ּ���.
}

TestEnemy::~TestEnemy()
{
}


void TestEnemy::Init()
{
	//�÷��̾��� ������ ����ϰ� �����Ƿ� Ű���� ���ؼ� ������ ������ �ſ���
	this->_player = (TestPlayer*)_ObjectManager->FindObject("TestPlayer");
	//�̷� �̹����� �ֳ���? �ִٸ� �ּ���
	//_ImageManager->AddFrameImage("BackMove", L"GolemBackMove.png", 47, 0);
	
	//���� �������̾ƴ϶� ī������ �ǰ����� �ʾƿ�
	this->_attackCount = 0;
}

void TestEnemy::Release()
{

}

void TestEnemy::Update()
{
	//�� �����ӿ� ���õ� �����̿���
	EnemyMove();
	//���� ��� �����ұ��?
	EnemyAttack();
	//���� ������ ������ ��Ÿ��� �˷��ִ� �Լ�����
	AttactDistance();
}

void TestEnemy::Render()
{
	//���� �׷��ְ��־�� 
	_DXRenderer->FillRectangle(_rc, DefaultBrush::green);
	if (_isAttack == false)
	{
		_DXRenderer->DrawEllipse(_position, (_size.x * 2), DefaultBrush::blue);
	}
	if (_isAttack == true)
	{
		_DXRenderer->DrawEllipse(_position, (_size.x * 2), DefaultBrush::red);
	}
}

void TestEnemy::EnemyMove()
{
	//�÷��̾��� ������ �ǳ��ּ���
	this->_player = (TestPlayer*) _ObjectManager->FindObject("TestPlayer");
	//�� ������ ������� ���� �÷��̾� ���� ������ ã���Կ�
	this->_angle = Math::GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
	
	//���� ������ ������� �����Ϸ���
	this->_position.x += cosf(_angle) * _speed * _Time->DeltaTime();
	this->_position.y += -sinf(_angle) * _speed * _Time->DeltaTime();
	//���� ����ؼ� �׷��ּ���.
	this->UpdateRect();

}

void TestEnemy::EnemyAttack()
{
	//�浹�� ���� �����Ⱚ�� �ʿ��ؿ�
	RECT TestTemp = { 0 };
	//�浹�ߴٸ�?
	if (IntersectRect(&TestTemp, &_rc, &_player->GetRect()))
	{
		//�̰� �ǰ��ε� �� ���� ����? �߸�����.
		_isAttacked = true;
	}
	this->UpdateRect();
}

//���ʹ� ���º� ����.
void TestEnemy::EnemyMoveType()
{
	if (_move == MoveType::Back)
	{

	}
	else if (_move == MoveType::Front)
	{

	}
	else if (_move == MoveType::Left)
	{

	}
	else if(_move == MoveType::Rigth)
	{

	}
}

void TestEnemy::AttactDistance()
{
	//���� ������ ��Ÿ��� �˱� ���ؼ� ���� �÷��̾�� �����Ÿ��� ���.
	_distance = Math::GetDistance(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
	//�� �����Ÿ��� �� ���α����� �ι谡 �Ѵ´ٸ�?
	if (_distance < (_size.x * 2))
	{
		//���� ������ ���� �ҰԿ�
		_isAttack = true;
	}
	//���� ������ �Ѵٸ�
	if (_isAttack == true)
	{
		//���� ī��Ʈ�� �����ּ���
		_attackCount++;
	}
	//���࿡ �� ī��Ʈ�� 20���� Ŀ����
	if (_attackCount > 20)
	{
		//ī��Ʈ�� �ʱ�ȭ�ϰ� ���ݻ��¸� �޽����ѿ�.
		_attackCount = 0;
		_isAttack = false;
	}
}