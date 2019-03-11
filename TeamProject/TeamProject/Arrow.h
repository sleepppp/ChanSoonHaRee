#pragma once
#include "GameObject.h"
class Arrow : public GameObject
{	
private:
	class Image* _imgArrow_left;
	class Image* _imgArrow_right;
	class Image* _imgArrow_up;
	class Image* _imgArrow_down;

	//class UI
	//class Player* _player;
	//vector <RECT> _bullet;
	float _speed;
	int _max;
	int _damage;
	bool fire;
	
public:
	enum class State
	{
		Left,Right,Up,Down,
		end
	};
	State _state;

public:
	Arrow(Vector2 pos, State state);
	~Arrow();

	void Init() override;
	void Release()override;
	void Update()override;
	void Render()override;

};

//new 贸府肺 茄惯究 阂房