#include "stdafx.h"
#include "iniDataManager.h"


iniDataManager::iniDataManager()
{
}


iniDataManager::~iniDataManager()
{

}

HRESULT iniDataManager::init()
{

	return S_OK;
}

void iniDataManager::release()
{

}


void iniDataManager::addData(const char* subject, const char* title, const char* body)
{
	//구조체 선언

	tagIniData iniData;

	iniData.subject = subject;
	iniData.title = title;
	iniData.body = body;

	arrIniData vIniData;
	vIniData.push_back(iniData);

	_vIniData.push_back(vIniData);

}

void iniDataManager::iniSave(char* fileName)										  
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s.ini", fileName);

	//현재 디렉토리 경로를 받아오는 함수
	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	for (int i = 0; i < _vIniData.size(); ++i)
	{
		arrIniData vData = _vIniData[i];

		//[제갈량] [] 만들어주는 함수
		WritePrivateProfileString(vData[0].subject, vData[0].title, vData[0].body, str);

		vData.clear();
	}

	_vIniData.clear();
}


char* iniDataManager::loadDataString(const char* fileName, const char* subject, const char* title)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	//현재 경로의 iniData파일로 접근
	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	char data[128] = { NULL };
	GetPrivateProfileString(subject, title, "", data, 64, str);

	return data;
}

int iniDataManager::loadDataInterger(const char* fileName, const char* subject, const char* title)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	//현재 경로의 iniData파일로 접근
	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	return GetPrivateProfileInt(subject, title, 0, str);
}
