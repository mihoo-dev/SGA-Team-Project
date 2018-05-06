#pragma once
#include "gameNode.h"
#include "PlayerManager.h"
#include "Bubble.h"
#include "Door.h"
#include <vector>

class TutorialScene : public gameNode
{
private:
    PlayerManager * _pm;

    int _alpha;

	//자막 관련 변수
	BOOL	_viewScript;
	int		_scriptX;
	int		_scriptState;

	//버튼 관련 변수
	BOOL						_pressX;	//버튼 표시 유무
	int							_Xframe;	//버튼 프레임
	int							_Xcount;	//버튼 프레임 관련 카운트

    vector<Object*> _vObject;
public:
    TutorialScene();
    ~TutorialScene();

    HRESULT init();
    void release();
    void update();
    void render();

	void TestText();
	void Script();
	void MoveScript();
	void button();
};

