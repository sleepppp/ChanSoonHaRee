#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
protected:
	//�������� Ÿ��. ������ �˱� ���ؼ� ���� �̳Ѱ�
	enum class MoveType
	{
		Top = 0, Left, Right, Bottom, End
	};

	//�i�»��¿� ���� ���¸� �����ϱ� ���ؼ� ����� ���� �̳Ѱ�.
	//����� ���¸� �����ϱ� ���ؼ� �������. �ǰݽ� �̹����� �ٲ�ų� ���� �ʰ� �����̴� ������ ��Ʋ���⵵ �����Ƿ� 
	//���� Attacked�� ���� �ʿ䰡 ���� ������Ʈ�� ���ʹ��� ��쿡�� �⺻ ������ ��ü�� ���ٰ� ���� ���������� Idle���·� ����.
	enum class StateType
	{
		Chasing = 0, attack
	};

protected:
	float _speed;			//�ӵ�
	float _distance;		//�����Ÿ��� ���ϱ� ���� ����
	float _angle;			//�ޱ�
	float _attackedAngle;	//������ �޾��� �ÿ� ƨ���� ���� ����.
	int _damage;			//���ݷ�
	int _hp;				//ü��
	RECT _renderRect;		//�̹����� ���ؼ� ���� ��Ʈ
	float _count;			//�ð��� ��� ���ؼ� ���� ī��Ʈ ����.

	bool _attacked;			//������ �������θ� �����ϱ� ���ؼ� ���� �� ����.
	bool _attackedColor;	//�ǰݽ� ��, ������ ��¦���� �־�� �ϱ� ������ ������ �� ����.
	//���ʹ� ������� ����
	MoveType _move;		//���⿡ ���õ� �̳��� �ҷ����� ���� �Լ�

	StateType _state;	//���¿� ���õ� �̳��� �ҷ����� ���� �Լ�

	//�ٸ� ����� Ŭ���� �ҷ�����
	class Player* _player;

public:

	//�� �浹�� ���ؼ� ������ ó���� �� �� �ְ� �������� �� hp�� ��� �Լ�.
	//�浹ó���� �ϰ� ������ ������ �� �Լ��� �ҷ��� �ȿ� �������� �־��ָ� ������ �������� ������ ���ͼ� �� hp�� �����.
	virtual void AttackedDemege(int damage);

	//��Ʈ ������ ���� �Լ� ���η�Ʈ �̿ܿ��� ��� ��Ʈ�� �ڵ带 ����ȭ �ϰ� �; ���� �Լ�.
	RECT UpdateRect(Vector2 position, Vector2 size, Pivot::Enum _pivot);

	//���ʹ� �����̴� Ÿ��. �ޱ۰��� ���� �̹����� �ٶ󺸴� �����̳� ������ ��Ҹ� �� �� ����.
	//������ ��Ƴ��� ���ݴ� �ڿ������� ������ �� ����.
	void EnemyMoveType();

	//�̰� ������ �ݸ��� ��Ʈ�� ����Ϸ��� �� ��Ʈ���� ���� �� �ٲ�� �ؼ�
	//�����Լ��� �̿��ؼ� ���ʿ��� ���ڰ��� �ٲ㼭 ���� �������� ��Ʈ�� �浹ó���� ��Ű���� ���� �Լ�.
	RECT GetCollisionRect()const override {return _renderRect;}

	//�ڽ��̿��� ���͵�� �浹ó���� �ϰ� ������ ���.
	//�ణ�� ���� ������ �����ٸ� �浹ó���� �ϸ�ȵǴ°͵� �з��� �� ����.
	//�Ʒ��� InterSectReaction�� �����Ǿ��ִ�.
	void ObjectCollision();

	//�̰� ���� �ƴ� �浹���ε� ���ʹ� or ���� �����̴� ��ü�� �� �̿��� �͵��̶� �浹�Ҷ� �����.
	//�����ؼ� �浹�� ��븦 ���Ҷ� ����Ѵٰ� �����ϸ� ���� ��
	bool IntersectReaction(RECT* moveRect, RECT* unMoveRect);

	//���ʹ̴� �׻� �÷��̾ �߽����� ���ư��� ������ �÷��̾���� �����Ÿ��� ���ϰ� ��� ���ؼ� ����� ����.
	float Distance(Vector2 pos);

	//���Ͻ��� ���������� ���ϰ�  �÷��̾ ���ϰ� �i�� ���ؼ� ����� ���� �ޱ��Լ�.
	float Angle(Vector2 angle);

public:
	virtual void Init();
	virtual void Release() {}
	virtual void Update() {}
	virtual void Render() {}

	void SprayItemEnemy(string name);	//���ʹ� ������ �Ѹ��� �Լ�

public:
	Enemy();
	~Enemy();
};
