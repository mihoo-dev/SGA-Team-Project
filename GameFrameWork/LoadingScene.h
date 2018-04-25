#pragma once
#include "gameNode.h"
class LoadingScene :
    public gameNode
{
private:

public:
    LoadingScene();
    ~LoadingScene();

    HRESULT init();
    void release();
    void update();
    void render();
};

