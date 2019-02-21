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
	Pivot::Enum pivot;		//��Ʈ ������ �Ǻ� 
	string name;			//������Ʈ �̸� 
	Vector2 position;		//������Ʈ ��ǥ 
	Vector2 size;			//������Ʈ ������ 
	RECT rc;				//������Ʈ ��Ʈ 
	bool isActive;			//Ȱ�� ���� 
	Synthesize(bool,isLive,IsLive)	//���� ����(������ Synthesize �־����, ������ �̰����� �غ� �� �ѹ� �Ẹ����) 
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
	string GetName()const { return name; }
	Vector2 GetPosition()const { return this->position; }
	Vector2 GetSize()const { return this->size; }
	RECT GetRect()const { return this->rc; }
	bool GetActive()const { return this->isActive; }
	//������
	void SetName(string name) { this->name = name; }
	void SetPosition(Vector2 pos);
	void SetSize(Vector2 size);
	void SetPivot(Pivot::Enum pivot);
	void SetActice(bool b) { this->isActive = b; }
	//��Ʈ�� �ǹ� �������� ������Ʈ �����ش�.
	void UpdateRect();
};

