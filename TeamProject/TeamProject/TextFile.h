#pragma once

/*********************************************
## TextWriter ##
�ؽ�Ʈ ���� ���� ��
**********************************************/
class TextWriter
{
private:
	static const char spaceToken;
	static const char endLineToken;
	static const char endFileToken;
private:
	FILE* file;
	string tempStr;
public:
	TextWriter() :file(nullptr){}

	bool Open(string filePath);
	void Close();

	void String(string str);
	void Int(int i);
	void Float(float f);
	void Bool(bool b);
	void UInt(UINT ui);

	void EndLine();
};
/*********************************************
## TextReader ##
�ؽ�Ʈ ���� �б� ��
**********************************************/
class TextReader
{
private:
	static const char spaceToken;
	static const char endLineToken;
	static const char endFileToken;
private:
	FILE* file;
	string tempStr;
	int endIndex;
public:
	TextReader() :file(nullptr) ,endIndex(0){}

	bool Open(string filePath);
	void Close();

	string String();
	int Int();
	float Float();
	bool Bool();
	UINT UInt();

	void ReadLine();
};