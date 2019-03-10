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
		End
	};

	class Image* _plankton;			//�ö�ũ�� ���� �̹���
	class Image* _planktonRed;		//�ö�ũ�� ���� (�ǰ�)
	class Image* _planktonWhite;	//�ö�ũ�� �Ͼ� (�ǰ�)


	PlanktonState _planktonState;	//�̳� ������Ʈ : �ö�ũ�� ����


public:
	Plankton(Vector2 position);
	~Plankton();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

	void PlanktonStates();
};

