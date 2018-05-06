#pragma once
#include "gameNode.h"
class ClearScene :
    public gameNode
{
private:
    bool _sceneStart;
    int _alpha;
public:
    ClearScene();
    ~ClearScene();

    HRESULT init();
    void release();
    void update();
    void render();
};

