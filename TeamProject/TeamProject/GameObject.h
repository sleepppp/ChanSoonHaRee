#pragma once
/***************************************************************
## GameObject ## 
��� ������Ʈ���� ������ �� Ŭ������ ��ӹ��� ���� 
������ ��� ������Ʈ���� ���������� �ʿ��� �͵�� GameObjectŬ�������� �̸� 
������ش�.
Player,UI,Enemy,Item��� 
***************************************************************/
class GameObject
{
	//Protected�� ���������ڰ� �����Ǿ� ������ �ڽ� ��ü������ �ش� ���� �� �Լ��� ���� ����
protected:
	Pivot::Enum _pivot;		//��Ʈ ������ �Ǻ� 
	string _name;			//������Ʈ �̸� 
	Vector2 _position;		//������Ʈ ��ǥ 
	Vector2 _size;			//������Ʈ ������ 
	RECT _rc;				//������Ʈ ��Ʈ 
	bool _isActive;			//Ȱ�� ���� 
	Synthesize(bool,_isLive,IsLive)	//���� ����(������ Synthesize �־����, ������ �̰����� �غ� �� �ѹ� �Ẹ����) 
public:
	//�����ڸ� 
	GameObject();
	//�Ҹ��� �ǰڽ��ϴ�
	//�Ҹ��ڿ��� �����Լ��� �ٿ� �ִ� ������ GameObject*�� Object�� �����ϱ� ������ delete GameObject�� �ϰ� �Ǹ�
	//�ڽ� ��ü�� �Ҹ��ڵ� ȣ��Ǿ�� �Ѵ�. ���� virtual�� �Ⱥ��̸� �ڽ� �Ҹ��ڴ� ȣ���� �ȉ�
	virtual ~GameObject();
	//virtual void Init() = 0; �� ���� � �Լ��� �ڿ� = 0 �� ���̸� 
	//�ش� �Լ��� ���������Լ��� �Ǿ �ƹ� ���뵵 �ۼ��� �� ���� 
	//�ڽ� ��ü�� �ݵ�� ���� �����Լ��� �������̵�(override) ���־�� �Ѵ�. 
	//���� ���� �� ������~
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0; 
	//������
	string GetName()const { return _name; }
	Vector2 GetPosition()const { return this->_position; }
	Vector2 GetSize()const { return this->_size; }
	RECT GetRect()const { return this->_rc; }
	bool GetActive()const { return this->_isActive; }
	//������
	void SetName(string name) { this->_name = name; }
	void SetPosition(Vector2 pos);
	void SetSize(Vector2 size);
	void SetPivot(Pivot::Enum pivot);
	void SetActice(bool b) { this->_isActive = b; }
	//��Ʈ�� �ǹ� �������� ������Ʈ �����ش�.
	void UpdateRect();
};

