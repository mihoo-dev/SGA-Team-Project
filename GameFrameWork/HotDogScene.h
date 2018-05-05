#pragma once
#include "gameNode.h"

class PlayerManager;

class HotDogScene :	public gameNode
{
private:
	PlayerManager*	_pm;
	
	float				_loopX;
	int					_scriptX;
	int					_scriptState;

	//버튼 관련 변수
	BOOL						_pressX;
	int							_Xframe;
	int							_Xcount;

public:
	HotDogScene();
	~HotDogScene();

	HRESULT init();
	void release();
	void update();
	void render();
	
	//버튼 함수
	void button();
	
	//자막 함수
	void Script();
	void MoveScript();
	void CheckStatus();
};

