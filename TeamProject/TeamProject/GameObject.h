#pragma once
class GameObject
{
protected:
	Pivot::Enum pivot;
	string name; 
	Vector2 position;
	Vector2 size; 
	RECT rc; 
	bool isActive;
	Synthesize(bool,isLive,IsLive)
public:
	GameObject();
	virtual ~GameObject();

	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0; 

	string GetName()const { return name; }
	Vector2 GetPosition()const { return this->position; }
	Vector2 GetSize()const { return this->size; }
	RECT GetRect()const { return this->rc; }
	bool GetActive()const { return this->isActive; }

	void SetName(string name) { this->name = name; }
	void SetPosition(Vector2 pos);
	void SetSize(Vector2 size);
	void SetPivot(Pivot::Enum pivot);
	void SetActice(bool b) { this->isActive = b; }

	void UpdateRect();
};

