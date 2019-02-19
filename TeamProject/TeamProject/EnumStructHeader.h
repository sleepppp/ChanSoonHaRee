#pragma once
struct TagMessage
{
	string name;
	float delayTime;
	class DataContextValue* data;

	TagMessage()
		:name(""), delayTime(0.0f), data(nullptr) {}
	TagMessage(string name, float delayTime = 0.0f, class DataContextValue* data = nullptr)
		:name(name), delayTime(delayTime), data(data) {}
};

struct TagInt
{
	int x, y;
	TagInt()
		:x(0), y(0) {}
	TagInt(int x, int y)
		:x(x), y(y) {}
};

namespace Pivot
{
	enum Enum
	{
		LEFT_TOP = 0, CENTER, BOTTOM, TOP
	};

	inline string GetPivotName(Pivot::Enum pivot)
	{
		switch (pivot)
		{
		case Pivot::LEFT_TOP:
			return "LeftTop";
		case Pivot::CENTER:
			return "Center";
		case Pivot::BOTTOM:
			return "Bottom";
		case Pivot::TOP:
			return "Top";
		default:
			return "Error";
		}
	}

	inline Pivot::Enum GetPivotEnum(string name)
	{
		if (name == "LeftTop")
			return Pivot::LEFT_TOP;
		else if (name == "Center")
			return Pivot::CENTER;
		else if (name == "Bottom")
			return Pivot::BOTTOM;
		else
			return Pivot::TOP;
	}

}



class GameColor
{
public:
	union
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		};
		float arr[4];
	};

	GameColor()
		:r(0.f), g(0.f), b(0.f), a(0.f) {}
	GameColor(float r, float g, float b, float a)
		:r(r), g(g), b(b), a(a) {}
};