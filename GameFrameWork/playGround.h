#pragma once
#include "gameNode.h"
#include "StartScene.h"
#include "WorldScene.h"
#include "EndScene.h"
#include "LoadingScene.h"
#include "StoreScene.h"
#include "ClearScene.h"

//스테이지
#include "TutorialScene.h"
#include "GraveyardScene.h"
#include "BossSnakeScene.h"
#include "HotDogScene.h"
#include "BossBearScene.h"
#include "BunnyScene.h"

class playGround : public gameNode
{
private:
    gameNode * _startScene;
	gameNode * _worldScene;
    gameNode * _endScene;
    gameNode * _loadingScene;
	gameNode * _storeScene;
    gameNode * _clearScene;

	//스테이지
	gameNode * _tutorialScene;
	gameNode * _graveyardScene;
	gameNode * _snakeScene;
	gameNode * _hotdogScene;
	gameNode * _bearScene;
	gameNode * _bunnyScene;

    int _alpha;

    bool _sceneChange1;
    bool _sceneChange2;
	bool _sceneChange3;
	bool _sceneChange4;
	bool _sceneChange5;
	bool _sceneChange6;
	bool _sceneChange7;
	bool _sceneChange8;
    bool _sceneChange9;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();



	playGround();
	~playGround();
};

