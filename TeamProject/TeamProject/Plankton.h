#pragma once
#include "Enemy.h"
class Plankton : public Enemy
{
private:
	enum class PlanktonState
	{
		Follow = 0,
		Attack,
		Attacked,
		Dead,
		End
	};

	class Image* _plankton;			//�ö�ũ�� ���� �̹���
	class Image* _planktonRed;		//�ö�ũ�� ���� (�ǰ�)
	class Image* _planktonWhite;	//�ö�ũ�� �Ͼ� (�ǰ�)


	PlanktonState _planktonState;	//�̳� ������Ʈ : �ö�ũ�� ����

	bool _isAttack;					//���� bool ��
	bool _isAtkedRender;			//�ǰ� Render bool ��

	RECT _atkRect;					//���� ��Ʈ

public:
	Plankton(Vector2 position);
	~Plankton();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

	void PlanktonStates();

	void AtkedState(Vector2 position, float angle, float speed, float countValue);

};




