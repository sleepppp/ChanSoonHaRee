#pragma once
#include "GameObject.h"
class Player : public GameObject
{
	class Image* _image;	//�÷��̾� �̹�����������Ʈ
	float _frameCount;		//�ִ� �����ӽð���
	float _frameIndexX;		//�ִ� ������ ����
	float _frameIndexY;		//�ִ� ������ ����
	float _speed;			//

	float _standRate;
	float _runRate;

	float _changeIndexX;
	bool _isRolling;

	RECT _colliRc;	//�浹������ �׸�



	//�÷��̾� �������� ���� enum��
	enum class State
	{
		stand_L,
		stand_R,
		stand_U,
		stand_D,
		run_L,
		run_R,
		run_U,
		run_D,
		//rolling_L,
		end
	};

	State _state;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

	RECT getPlayerCollisitionRc() { return _colliRc; }

	Player();
	~Player();
};

