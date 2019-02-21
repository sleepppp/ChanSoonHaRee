#pragma once
/***************************************************************
## GameObject ## 
모든 오브젝트들은 앞으로 이 클래스를 상속받을 예정 
때문에 모든 오브젝트들이 공통적으로 필요한 것들들 GameObject클래스에서 미리 
만들어준다.
Player,UI,Enemy,Item등등 
***************************************************************/
class GameObject
{
	//Protected로 접근지정자가 설정되어 있으면 자식 객체에서만 해당 변수 및 함수를 접근 가능
protected:
	Pivot::Enum pivot;		//렉트 생성할 피봇 
	string name;			//오브젝트 이름 
	Vector2 position;		//오브젝트 좌표 
	Vector2 size;			//오브젝트 사이즈 
	RECT rc;				//오브젝트 렉트 
	bool isActive;			//활성 여부 
	Synthesize(bool,isLive,IsLive)	//생사 여부(예제로 Synthesize 넣어봤음, 집에서 이것저것 해볼 때 한번 써보세요) 
public:
	//생성자며 
	GameObject();
	//소멸자 되겠습니다
	//소멸자에서 가상함수를 붙여 주는 이유는 GameObject*로 Object를 관리하기 때문에 delete GameObject를 하게 되면
	//자식 객체의 소멸자도 호출되어야 한다. 만약 virtual을 안붙이면 자식 소멸자는 호출이 안됌
	virtual ~GameObject();
	//virtual void Init() = 0; 과 같이 어떤 함수의 뒤에 = 0 을 붙이면 
	//해당 함수는 순수가상함수가 되어서 아무 내용도 작성할 수 없고 
	//자식 객체는 반드시 순수 가상함수를 오버라이딩(override) 해주어야 한다. 
	//만약 안할 시 빨간줄~
	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0; 
	//접근자
	string GetName()const { return name; }
	Vector2 GetPosition()const { return this->position; }
	Vector2 GetSize()const { return this->size; }
	RECT GetRect()const { return this->rc; }
	bool GetActive()const { return this->isActive; }
	//설정자
	void SetName(string name) { this->name = name; }
	void SetPosition(Vector2 pos);
	void SetSize(Vector2 size);
	void SetPivot(Pivot::Enum pivot);
	void SetActice(bool b) { this->isActive = b; }
	//렉트를 피벗 기준으로 업데이트 시켜준다.
	void UpdateRect();
};

