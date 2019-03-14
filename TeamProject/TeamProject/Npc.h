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

	//�ִϸ��̼��� ���� ���� �ݺ���
	typedef map<State, class Animation*>::iterator AnimationIter;
	class Animation* _mainAnimation;
	map<State, class Animation*> _animationList;	//���º� �ִϸ� �����ϱ� ���� �� ���
	
	State _state;
	//Move* _move;

	//Math::GetAngle()
	//�� ��ġ �迭�� ���
	//4�� �迭�̻� �Ѿ���Ҷ� 0���� �ʱ�ȭ �Ͽ� 0��ġ�� �ٽ� ������ �Ѵ�.

	
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

