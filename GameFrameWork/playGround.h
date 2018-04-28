#pragma once
#include "gameNode.h"
#include "StartScene.h"
#include "PlayScene.h"
#include "WorldScene.h"
#include "EndScene.h"
#include "LoadingScene.h"

class playGround : public gameNode
{
private:
    gameNode * _startScene;
    gameNode * _playScene;
	gameNode * _worldScene;
    gameNode * _endScene;
    gameNode * _loadingScene;

    int _alpha;

    bool _sceneChange1;
    bool _sceneChange2;
	bool _sceneChange3;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();



	playGround();
	~playGround();
};

