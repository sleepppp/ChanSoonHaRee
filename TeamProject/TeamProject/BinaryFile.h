#pragma once

class BinaryWriter
{
public:
	BinaryWriter();
	~BinaryWriter();

	void Open(wstring filePath, UINT openOption = CREATE_ALWAYS);
	void Close();

	void Bool(bool data);
	void Word(WORD data);
	void Int(int data);
	void UInt(UINT data);
	void Float(float data);
	void Double(double data);

	void String(const string& data);
	void Byte(void* data, UINT dataSize);

protected:
	HANDLE fileHandle;
	DWORD size;
};

//////////////////////////////////////////////////////////////////////////

class BinaryReader
{
public:
	BinaryReader();
	~BinaryReader();

	bool Open(wstring filePath);
	void Close();

	bool Bool();
	WORD Word();
	int Int();
	UINT UInt();
	float Float();
	double Double();

	string String();
	void Byte(void** data, UINT dataSize);

protected:
	HANDLE fileHandle;
	DWORD size;
};