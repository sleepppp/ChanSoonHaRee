#include "stdafx.h"
#include "TestEnemy.h"
#include "TestPlayer.h"
#include "TestPlayer.h"
TestEnemy::TestEnemy(Vector2 position, Vector2 size, Pivot::Enum pivot, float speed)
{
	this->_name = "Enemy";			// 내이름은?
	this->_position = position;		//내좌표 주세요
	this->_size = size;				//나는 어느정도 크기인가요?
	this->_pivot = pivot;			//나는 어디를 기준으로 그려지고 있죠?
	this->_speed = speed;			//내 속도를 알려주오
	this->_isActive = true;			//난 아직 활성화 중이에요
	this->_isAttacked = false;		//전 아직 얻어맞고 있지 않아요
	this->UpdateRect();				//위를 기준으로 나를 그려주세요.
}

TestEnemy::~TestEnemy()
{
}


void TestEnemy::Init()
{
	//플레이어의 정보를 사용하고 싶으므로 키값을 통해서 정보를 꺼내올 거에요
	this->_player = (TestPlayer*)_ObjectManager->FindObject("TestPlayer");
	//이런 이미지가 있나요? 있다면 주세요
	//_ImageManager->AddFrameImage("BackMove", L"GolemBackMove.png", 47, 0);
	
	//아직 공격중이아니라서 카운팅이 되고있지 않아요
	this->_attackCount = 0;
}

void TestEnemy::Release()
{

}

void TestEnemy::Update()
{
	//내 움직임에 관련된 내용이에요
	EnemyMove();
	//나는 어떻게 공격할까요?
	EnemyAttack();
	//내가 공격을 시작할 사거리를 알려주는 함수에요
	AttactDistance();
}

void TestEnemy::Render()
{
	//나를 그려주고있어요 
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
	//플레이어의 정보를 건네주세요
	this->_player = (TestPlayer*) _ObjectManager->FindObject("TestPlayer");
	//그 정보를 기반으로 나와 플레이어 간의 각도을 찾을게요
	this->_angle = Math::GetAngle(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
	
	//얻은 각도를 기반으로 움직일래요
	this->_position.x += cosf(_angle) * _speed * _Time->DeltaTime();
	this->_position.y += -sinf(_angle) * _speed * _Time->DeltaTime();
	//나를 계속해서 그려주세요.
	this->UpdateRect();

}

void TestEnemy::EnemyAttack()
{
	//충돌을 위한 쓰레기값이 필요해요
	RECT TestTemp = { 0 };
	//충돌했다면?
	if (IntersectRect(&TestTemp, &_rc, &_player->GetRect()))
	{
		//이건 피격인데 왜 내가 맞죠? 잘못됬어요.
		_isAttacked = true;
	}
	this->UpdateRect();
}

//에너미 상태별 정리.
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
	//내가 공격할 사거리를 알기 위해서 나와 플레이어간의 직선거리를 재요.
	_distance = Math::GetDistance(_position.x, _position.y, _player->GetPosition().x, _player->GetPosition().y);
	//그 직선거리가 내 가로길이의 두배가 넘는다면?
	if (_distance < (_size.x * 2))
	{
		//내가 공격을 시작 할게요
		_isAttack = true;
	}
	//내가 공격을 한다면
	if (_isAttack == true)
	{
		//어택 카운트를 더해주세요
		_attackCount++;
	}
	//만약에 그 카운트가 20보다 커지면
	if (_attackCount > 20)
	{
		//카운트를 초기화하고 공격상태를 펄스시켜요.
		_attackCount = 0;
		_isAttack = false;
	}
}