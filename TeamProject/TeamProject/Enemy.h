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
	enum class MoveType2
	{
		Left = 0, Right, End
	};
	enum class StateType
	{
		Chasing = 0, attack
	};

protected:
	float _speed;		//�ӵ�
	float _distance;	//�����Ÿ��� ���ϱ� ���� ����
	float _angle;		//�ޱ�
	float _attackedAngle;
	int _demage;		//���ݷ�
	int _hp;			//ü��
	RECT _renderRect;	//�̹����� ���ؼ� ���� ��Ʈ
	float _count;

	bool _attacked;
	//���ʹ� ������� ����
	MoveType _move;		//���⿡ ���õ� �̳��� �ҷ����� ���� �Լ�

	StateType _state;	//���¿� ���õ� �̳��� �ҷ����� ���� �Լ�

	//�ٸ� ����� Ŭ���� �ҷ�����
	class Player* _player;

public:
	virtual void AttackedDemege(int damage);
	//��Ʈ ������ ���� ����
	RECT UpdateRect(Vector2 position, Vector2 size, Pivot::Enum _pivot);
	//���ʹ� �����̴� Ÿ��.
	void EnemyMoveType();
	bool IntersectReaction(RECT* moveRect, RECT* unMoveRect);
	RECT GetCollisionRect()const override {return _renderRect;}
public:
	virtual void Init();
	virtual void Release() {}
	virtual void Update() {}
	virtual void Render() {}


public:
	Enemy();
	~Enemy();
};
