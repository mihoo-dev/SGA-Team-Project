#pragma once
#include "gameNode.h"

class PlayerManager;

class HotDogScene :	public gameNode
{
private:
	PlayerManager*	_pm;
	
	float				_loopX;				//구름 배경 루프렌더를 위한 변수
	int					_scriptX;			//자막 이미지 X좌표
	int					_scriptState;		//자막 단계
	int					_count;				//사운드매니져 오작동으로 인한 임시 카운트 변수

	//버튼 관련 변수
	BOOL						_pressX;	//버튼 표시 유무
	int							_Xframe;	//버튼 프레임
	int							_Xcount;	//버튼 프레임 관련 카운트

	//페이드 화면
	int					_alpha;
	BOOL				_sceneStart;

public:
	HotDogScene();
	~HotDogScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void OutStage();
	
	//씬 스타트
	void SceneStart();

	//버튼 함수
	void button();
	
	//자막 함수
	void Script();
	void MoveScript();
	void CheckStatus();
};

