#pragma once

class SaveModule
{
public:
	static const char token ;
	static const char next ;
	static const char endToken;
private:
	string filePath;
	FILE* file;
	string temp;
public:
	SaveModule(string filePath);
	~SaveModule();

	bool Open();
	void Close();

	void String(string str);
	void Int(int i);
	void Float(float f);
	void Bool(bool b);

	void EndLine();
};


class LoadModule
{
public:
	static const char token;
	static const char next;
	static const char endToken;
private:
	string filePath;
	FILE* file;
	string temp;
public:
	LoadModule(string filePath);
	~LoadModule();

	bool Open();
	void Close();

	void String(string str);
	void Int(int i);
	void Float(float f);
	void Bool(bool b);

	void EndLine();
};