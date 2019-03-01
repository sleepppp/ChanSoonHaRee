#pragma once
/*****************************************************************
## GameObject ##
���� GameObject�� �޶��� �� :
RECT _rc -> _mainRect 
+ _callbackList;�߰�
+ _reserveMessageList;�߰�
*****************************************************************/
class GameObject
{
protected:
	//unordered_map�� �ؽ� ���̺�� �̷���� �ִ� map���μ� �ؽ��Լ��� ���� Ű���� �迭�� 
	//�ε����� �ٲٴ� ����� ����ϹǷ� �ſ� ���� Ž���ӵ��� ������.�ֻ��� ��� �ð����⵵ ����� ���� 
	//��� ����� ������ map�� �����ϴ�. �̷��� �ִ� ������ �˾Ƶ���

	//first���� �����ų �Լ��� Ű��, second���� �����ų �Լ��� ��Ƶд�
	//function<void(struct TagMessage)>�� �Լ��� �������ִ� ���� �����μ� �ʾȿ� ����ִ� �ڷ����� ������ ���� �ǹ̸� ������
	//��ȯ���� void�̰� ���ڷδ� struct TagMessage�� �޴� �Լ� 
	
	//������ ���� �ʿ� �Լ��� ��Ƶδ� ������ �� ��Ȱ�� ��ü���� ����� ���� ������ �޼������ ����� �����ϱ� �����̴�. 
	//���� ��� � ��ü���� GameObject�� ��ӹ��� Enemy��� ��ü�� Attack�̶�� �Լ��� ȣ���ϰ� ���� �� �츮�� 
	//Enemy* enemy = (Enemy*)ObjectManager->FindObject("sdas); enemy->Attack();
	//�� ���� �Լ��� ����ȯ�� �� �Ŀ� ���������� ȣ�����־�� �߾���
	//�� �ڵ��� �������� ã�ƿ� GameObject*�� EnemyŬ������ �ƴ� ���� �ڵ��� ���������� ��ƴٴ� ���̴�. 
	
	//�޼��� ����� ������ EnemyŬ���������� �̸� �ڽ��� callbackList�� "Attack"�̶�� Ű���� �Բ� Attack()�Լ��� ��Ƶд�. 
	//�ܺ��� ��ü������ EnemyŬ�������� �����ߴٰ� �˷��ְ� ���� �� enemy->SendMessage(TagMessage("Attack")); �� ���� 
	//�Լ��� ȣ�����ָ� �ȴ�. �̷��� �Ǹ� �÷��̾� Ŭ���������� EnemyŬ������ ����� �� �ʿ䰡 �������� Enemy*�� �ٿ� ĳ������ �� �ʿ䵵
	//��������.
	typedef unordered_map < string, function<void(struct TagMessage)>> CallbackHashmap;
	typedef unordered_map<string, function<void(struct TagMessage)>>::iterator CallbackHashmapIter;
protected:
	string _name;			//�̸�
	Pivot::Enum _pivot;		//�Ǻ�
	Vector2 _position;		//��ǥ
	Vector2 _size;			//������
	RECT _mainRect;			//���� ��Ʈ
	bool _isActive;			//Ȱ�� ����
private:	//�Ʒ��� �������� �ڽ� ��ü���� �Ժη� �ǵ�� �ȵǱ� ������ private�� ���´�. 
	bool _isLive;			//��ü ���� ����(�ش� �Ұ��� ���� ObjectManager���� ��ü�� �����Ѵ�) 

	CallbackHashmap _callbackList;	//�޼��� ��ſ� ����� ��(�̰��� �̸� Ű���� �Բ� �Լ��� ��Ƶд�) 
	//���� �޼��� ����Ʈ 
	//���� ���� �޼����� delayTime�� �����Ǿ� ������ �ٷ� �Լ��� �����Ű�� �ʰ� �̰����� ������. 
	//GameObject�� ������Ʈ������ �ش� �޼����� ������ Ÿ���� ����ϴٰ� �ش� �Լ��� ���� �����ش�. 
	vector<struct TagMessage> _reserveMessageList;
public:
	//������ �����ε� 
	//��Ȳ�� �°� �ڽİ�ü���� ���ϴ� �����ڸ� ����ϸ� �ȴ�. 
	GameObject();
	GameObject(string name, Vector2 pos, Vector2 size, Pivot::Enum pivot);
	virtual ~GameObject();
	//���� �����Լ��� �������� ���� ������ GameObjectŬ������ Release,Update������ ����Ǿ�� �� ������� �ֱ� �����̴�.
	virtual void Init() {}
	virtual void Release();
	virtual void Update();
	virtual void Render() {}
	//Ȱ��ȭ�� �� ����Ǵ� �Լ� (���ӿ�����Ʈ�� ��ӹ��� ��ü���� ���� Ȱ��ȭ �Ǵ� ������ �����ؾ� �� ������ �ִٸ� �ش� �Լ��� 
	//�������̵��ؼ� ������ �ۼ��ϸ� �ȴ�. 
	virtual void Enable() {}
	//��Ȱ��ȭ�� �� ����Ǵ� �Լ�
	virtual void Disable() {}
	//�ش� ��ü�� �޼����� ������.
	void SendCallbackMessage(const struct TagMessage message);
	//�ش� ��ü�� �̸� �޼����� �޾��� �� ������ �Լ��� ���
	void AddCallbackMessage(const string name, const function<void(struct TagMessage)> func);
public:
	//�����ڸ� �����ڵ�
	string GetName()const { return this->_name; }
	Vector2 GetPosition()const { return this->_position; }
	Vector2 GetSize()const { return this->_size; }
	RECT GetMainRect()const { return this->_mainRect; }
	bool GetActive()const { return this->_isActive; }
	bool GetLive()const { return this->_isLive; }

	void SetName(const string name) { this->_name = name; }
	void SetPivot(const Pivot::Enum pivot);
	void SetPosition(const Vector2 position);
	void SetSize(const Vector2 size);
	void SetActive(const bool b);
	void Destroy() { this->_isLive = false; }
protected:
	//�Ǻ��� ���� ��Ʈ�� ������Ʈ �ȴ�
	void UpdateMainRect();
};

