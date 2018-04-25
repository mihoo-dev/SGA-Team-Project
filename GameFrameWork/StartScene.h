#pragma once
#include "gameNode.h"
class StartScene :
    public gameNode
{
public:
    StartScene();
    ~StartScene();

    HRESULT init();
    void release();
    void update();
    void render();
};

