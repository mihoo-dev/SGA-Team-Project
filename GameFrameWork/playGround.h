#pragma once
#include "gameNode.h"
#include "StartScene.h"
#include "PlayScene.h"
#include "EndScene.h"
#include "LoadingScene.h"

class playGround : public gameNode
{
private:
    gameNode * _startScene;
    gameNode * _playScene;
    gameNode * _endScene;
    gameNode * _loadingScene;

    int _alpha;

    bool _sceneChange1;
    bool _sceneChange2;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();



	playGround();
	~playGround();
};

