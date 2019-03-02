#pragma once
#include "GameObject.h"
class Player : public GameObject
{
	RECT _colliRc;	//�浹������ �׸�
	RECT _weaponRc;	//����(����) �׸�
	RECT _shieldRc;	//���� �׸�

	class Image* _image;	//�÷��̾� �̹�����������Ʈ
	float _frameCount;		//�ִ� �����ӽð���
	float _frameIndexX;		//�ִ� ������ ����
	float _frameIndexY;		//�ִ� ������ ����
	float _speed;			//

	float _standRate;
	float _runRate;

	float _changeIndexX;
	bool _isRolling;


	//�����¿� ��ǿ� enum
	enum class StateMove
	{
		stand_L, stand_R, stand_U, stand_D,
		run_L, run_R, run_U, run_D,
		roll_L, roll_R, roll_U, roll_D,
		sword_L, sword_R, sword_U, sword_D,
		shield_L, shield_R, shield_U, shield_D,
		end
	};
	StateMove _stateMove;
		
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

	void Move(StateMove _move);	//���°� ���� �Լ�


	RECT getPlayerCollisitionRc() { return _colliRc; }	//���޿�
	//void PlayerAtk();									//����� ���ʹ� �浹 ����
														//���ʹ� ����� �� �� �浹 ����

	Player();
	~Player();
};

