#pragma once
#include "GameObject.h"
class Arrow : public GameObject
{	
	class Image* _imgArrow_left;
	class Image* _imgArrow_right;
	class Image* _imgArrow_up;
	class Image* _imgArrow_down;

	//vector <RECT> _bullet;
	float _speed;
	int _max;
	int _damage;
	bool fire;

	enum class State
	{
		Left,Right,Up,Down,
		end
	};

	State _state;
	//_isCameraOut;

public:
	Arrow(Vector2 pos);
	~Arrow();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

};

//new 贸府肺 茄惯究 阂房