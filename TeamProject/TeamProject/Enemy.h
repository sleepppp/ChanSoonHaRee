#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
protected:
	//�������� Ÿ��.
	enum class MoveType
	{
		Top = 0, Left, Right, Bottom, End
	};
	enum class StateType
	{
		Chasing = 0, Attacked, attack
	};

protected:
	float _speed;		//�ӵ�
	float _distance;	//�����Ÿ��� ���ϱ� ���� ����
	float _angle;		//�ޱ�
	int _demage;		//���ݷ�
	int _hp;			//ü��
	RECT _renderRect;	//�̹����� ���ؼ� ���� ��Ʈ

	//���ʹ� ������� ����
	MoveType _move;		//���⿡ ���õ� �̳��� �ҷ����� ���� �Լ�
	StateType _state;	//���¿� ���õ� �̳��� �ҷ����� ���� �Լ�

	//�ٸ� ����� Ŭ���� �ҷ�����
	class Player* _player;

public:
	void AttackedDemege(int damage);
	RECT UpdateRect(RECT rc, Vector2 position, Vector2 size, Pivot::Enum _pivot);
	void EnemyMoveType();

public:
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

public:
	Enemy();
	~Enemy();
};
