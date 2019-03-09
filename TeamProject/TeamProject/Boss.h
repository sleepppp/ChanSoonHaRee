#pragma once
#include "GameObject.h"
class Boss : public GameObject
{
private:
	//������ ���� ���� , �÷��̾ ����ġ�� ��, ����ġ����  �����, ������, �ն�����, �ָԹ߻�, ��������., 
	enum class StateType
	{
		Idle, Create,Dead, 
		Hand_Shoot_First, Hand_Shoot_Second, Hand_Shoot_Last,
		Rock_Shoot_First, Rock_Shoot_Second, Rock_Shoot_Last,
		Fist_Shoot_First, Fist_Shoot_Second, Fist_Shoot_Last, 
		End
	};

	struct AniAndImage
	{
		class Image* _bossImage;
		class Animation* _animation;
	};
private:
	//�÷��̾ �ҷ�����.
	class Player* _player;
	//���¸� �ҷ��������ؼ� �γѰ��� ��������.
	StateType _state;
	AniAndImage* _aniImage;

	typedef map<StateType, AniAndImage*>::iterator AniImgIter;
	map<StateType, AniAndImage*> _aniImgList;

//�̹���
#pragma region Image
	class Image* _handImgae;		//�� ������ ��ų�� �� �̹���
										 
	class Image* _rockImgae1;		//�� ������ ��ų�� �������� 1
	class Image* _rockImage2;		//�� ������ ��ų�� �������� 2
	class Image* _rockImage3;		//�� ������ ��ų�� �������� 3
	
	class Image* _slimeArmImage1;	//�� ������ ��ų�� ������ �� 1
	class Image* _slimeArmImage2;	//�� ������ ��ų�� ������ �� 2
#pragma endregion	

	int _hp;					//ü���� �־�� �� �Ű�
	int _demage;				//�÷��̾ �����ؾ��ϴϱ� �������� ���� ���̰�,
	float _speed;				//�� ���ݵ��� �ӵ��� �������ϴϱ� �ӵ��� ������ ��
	float _angle;				//������ ����ؾ��ϴϱ� �ޱ۰��� ���� ���̰�,
	float _distance;			//�÷��̾ �����Ÿ� �ȿ� ���� ���������ϴϱ� �÷��̾��� �Ÿ��� ��� ���ؼ� ���Ͻ��� �־�� �ϰ�,
	
	Vector2 _rockPosition;		//���鸶�� �浹�� �Ǿ�� �ϰ� ������ ��ǥ�� �ѷ�����ϴϱ� ����� ��ǥ�� �ֱ����ؼ� ��ǥ���־�߰���?
	Vector2 _rockSize;			//���鵵 ũ�Ⱑ ������ �Ƴ� �׷� ������վ�߰���
	RECT _rockRc;				//��ǥ �ְ� ũ�� ������ �׷������
	
	Vector2 _fistPosition;		//�÷��̾��� ��Ʈ�� �� �������� �g�c�ϰ� �浹���Ѿ��ϴϱ� �g�c���� ���� �׷��ְ�, 
	Vector2 _fistSize;			//�g�ɴϿ� �޸� �ָ� ũ�⵵ �־�� �Ұ� �Ƴ�
	RECT _fistRc;				//�g�c�Ͽ� �޸� �ָ��� ��Ʈ�� �־�� ����?

	RECT _handRc;				//�������ָԵ� ������ �����ϱ� ��Ʈ���־�� �ϰ�,
	RECT _attackedRc;			//������ �±� ���� ��Ʈ�� �־�� �ϰ�,
	
public:
	float Distance(Vector2 position);
	float Angle(Vector2 position);

	void ChangeState(StateType state);
	void UpdateState();
	void ChangeAnimation(StateType state);
	void CreateAnimatiom();
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

public:
	Boss();
	~Boss();
};

