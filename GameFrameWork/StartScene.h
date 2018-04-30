#pragma once
#include "gameNode.h"
class StartScene :
    public gameNode
{
private:
    int _alpha2;
    bool _sceneChange;

    int _alpha;
    float _alphaCount;

    RECT _pressStartButton;

public:
    StartScene();
    ~StartScene();

    HRESULT init();
    void release();
    void update();
    void render();
};

