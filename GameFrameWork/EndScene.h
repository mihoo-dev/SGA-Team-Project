#pragma once
#include "gameNode.h"
class EndScene :
    public gameNode
{
public:
    EndScene();
    ~EndScene();

    HRESULT init();
    void release();
    void update();
    void render();
};

