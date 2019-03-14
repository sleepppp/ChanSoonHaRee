#pragma once
#include "GameObject.h"

class Npc :	public GameObject
{
protected:	
	class Image* _ImgKids;
	float _count;
	RECT _npcRc;
	vector<Vector2>movePoint;
	Vector2 position;
	//Vector2 size;
	float _speed;
	int _index;
	int _frameX;
	int _frameY;

	enum class State
	{
		Left, Right, Up, Down, end
	};

	//애니메이션을 담을 맵의 반복자
	typedef map<State, class Animation*>::iterator AnimationIter;
	class Animation* _mainAnimation;
	map<State, class Animation*> _animationList;	//상태별 애니를 관리하기 위해 맵 사용
	
	State _state;
	//Move* _move;

	//Math::GetAngle()
	//각 위치 배열로 담고
	//4번 배열이상 넘어가려할때 0으로 초기화 하여 0위치로 다시 돌도록 한다.

	
public:
	Npc();
	~Npc();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

	void ChangeAnimation(State state);
	void NpcAni();

};

