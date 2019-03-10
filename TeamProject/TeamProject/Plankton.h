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

	class Image* _plankton;			//플랑크톤 몬스터 이미지
	class Image* _planktonRed;		//플랑크톤 빨강 (피격)
	class Image* _planktonWhite;	//플랑크톤 하양 (피격)


	PlanktonState _planktonState;	//이넘 스테이트 : 플랑크톤 상태


public:
	Plankton(Vector2 position);
	~Plankton();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

	void PlanktonStates();
};

