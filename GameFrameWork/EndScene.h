#pragma once
#include "gameNode.h"
class EndScene :
    public gameNode
{
private:
    bool _sceneStart;
    int _alpha;
public:
    EndScene();
    ~EndScene();

    HRESULT init();
    void release();
    void update();
    void render();
};

