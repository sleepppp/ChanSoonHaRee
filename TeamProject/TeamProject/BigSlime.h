#pragma once
#include "Enemy.h"
class BigSlime : public Enemy
{
private:
	enum class StateType
	{
		//�⺻ ��� ����ϰ��ִ� ����, �÷��̾ �߰��ϰ� �����ǰ� �ִ� ����, �÷��̾ �߰��ϰ� �ִ� ����, �÷��̾ �����ϰ� �ִ� ����, �״»���
		Idle, Create, Chasing, Attack, Dead, End
	};
	struct Ani
	{
		class Image* _CreateImage;
		class Animation* _animation;
	};
private:
	typedef map <StateType, Ani>::iterator _aniIter;

	map <StateType, Ani> _aniList;
	
	class Animation* _mainAnimation;

	StateType _state;
	Ani _ani;

	class Image* _createImage;	//���� �̹��� 
	class Image* _moveImage;	//���� �̹���
	class Image* _attackImage;	//���� �̹���

public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
public:
	void ChangeState(StateType state);
	void ChangeAnimation(StateType state);
	void CreateAnimation();


public:
	BigSlime(Vector2 pos);
	~BigSlime();
};

