#include "stdafx.h"
#include "SaveLoadModule.h"

const char SaveModule::token = '\t';
const char SaveModule::next = '\n';
const char SaveModule::endToken = '/';

SaveModule::SaveModule(string filePath)
	:file(nullptr), filePath(filePath)
{
}

SaveModule::~SaveModule()
{
}

bool SaveModule::Open()
{
	//파일 오픈 할때 성공하면 0 아니면 에러값
	bool succeeded = fopen_s(&file, filePath.c_str(), "w+t");
	if (succeeded == false)
		return true;
	return false;
}

void SaveModule::Close()
{
	fwrite(&SaveModule::endToken, sizeof SaveModule::endToken, 1, file);

	if(file != nullptr)
		fclose(file);
}

void SaveModule::String(string str)
{
	temp += str;
	temp += SaveModule::token;
}

void SaveModule::Int(int i)
{
	temp += to_string(i);
	temp += SaveModule::token;
}

void SaveModule::Float(float f)
{
	temp += to_string(f);
	temp += SaveModule::token;
}

void SaveModule::Bool(bool b)
{
	temp += to_string(b);
	temp += SaveModule::token;
}

void SaveModule::EndLine()
{
	fwrite(temp.c_str(), temp.size(), 1, file);
	temp.clear();
}



LoadModule::LoadModule(string filePath)
{
}

LoadModule::~LoadModule()
{
}

bool LoadModule::Open()
{
	return false;
}

void LoadModule::Close()
{
}

void LoadModule::String(string str)
{
}

void LoadModule::Int(int i)
{
}

void LoadModule::Float(float f)
{
}

void LoadModule::Bool(bool b)
{
}

void LoadModule::EndLine()
{
}
